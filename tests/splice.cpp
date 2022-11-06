#include <list>
#include <iostream>

int main() {
    std::list<int> list1{1, 2, 3, 4, 5};
    std::list<int> list2{6, 7, 8, 9};
    list1.splice(list1.end(), list2, list2.begin(), list2.end());
    for (auto i : list1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (auto i : list2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
}