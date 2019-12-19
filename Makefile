all: project

project: building.o input.o min_heap.o rb_tree.o wanye.o
			g++ building.o input.o min_heap.o rb_tree.o wanye.o -o risingCity

building.o: building.cpp building.hpp
			g++ -c building.cpp 


input.o: input.cpp input.hpp
			g++ -c  input.cpp 
			
min_heap.o: min_heap.cpp min_heap.hpp
			g++ -c min_heap.cpp 


rb_tree: rb_tree.cpp rb_tree.hpp
			g++ -c rb_tree.cpp

wanye.o: wanye.cpp wanye.hpp
			g++ -c wanye.cpp

clean: 
		rm -rf *o project