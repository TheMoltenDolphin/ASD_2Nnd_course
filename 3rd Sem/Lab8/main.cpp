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


void RadixSort(std::vector<int>& arr)
{
    std::vector<int> negatives, positives;
    for (int x : arr) {
        if (x < 0)
            negatives.push_back(-x);
        else
            positives.push_back(x);
    }

    void (*radix)(std::vector<int>&) = [](std::vector<int>& arr) {
        std::vector<int> bit[10];
        std::vector<int> itBit;
        int size = arr.size();

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



        for(int i = 0; i < m; i++)
        {
            
            for(int j = 0; j < size; j++)
            {
                bit[abs((arr[j] % (int)pow(10, i+1)) / (int)pow(10, i))].push_back(arr[j]);
            }


            for(int c = 0; c < 10; c++)
            {
                std::cout << c << " ";
                for(int item : bit[c])
                {
                    std::cout << item << " ";
                }
                std::cout << std::endl;
            }

            arr.clear();
            std::cout << arr.size();

            for(int k = 0; k < 10; k++)
            {
                for(int j = 0; j < bit[k].size(); j++)
                {
                    std::cout << "!@#123";
                    arr.push_back(bit[k][j]);
                }
                bit[k].clear();
            }

            std::cout << "iter " << i << std::endl;
        }

        std::cout << "done" << std::endl;
    };

    radix(positives);
    radix(negatives);

    arr.clear();
    for (std::vector<int>::reverse_iterator it = negatives.rbegin(); it != negatives.rend(); ++it)
        arr.push_back(-*it);
    for (int x : positives)
        arr.push_back(x);

    return;
}


int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = generateRandomVector(10);
    arr.push_back(0);

    for(int i = 0; i < 10; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    RadixSort(arr);
    
    for(int i = 0; i < 10; i++)
         std::cout << arr[i] << " ";
    
    return 0;
}