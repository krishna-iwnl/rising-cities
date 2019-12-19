#include "wanye.hpp"


wanye::wanye(vector<vector<string>>commands,ofstream& out):commands(commands),time(0),out(out){}

//Selects the next building to be operated and removes it from the heap or returns a placeholder if heap is empty
heap_node wanye::select_building(){
    if(!empty()){
        heap_node top = heap.get_min();
        heap.pop();   
        return top;
    }
    else{
        return {{-1,-1,-1},nullptr};
    }
}

//The main loop of the program, builds the city according to given rules in project
void wanye::build_city(){
    int curr_time = 0;
    //loop till first insert command
    while(empty() and !commands.empty()){
        int ctime = stoi(commands.back()[0]);
        if(ctime == time) perform_input_op(out);
    }
    //Loop untill no commands and no buildings left
    while(!empty() or !commands.empty()){
       heap_node top = select_building();

       //min_e has the build time for curr building 
       int min_e = min(5,top.building.total_time - top.building.exec_time);
        //if no building then run next command
        if(min_e==0){
               if(!commands.empty()){
                time++;
                  if(!commands.empty()){
                int ctime = stoi(commands.back()[0]);
                if(ctime == time) perform_input_op(out);
            }
                continue;
            }
        }
        //Loop through days and increment execution time accordingly
       for(int day=0;day<min_e;day++){
            time++;
            if(top.map_ptr){
                map.increment(top.building.id);
            }
            if(!commands.empty()){
                int ctime = stoi(commands.back()[0]);
                if(ctime == time) perform_input_op(out);
            } 
       }
       top.building.exec_time+=min_e;
       //Output if building is done
       if(top.building.exec_time == top.building.total_time and top.building.id!=-1){
            out<<"("<<top.building.get_id()<<","<<" "<<time<<")"<<endl;
           remove_from_map(top);
       }
       //insert in heap as it still needs execution
       else{
           heap.insert(top);
       }
    }
    out<<time<<endl;
}
bool wanye::empty(){
    return heap.empty();
}

//Inserts in both data structures
void wanye::insert(Building b){
    rb_node* node = map.insert(b);
    heap.insert({b,node});    
}

//Delete in RBT
void wanye::remove_from_map(heap_node h_node){
    map.erase(h_node.building.get_id());
}

//Run the input operation
void wanye::perform_input_op(ofstream& out){
    vector<string> cmd = commands.back();
    commands.pop_back();

    if(cmd[1]=="INSERT"){
        int id = stoi(cmd[2]);
        int total_time = stoi(cmd[3]);
        // cout<<"insert\n";
        insert({id,0,total_time});
    }
    else if(cmd[1]=="PRINT_NODE"){
        int id = stoi(cmd[2]);
        map.print(id,out);
    }
    else if(cmd[1]=="PRINT_RANGE"){
        int l = stoi(cmd[2]);
        int r = stoi(cmd[3]);
        map.range_print(l,r,out);    
    }
    else{
        cout<<"\n reading error \n";
    }
}

int main(int argc, char *argv[]){
    cout << "\033[2J\033[1;1H";
    string input_file_name = argv[1];
    ofstream out("output_file.txt");
    IO io(input_file_name);
    auto cmds = io.read_input();
    wanye w(cmds,out);
    w.build_city();
}