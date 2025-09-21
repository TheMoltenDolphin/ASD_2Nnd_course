#include <iostream>
#include <windows.h>
#include <vector>


void selSort(std::vector<int>& arr)
{
    int len = arr.size();
    int steps = 0;
    for(int i = 0; i < len; i++)
    {
        int min = INT_MAX;
        int ToSwap = steps;
        for(int j = steps; j < len; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                ToSwap = j;
            }
        }
        std::swap(arr[i], arr[ToSwap]);
        steps++;
    }

    return;
}
int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = { 5, 3, 8, 1, 2, 7 };
    selSort(arr);
    for (int num : arr)
        std::cout << num << " ";
    return 0;



}