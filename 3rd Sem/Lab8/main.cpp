#include <iostream>
#include <windows.h>
#include <vector>
#include <random>


std::vector<int> generateRandomVector(int length) {
    std::vector<int> vec(length);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-pow(10, 3), pow(10, 3));
    for (int& x : vec)
        x = dis(gen);
    return vec;
}

void RadixSort(std::vector<int> arr)
{


    std::vector<int>* bit[10];
    std::vector<int> itBit;
    int size = arr.size();
    for(int i = 0; i < 10; i++)
        bit[i] = new std::vector<int>;

    int m = 0;
    for(int i = 0; i < size; i++)
    {
        int k = abs(arr[i]);
        int len = 0;
        while(k > 0)
        {
            k /= 10;
            len++;
        }
        m = max(m, len);
        itBit.push_back(len);
    }



    for(int i = 0; i < 1; i++)
    {
        for(int j = 0; j < size; j++)
        {
            bit[abs(arr[j] % (int)pow(10, i+1))]->push_back(arr[j]);
        }

        for(int i = 0; i < 10; i++)
        {
            std::cout << i << " ";
            for(int item : *bit[i])
            {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    }


    arr.clear();


    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < bit[i]->size(); j++)
        {
            arr.push_back((*bit[i])[j]);
        }
    }

    for(int i = 0; i < 10; i++)
        std::cout << arr[i] << " ";

    for(int i = 0; i < 10; i++)
        delete bit[i];

    return;
}


int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = generateRandomVector(10);

    for(int i = 0; i < 10; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    RadixSort(arr);
    
    // for(int i = 0; i < 10; i++)
    //     std::cout << arr[i] << " ";
    
    return 0;
}