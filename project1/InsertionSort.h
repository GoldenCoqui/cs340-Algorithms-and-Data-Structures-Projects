#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <vector>

class InsertionSort
{
private:
    std::vector<int>& arr;
public:
    InsertionSort(std::vector<int>& inputArr) : arr(inputArr){}
    
    void sort()
    {
        for (int i = 1; i < arr.size(); ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

};



#endif