#include<iostream>
#include<fstream>
#include<utility>
#include<set>
#include<unordered_set>
#include<iterator>

int main(){
    std::set<double> num;
    num.insert(4);
    num.insert(3);
    num.insert(1);

    for(auto pos = num.begin(); pos != num.end(); ++pos){
      std::cout << *pos << " ";
    }

  return 0;
}

