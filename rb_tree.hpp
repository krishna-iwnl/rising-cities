#include <iostream>
#include <vector>
#include "building.hpp"
#include<fstream>
using namespace std;

enum class COLOR : bool
{
    RED,
    BLACK
};
class rb_node
{
public:
    Building building;
    COLOR color;
    rb_node *left, *right, *parent;

    rb_node(COLOR color, Building building);
    void to_black();
    void to_red();
    bool is_black(rb_node* node);
    bool is_red(rb_node* node);
    rb_node* get_sib();
    rb_node* get_uncle();
};
ostream &operator<<(ostream &st, rb_node &b);

class rb_tree
{
public:
    rb_node *root;
    int size;
    rb_tree();
    rb_node* insert(Building building);
    void increment(int id);
    void erase(int id);
    void erase(rb_node *root,int id);
    void replace_in_parent(rb_node* root,rb_node* new_node);
    rb_node *find(int id);
    rb_node* find_min(rb_node*);
    void inspect();
    bool empty();
    void update(rb_node* node,int new_exec);
    void insert_fix(rb_node* node);
    void ll_rotate(rb_node* node);
    void rr_rotate(rb_node* node);
    void lr_rotate(rb_node* node);
    void rl_rotate(rb_node* node);
    void insert_rotation_fix(rb_node* node);
    void range_print(int l,int r,ofstream& out);
    void range_print_util(rb_node* root,int l,int r,vector<Building>& res,ofstream& out);
    void erase_fix(rb_node* y,rb_node* py);
    int red_children(rb_node*);
    void print(int id,ofstream& out);
    void print_util(rb_node* root,int id,ofstream& out);
};
ostream &operator<<(ostream &st, rb_tree &b);
