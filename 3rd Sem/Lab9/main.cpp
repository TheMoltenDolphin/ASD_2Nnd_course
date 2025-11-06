#include <iostream>
#include <windows.h>
#include <vector>

static void heapify(std::vector<int>& data, size_t root, size_t heapSize) {
    while (true) {
        size_t left = 2 * root + 1;
        if (left >= heapSize)
            break;
        size_t largest = root;
        if (data[left] > data[largest])
            largest = left;
        size_t right = left + 1;
        if (right < heapSize && data[right] > data[largest])
            largest = right;
        if (largest == root)
            break;
        std::swap(data[root], data[largest]);
        root = largest;
    }
    

    for(int i : data)
        std::cout << i << " ";
    std::cout << std::endl;
}


static void heapSort(std::vector<int>& data) {
    size_t n = data.size();
    if (n < 2)
        return;
    for (size_t i = n / 2; i > 0; --i) {
        heapify(data, i - 1, n);
    }
    for (size_t end = n; end > 1; --end) {
        std::swap(data[0], data[end - 1]);
        heapify(data, 0, end - 1);
    }
}

int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::vector<int> arr = { 5, 2, 9, 1, 5, 6, 3, 4, 8, 7, 0, 10, 11, 12, 13, 25, 14, 55, 99, 100, 42, 20, 15, 30, 18, 17};
    heapSort(arr);
    for (int i : arr) {
        std::cout << i << " ";
    }
    return 0;
}

