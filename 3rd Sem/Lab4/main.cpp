#include <iostream>
#include <windows.h>
#include <vector>


void combSort(std::vector<int>& arr) {
    size_t len = arr.size();
    size_t gap = len / 1.247f;
    while(gap >= 1)
    {
        for(int i = 0; i < len-gap; i += 1)
            if(arr[i] > arr[i+gap])
                std::swap(arr[i], arr[i+gap]);
        gap /= 1.247;
    }
    return;
}

int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = { 5, 3, 8, 1, 2, 7 };
    combSort(arr);
    for (int num : arr)
        std::cout << num << " ";
    return 0;



}