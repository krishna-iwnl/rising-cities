#include "input.hpp"

IO::IO(string file_name) : file_name(file_name) {}

//parses a line of input
vector<string> IO::parse_list(string s) {
  istringstream ss(s);
  vector<string> res;
  string temp;
  while (getline(ss, temp, ',')) {
    res.push_back(temp);
  }
  return res;
}

//reads a line of input and categorizes the command
vector<string> IO::read_line(ifstream& file) {
  vector<string> line;
  if (file.is_open()) {
    int time = 0;
    string shit, command;
    file >> time >> shit;
    getline(file, command);
    line.push_back(to_string(time));
    string comm = command.substr(0, 7);
    int len = command.size();
    string args = command.substr(7, len);
    comm.erase(0, 1);
    if (comm[0] == 'P') comm.pop_back();
    args.erase(0, 1);
    args.erase(find(args.begin(), args.end(), ')'));
    vector<string> args_list = parse_list(args);
    if (comm == "Print" and args_list.size() == 2) {
      comm = "PRINT_RANGE";
    } else if (comm == "Print" and args_list.size() == 1) {
      comm = "PRINT_NODE";
    } else if (comm == "Insert") {
      comm = "INSERT";
    } else {
      comm = "ERROR";
    }
    line.push_back(comm);
    for (auto arg : args_list) {
      line.push_back(arg);
    }
  }
  return line;
}

//read the whole input
vector<vector<string>> IO::read_input() {
  ifstream f(file_name);
  vector<vector<string>> commands;
  if (!f) {
    cout << "Cannot find or open file" << endl;
    return commands;
  }
  while (!f.eof()) {
    try {
      auto line = read_line(f);
      commands.push_back(line);
    } catch (const std::exception& e) {
      std::cerr << "Exception: " << e.what() << '\n';
    }
  }
  reverse(commands.begin(),commands.end());
  return commands;
}

void write(){
  
}