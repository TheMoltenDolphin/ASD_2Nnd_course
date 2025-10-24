#include <iostream>
#include <windows.h>
#include <vector>
#include <random>


std::vector<int> generateRandomVector(int length) {
    std::vector<int> vec(length);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-pow(10, 4), pow(10, 4));
    for (int& x : vec)
        x = dis(gen);
    return vec;
}


int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = generateRandomVector(10);
    arr.push_back(0);
    return 0;
}