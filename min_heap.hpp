#include<iostream>
#include<vector>
#include "rb_tree.hpp"

using namespace std;

class heap_node {
public:
    Building building;
    rb_node* map_ptr;
    heap_node(Building building,rb_node* map_ptr);
};


class min_heap
{

public:
    int size;
    vector<heap_node> data;
    void heapify(int index);
    void insert(heap_node);
    void pop();
    bool compare(int p,int i);
    heap_node get_min();
    int left(int index);
    int right(int index);
    int parent(int index);
    void inspect();
    bool empty();
    min_heap();
    ~min_heap();
};
