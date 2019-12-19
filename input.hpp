#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<sstream>
using namespace std;

class IO{
    public:
    IO(string file_name);
    vector<string> parse_list(string s);
    vector<vector<string>> read_input();
    vector<string> read_line(ifstream& file);
    string file_name;
};