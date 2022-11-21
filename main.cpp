#include <iostream>
#include "bulkmanager.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage:" << std::endl;
        std::cout << "   bulk [number of commands]" << std::endl;
        return 0;
    }
    std::string one;
    bulkManager manager(atoi(argv[1]));
    while (std::cin >> one) {
        manager.newString(one);
    }
    manager.finish();
    return 0;
}
