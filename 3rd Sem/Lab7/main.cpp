#include <iostream>
#include <windows.h>
#include <vector>
#include <random>




void SetGaps(std::vector<int>& inp, int len)
{
    inp.clear();
    for(int i = 1; ((pow(3, i) - 1) / 2)  < len; i++)
        inp.push_back(((pow(3, i) - 1) / 2));
    std::reverse(inp.begin(), inp.end());
    return;
}

void shellSort(std::vector<int>& arr)
{
    int len = arr.size();
    std::vector<int> gaps;
    SetGaps(gaps, len);
    for(int gap : gaps)
        for(int i = gap; i < len; i++)
            for(int j = i; j >= gap && arr[j] < arr[j-gap]; j--)
                std::swap(arr[j], arr[j-gap]);


    return;
}

int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = { 5, 2, 9, 1, 5, 6, 3, 4, 8, 7, 0, 10, 11, 12, 13, 25, 14, 55, 99, 100, 42, 20, 15, 30, 18, 17};
    shellSort(arr);
    std::cout << "Sorted array: \n";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}