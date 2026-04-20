#include<iostream>
#include<fstream>
#include<utility>
#include<unordered_set>
#include<iterator>

int main(int argc, const char* argv[]){

  if(argc != 3){
    std::cerr << "Error, less than len 3";
    return 1;
  }
  else{
    std::string fileName = argv[1];
    std::string content = argv[2];

    std::ofstream out(fileName);
    out << content;
    return 0;
  }
  
}

