#include <iostream>
#include <windows.h>
#include <vector>


void insSort(std::vector<int>& arr)
{
    int len = arr.size();
    for(int i = 1; i < len; i++)
        for(int j = i; j > 0 && arr[j] < arr[j-1]; j--)
            std::swap(arr[j], arr[j-1]);
    return;
}

int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = { 5, 3, 8, 1, 2, 7 };
    insSort(arr);
    for (int num : arr)
        std::cout << num << " ";
    return 0;



}