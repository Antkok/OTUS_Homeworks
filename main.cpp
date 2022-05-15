#include <iostream>
#include <map>
#include "list.h"
#include "my_allocator.h"
#include "lib.h"

int main()
{
    std::map<int, size_t> firstMap;
    for (int i = 0; i < 10; ++i) {
        firstMap[i] = fact(i);
    }
    
    for (auto a : firstMap) {
        std::cout << a.first << " " << a.second << std::endl;
    }

    std::cout << std::endl;

    using testAlloc = myAlloc<std::pair<int, size_t>, 10>;
    auto secondMap = std::map<int, size_t, std::less<>, testAlloc>{};
    for (int i = 0; i < 10; ++i) {
        secondMap[i] = fact(i);
    }
    for (auto a : secondMap) {
        std::cout << a.first << " " << a.second << std::endl;
    }

    std::cout << std::endl;

    containerList<int> firstList;
    for (int i = 0; i < 10; ++i) {
        firstList.pushFront(i);
    }
    containerList<int, myAlloc<int, 10>> secondList;
    for (int i = 0; i < 10; ++i) {
        secondList.pushFront(i);
    }
    for (auto a : secondList) {
        std::cout << a << std::endl;
    }
}