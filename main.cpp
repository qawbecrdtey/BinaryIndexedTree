#include <iostream>
#include "BIT.hpp"

int main() {
    std::array<int, 10> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    auto bit = BIT<int>(10, [](int a, int b){ return a > b ? a : b; }, arr.begin());
    std::cout << bit.get(0) << '\n'; // 1
    std::cout << bit.get(4) << '\n'; // 9
    std::cout << bit.get(9) << '\n'; // 10
    bit.set(1, 6);
    std::cout << bit.get(2) << '\n'; // 6
    std::cout << bit.get(3) << '\n'; // 7
}