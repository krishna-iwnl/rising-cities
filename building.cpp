#include "building.hpp"

Building::Building(int _id,int _exec_time, int _total_time):id(_id),exec_time(_exec_time),total_time(_total_time){};

int Building::get_id(){
    return id;
}

int Building::get_exec(){
    return exec_time;
}

int Building::get_total(){
    return total_time;
}

ostream& operator<<(ostream& st,Building& b){ 
    st<<"("<<b.get_id()<<","<<b.get_exec()<<","<<b.get_total()<<")";
}

void Building::update(int new_exec){
    exec_time = new_exec;
}

void Building::increment(){
    exec_time++;
}

