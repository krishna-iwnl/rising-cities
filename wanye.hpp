#include<iostream>
#include<vector>
#include<fstream>
#include "min_heap.hpp"
#include "input.hpp"
using namespace std;

class wanye{
public:
    min_heap heap;
    rb_tree map;
    int time;
    vector<vector<string>> commands;
    ofstream& out;
    
    wanye(vector<vector<string>>commands,ofstream &out);
    heap_node select_building();
    void build_city();
    void insert(Building b);
    void remove_from_map(heap_node node);
    void perform_input_op(ofstream& res);
    bool empty();
    void build();
};
ostream &operator<<(ostream &st, wanye &w);

