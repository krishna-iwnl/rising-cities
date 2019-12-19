
void rb_tree::erase_fix(rb_node* y,rb_node* py){
  // if(y)cout<<"y "<<y->building.id<<"  ";
  // if(py)cout<<"py "<<py->building.id<<endl;
  if(!py){
    root =y;
    return;
  };
  // case 1 y is red
  if(is_red(y)){
    y->to_black();
    return;
  }
  //case 2 y is black root done!
  if(is_black(y) and y and y->parent==nullptr)
    return;
  //cases
  rb_node* v = nullptr;
  if(py->left==y) v = py->right;
  else v = py->left;

  //RB0/LB0 case 1 - py is black
  if(is_black(v) and red_children(v)==0 and is_black(py)){
    v->to_red();
    erase_fix(py,py->parent);
    return;
  } 
  //RB0/LB0 case 2 - py is red
  if(is_black(v) and red_children(v)==0 and is_red(py)){
    v->to_red();
    py->color == COLOR::BLACK;
    return;
  }
  //RB1 case 1
  if(py->right == y and is_black(v) and is_red(v->left) and is_black(v->right)){
    v->left->to_black();
    v->color = py->color;
    py->to_black();
    ll_rotate(py);
  }
  //LB1 case 1
  if(py->left == y and is_black(v) and is_red(v->right) and is_black(v->left)){
    v->right->to_black();
    v->color = py->color;
    py->to_black();
    rr_rotate(py);
  }
  //RB1 case 2
  if(py->right == y and is_black(v) and is_red(v->right) and is_black(v->left)){
    if(py->left->right)
      py->left->right->color = py->color;
    lr_rotate(py);
  }

  // LB1 case 2
  if(py->left == y and is_black(v) and is_red(v->left) and is_black(v->right)){
    if(py->right->left)
      py->right->left->color = py->color;
    rl_rotate(py);
  }
  //RB2
  if(py->right == y and is_black(v) and red_children(v)==2){
    if(py->left->right)
      py->left->right->color = py->color;
    lr_rotate(py);   
  }

  //LB2
  if(py->left == y and is_black(v) and red_children(v)==2){
    if(py->right->left)
      py->right->left->color = py->color;
    rl_rotate(py);   
  }

  // //RR0
  if(py->right == y  and is_red(v) and red_children(v)==0 and v and red_children(v->right)==0){
     if(v->right)
      v->right->to_red();
    if(v)
    v->to_black();
    ll_rotate(py);
  }
  // //LR0
  // if(py->left == y and is_red(v) and red_children(v)==0 and v and red_children(v->left)==0){
  //   if(v->left)
  //     v->left->to_red();
  //     if(v){
  //       cout<<*v<<endl;
  //       v->color = COLOR::BLACK;    
  //     }
  //   // rr_rotate(py);
  // }
  
  if(py->right == y  and is_red(v)){
    rb_node* w = v->right;
    //RR1 case 1
    if(w and is_red(w->left) and is_black(w->right)){
      w->left->to_black();
      lr_rotate(py);
    }
    //RR1 case 2
    else if(w and is_red(w->right) ){
      if(w->right)w->right->to_black();
      rr_rotate(w);
      lr_rotate(py);
    }
    else{
      // cout<<"msitake"<<endl;
    }
  }

}
