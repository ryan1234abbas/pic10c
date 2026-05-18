// #include <iostream>
// #include <string>

// template<typename Out, typename Container>
// Out first(Container& c) {
// return *( std::begin(c) );
// }
// int main()
// {
// 	std::string s("hi");
// 	first<char&>(s) = 'H';
// 	std::cout << s << std::endl;

// }


#include <iostream>
#include <string>

template<typename Out, typename Container>
Out first(Container& c) {
    return *(std::begin(c));
}

int main() {
    std::string s("hi");
    first<char>(s) = 'H';
    std::cout << s << std::endl;
}