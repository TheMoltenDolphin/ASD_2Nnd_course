#include <iostream>
#include <windows.h>
#include <vector>
#include <random>



int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = { 5, 2, 9, 1, 5, 6, 3, 4, 8, 7, 0, 10, 11, 12, 13, 25, 14, 55, 99, 100, 42, 20, 15, 30, 18, 17};
    arr.push_back(0);
    return 0;
}

