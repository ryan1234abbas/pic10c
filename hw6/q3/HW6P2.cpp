#include "array_template.h"

int main() {
    Array<int, 5> arr1;
    arr1.emplace(0, 3);
    arr1.emplace(1, 1);
    arr1.emplace(2, 4);
    arr1.emplace(3, -5);
    arr1.emplace(4, 6);
    arr1.print(); // Should trigger sorting and then print

    auto cmp = [](double x, double y) { return x * x < y * y; };
    Array<double, 5, decltype(cmp)> arr2(cmp);
    arr2.emplace(0, 3.0);
    arr2.emplace(1, 1.0);
    arr2.emplace(2, 4.0);
    arr2.emplace(3, -5.0);
    arr2.emplace(4, 6.0);
    arr2.print();

    Array<std::string, 3, std::greater<>> arr3;
    arr3.emplace(0);
    arr3.emplace(1, "Kiwi");
    arr3.emplace(2, 3, 'a');
    arr3.print();

    return 0;
}
