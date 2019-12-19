#include<iostream> 
using namespace std;

class Building{
public:
    int id,exec_time,total_time;
    Building(int _id,int _exec_time, int _total_time);
    int get_id();
    int get_exec();
    int get_total();
    void inspect();
    void increment();
    void update(int new_exec);
};
ostream& operator<< (ostream& st,Building& b) ;
