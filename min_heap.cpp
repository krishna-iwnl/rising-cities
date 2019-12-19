#include "min_heap.hpp"

heap_node::heap_node(Building building,rb_node* map_ptr):building(building),map_ptr(map_ptr){}
min_heap::min_heap() { size = 0; }

min_heap::~min_heap() {}

int min_heap::left(int i) { return (2 * i) + 1; }

int min_heap::right(int i) { return (2 * i) + 2; }

int min_heap::parent(int i) { return (i - 1) / 2; }

heap_node min_heap::get_min() {
  if (size != 0) {
    heap_node t = data[0];
    return t;
  } else {
    cout << "empty";
    return heap_node({-1, 0, 0},nullptr);
  }
}

bool min_heap::empty(){
  return size==0;
}

// return true if i should be up
bool min_heap::compare(int p, int i) {
  heap_node pb = data[p];
  heap_node ib = data[i];
  if (pb.building.get_exec() > ib.building.get_exec())
    return true;
  else if (pb.building.get_exec() == ib.building.get_exec() and pb.building.get_id() > ib.building.get_id())
    return true;
  else
    return false;
}

//push into heap
void min_heap::insert(heap_node n) {
  data.push_back(n);
  int i = size;
  size++;
  while (i > 0 and compare(parent(i), i)) {
    swap(data[parent(i)], data[i]);
    i = parent(i);
  }
}

//pop into heap
void min_heap::pop() {
  if (size == 0) {
    cout << "heap empty" << endl;
    return;
  }

  data[0] = data[size - 1];
  data.pop_back();
  size--;
  heapify(0);
}

//heapify downward 
void min_heap::heapify(int i) {
  int smallest = i;
  if (right(i) < size and compare(i, right(i))) {
    smallest = right(i);
  }
  if (left(i) < size and compare(i, left(i))) {
    smallest = left(i);
  }
  if (smallest != i) {
    swap(data[smallest], data[i]);
    heapify(smallest);
  }
}