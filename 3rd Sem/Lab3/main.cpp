#include <iostream>
#include <windows.h>




int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    long long x;
    std::cin >> x;

    int k = (int)(log(x) / log(3));
    int m = (int)(log(x) / log(5));
    int n = (int)(log(x) / log(7));

    for(int i = 0; i < k + 1; i++)
        for(int j = 0; j < m + 1; j++)
            for(int l = 0; l < n + 1; l++)
            {
                if(pow(3, i) * pow(5, j) * pow(7, l) > x)
                    continue;
                std::cout << pow(3, i) * pow(5, j) * pow(7, l) << std::endl;
            }


    return 0;
}