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


void QuickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        QuickSort(arr, low, i);
        QuickSort(arr, i + 2, high);
    }
}

int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = generateRandomVector(10);
    arr.push_back(0);

    for(int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    QuickSort(arr, 0, arr.size() - 1);

    for(int i = 0; i < arr.size(); i++)
         std::cout << arr[i] << " ";
    std::cout << std::endl;

    
    return 0;
}