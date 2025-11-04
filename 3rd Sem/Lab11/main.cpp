#include <iostream>
#include <windows.h>
#include <vector>
#include <random>


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

    std::vector<int> arr = { 5, 2, 9, 1, 5, 6, 3, 4, 8, 7, 0, 10, 11, 12, 13, 25, 14, 55, 99, 100, 42, 20, 15, 30, 18, 17};
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