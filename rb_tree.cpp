#include "rb_tree.hpp"
#include <iomanip>
#include<string>
#include <queue>
#include <algorithm>
#include <random>
#include <cmath>

// RB_NODE
rb_node::rb_node(COLOR color, Building building)
    : color(color),
      building(building),
      left(nullptr),
      right(nullptr),
      parent(nullptr) {}

rb_tree::rb_tree() : root(nullptr), size(0) {}

void rb_node::to_black(){
  this->color = COLOR::BLACK;
}

void rb_node::to_red(){
  color = COLOR::RED;
}

//gets sibling node - return nullptr if invaild
rb_node* rb_node::get_sib(){
  rb_node * p = this->parent;
  if(p==nullptr)return nullptr;
  if(p->left == this)
    return p->right;
  else if(p->right == this)
    return p->left;
  else{
    cout<<"error in sibling"<<endl;
    return nullptr;
  }
}

//gets uncle - returns nullptr if invalid
rb_node* rb_node::get_uncle(){
  rb_node* p = this->parent;
  if(p==nullptr)return nullptr;
  rb_node* gp = p->parent;
  if(gp==nullptr)return nullptr;
  return p->get_sib();
}

//checks if black
bool is_black(rb_node* node){
  if(node==nullptr)return true;
  return node->color == COLOR::BLACK;
}

//checks if red
bool is_red(rb_node* node){
  if(node==nullptr)return false;
  return node->color == COLOR::RED;
}

//RR rotate
void rb_tree::rr_rotate(rb_node* x){
  if(!x or !x->right)return;
  rb_node * y = x->right;
  rb_node * z = y->left;
  x->right = z;
  y->left = x;
  if(z)
    z->parent = x;
  replace_in_parent(x,y);
  x->parent = y;
  if(x==root)root=y;
}

//LL rotate
void rb_tree::ll_rotate(rb_node* x){
  if(!x or !x->left)return;
  rb_node * y = x->left;
  rb_node * z = y->right;
  x->left = z;
  y->right = x;
  if(z)
    z->parent = x;
  replace_in_parent(x,y);
  x->parent = y;
  if(x==root)root=y;
}

//RL rotate
void rb_tree::rl_rotate(rb_node* x){
  if(!x or !x->right or !x->right->left) return;
  ll_rotate(x->right);
  rr_rotate(x);
}

//LR rotate
void rb_tree::lr_rotate(rb_node* x){
  if(!x or !x->left or !x->left->right)return;
  rr_rotate(x->left);
  ll_rotate(x);
}

//Inserts new building and returns a pointer to node
rb_node* rb_tree::insert(Building new_building) {
  rb_node *new_node = new rb_node(COLOR::RED, new_building);
  rb_node* par = nullptr;

  if (root == nullptr) {
    root = new_node;
    root->to_black();
    return new_node;
  }
  rb_node **walk = &(root);
  while (*walk) {
    int curr_id = (*walk)->building.get_id();
    par = *walk;
    if (curr_id < new_building.get_id()) {
      walk = &(*walk)->right;
    } else if (curr_id > new_building.get_id()) {
      walk = &(*walk)->left;
    } else {
      cout << "duplicate\n";
      delete new_node;
      return nullptr;
    }
  }
  new_node->parent = par;

  *walk = new_node;
  insert_fix(new_node);
  if(is_red(root))root->to_black();
  return new_node;
}

//Fixes the Tree to follow RBT rules after insertion
void rb_tree::insert_fix(rb_node* node){
  if(node==nullptr)return;
  //case 0 - if node is root change it to black.
  if(node->parent==nullptr){
   node->to_black();
   return;
  }
  //case 1 - parent black, node is red.
  if(is_black(node->parent))return ;
  //case 2 - parent is red, so it has to have gp.try switching colors if uncle is red
  rb_node* uncle = node->get_uncle();
  if(is_red(uncle)){
    rb_node* gp = node->parent->parent;
    node->parent->to_black();
    uncle->to_black();
    gp->to_red();
    insert_fix(gp);
  }
  else if(is_black(uncle)){
    // cout<<"\nby rotation\n";
    insert_rotation_fix(node);
  }
  else{
    cout<<"unknown!"<<endl;
  }
}

//Insert fix utility by rotation
void rb_tree::insert_rotation_fix(rb_node* node){  
  rb_node* p = node->parent;
  rb_node* gp = node->parent->parent;
  
  if(p->left == node and gp->left == p){
    p->to_black();
    gp->to_red();
    ll_rotate(gp);
  }
  else if(p->left == node and gp->right == p){
    node->to_black();
    gp->to_red();
    rl_rotate(gp);
  }
  else if(p->right == node and gp->left == p){
    node->to_black();
    gp->to_red();
    lr_rotate(gp);
  }
  else if(p->right == node and gp->right == p){
    p->to_black();
    gp->to_red();
    rr_rotate(gp);
  }
  else{
    cout<<"error in rotation fix!"<<endl;
  }
}

//Find a node with building id 
rb_node* rb_tree::find(int id){
  rb_node** walk = &root;
  while (*walk) {
    int curr_id = (*walk)->building.get_id();
    if(curr_id == id){
      break;
    }
    else if (curr_id < id) {
      walk = &(*walk)->right;
    } else if (curr_id > id) {
      walk = &(*walk)->left;
    } 
  }
  rb_node *res = &**walk;
  return *walk;
}

//Utility to replace child in parent and vice versa
void rb_tree::replace_in_parent(rb_node* root,rb_node* new_node){
  if(root->parent){
    if(root->parent->left == root)
      root->parent->left = new_node;
    else
      root->parent->right = new_node;
  }
  if(new_node){
    new_node->parent=root->parent;
  }
}

//Erase a node with id
void rb_tree::erase(int id){
  erase(root,id);
}


//Erase util for erase function
void rb_tree::erase(rb_node* curr,int id){
  if(!curr)return;
  int curr_id = curr->building.get_id();
  if(curr_id < id){
    erase(curr->right,id);
    return;
  }
  else if(curr_id>id){
    erase(curr->left,id);
    return;
  }
  rb_node* y=nullptr;
  rb_node* py=nullptr;
  py = curr->parent;
  if(curr->left and curr->right){
    rb_node* replacement = find_min(curr->right);
    curr->building.id = replacement->building.get_id();
    erase(replacement,replacement->building.get_id());
    return ;
  }
  //last step ,deleting curr
  else if(curr->left){
    y = curr->left;
    replace_in_parent(curr,curr->left);
  }
  else if(curr->right){
    y = curr->right;
    replace_in_parent(curr,curr->right);
  }
  else{
    if(curr==root){
      delete curr;
      root=nullptr;
      return;
    }
    y = nullptr;
    replace_in_parent(curr,nullptr);
  }
  if(is_black(curr))
    erase_fix(y,py);
  delete curr;
  if(is_red(root))root->to_black();
  return;
}

//Updates the building exec time
void rb_tree::update(rb_node* node,int new_exec){
  node->building.update(new_exec);
}


//Fixes the RBT after deletion of a node(cases are labled in the function)
void rb_tree::erase_fix(rb_node* y,rb_node* py){
  // y is RED

  if(!py){
    root = y;
    return;
  }
  if(is_red(y)){
    y->to_black();
    return;
  }
  // add in real
  else if(y==root){    
    return;
  }
  rb_node* v = (py->left==y)?py->right:py->left;
  // cout<<*v<<endl;
  //R
  if(y==py->right){
    //B
    if(is_black(v)){
      //0
      if(red_children(v)==0){
        if(is_black(py)){
          v->to_red();
          erase_fix(py,py->parent);
          return;
        }
        else {
          v->to_red();
          py->to_black();
          return;
        }
      }
      //1
      else if(red_children(v)==1){
        if(is_red(v->left)){
          v->left->to_black();
          v->color = py->color;
          py->to_black();
          ll_rotate(py);
        }
        else{
          v->right->color = py->color;
          py->to_black();
          lr_rotate(py);
        }
      }
      //2
      else if(red_children(v)==2){
        v->right->color = py->color;
        py->to_black();
        lr_rotate(py);
      }
    }
    //R
    else{
      //0
      if(red_children(v->right)==0){
          v->right->to_red();
          v->to_black();
          ll_rotate(py);
      }
      //1
      else if(red_children(v->right)==1){
        rb_node* w = v->right;
        if(is_red(w->left)){
          w->left->to_black();
          lr_rotate(py);
        }
        else{
          rb_node* x = w->right;
          x->to_black();
          rr_rotate(w);
          lr_rotate(py);
        }
      }
      //2
      else if(red_children(v->right)==2){
        rb_node* w = v->right;
        rb_node* x = w->right;
        x->to_black();
        rr_rotate(w);
        lr_rotate(py);
      }
    }
  } 
  //L
  else if(y==py->left){
    //B
    if(is_black(v)){
      //0
      if(red_children(v)==0){
        if(is_black(py)){
          v->to_red();
          erase_fix(py,py->parent);
          return;
        }
        else {
          v->to_red();
          py->to_black();
          return;
        }
      }
      //1
      else if(red_children(v)==1){
        if(is_red(v->right)){
          v->right->to_black();
          v->color = py->color;
          py->to_black();
          rr_rotate(py);
        }
        else{
          v->left->color = py->color;
          py->to_black();
          rl_rotate(py);
        }
      }
      //2
      else if(red_children(v)==2){
        v->left->color = py->color;
        py->to_black();
        rl_rotate(py);
      }
    }
    //R
    else{
      //0
      if(red_children(v->left)==0){
          // print2DUtil(root,0);
          // cout<<"LR"<<endl;
          v->left->to_red();
          v->to_black();
          rr_rotate(py);
          // cout<<*v<<endl;
          // print2DUtil(root,0);
      }
      //1
      else if(red_children(v->left)==1){
        rb_node* w = v->left;
        if(is_red(w->right)){
          w->right->to_black();
          rl_rotate(py);
        }
        else{
          rb_node* x = w->left;
          x->to_black();
          ll_rotate(w);
          rl_rotate(py);
        }
      }
      //2
      else if(red_children(v->left)==2){
        rb_node* w = v->left;
        rb_node* x = w->left;
        x->to_black();
        ll_rotate(w);
        rl_rotate(py);
      }
    }
  }
  

}

//Check if tree is empty
bool rb_tree::empty(){
  return root==nullptr;
}


//count the number of red children
int rb_tree::red_children(rb_node* node){
  int res = 0;
  if(!node)return res;
  if(node->left!=nullptr and node->left->color==COLOR::RED)res++;
  if(node->right!=nullptr and node->right->color==COLOR::RED)res++;
  return res;
}


//Find the min element in a given subtree
rb_node* rb_tree::find_min(rb_node* root){
  rb_node * walk = root;
  while(walk->left){
    walk = walk->left;
  }
  return walk;
}

ostream &operator<<(ostream &st, rb_node &n) { 
  st << n.building;
}
ostream &operator<<(ostream &st, rb_tree &t) {}

// Outputs the buildings in a range
void rb_tree::range_print(int l,int r,ofstream& out){
  vector<Building> res;
  range_print_util(root,l,r,res,out);
  if(res.size()>0){
    out<<res[0];
  }
  for(int i=1;i<res.size();i++){
    out<<""<<res[i];
  
  }
  if(res.size()>0)out<<endl;
}

//Outputs a single building
void rb_tree::print(int id,ofstream& out){
  print_util(root,id,out);
}

// print utility function
void rb_tree::print_util(rb_node* root, int id,ofstream& out){
  if(root==nullptr){
    out<<"(0,0,0)"<<endl;
    return;
  }
  int num = root->building.get_id();
  if(num<id){
    // cout<<*root->building<<endl;
    print_util(root->right,id,out);
    return;
  }
  if(num>id){
    print_util(root->left,id,out);
    // cout<<*root->building<<endl;
    return;
  }
  out<<root->building<<","<<endl;
}

// Range print utility function
void rb_tree::range_print_util(rb_node* root,int l,int r,vector<Building> &res,ofstream& out){
  if(root==nullptr){
    return;
  }
  int num = root->building.get_id();
  if(num<l){
    // cout<<*root->building<<endl;
    range_print_util(root->right,l,r,res,out);
    return;
  }
  if(num>r){
    range_print_util(root->left,l,r,res,out);
    // cout<<*root->building<<endl;
    return;
  }
  range_print_util(root->left,l,r,res,out);
  res.push_back(root->building);
  range_print_util(root->right,l,r,res,out);
}

//Increments the building exec_time
void rb_tree::increment(int id){
  rb_node *node= this->find(id);
  if(node)
  node->building.exec_time += 1;
}
