#include <iostream>
#include <windows.h>
#include <vector>
#include <random>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= right) {
        if(arr[i] < arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    while(i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while(j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for(int t = 0; t < temp.size(); ++t)
        arr[left + t] = temp[t];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if(left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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

    mergeSort(arr, 0, arr.size() - 1);

    for(int i = 0; i < arr.size(); i++)
         std::cout << arr[i] << " ";

    std::cout << std::endl;

    
    return 0;
}