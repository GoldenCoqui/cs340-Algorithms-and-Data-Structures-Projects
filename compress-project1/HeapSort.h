#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>

class HeapSort
{
private:
    int heapsize;
    std::vector<int>& arr;
public:
    HeapSort(std::vector<int>& inputArr) : arr(inputArr) {
        heapsize = arr.size();
    }

    int parent(int i){
        return (i - 1) / 2;
    }

    int left(int i){
        return 2 * i + 1;
    }

    int right(int i){
     return 2 * i + 2;
    }

    void sort() {
        buildMaxHeap();
        for(int i = heapsize - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            --heapsize;
            maxHeapify(0);
        }
    }

    void maxHeapify(int i){
        int l = left(i);
        int r = right(i);
        int largest = i;

        if(l < heapsize && arr[l] > arr[i]){
            largest = l;
        }
        if(r < heapsize && arr[r] > arr[largest]) {
            largest = r;
        }
        if(largest != i){
            std::swap(arr[i], arr[largest]);
            maxHeapify(largest);
        }

    }
    void buildMaxHeap() {
        for(int i = heapsize / 2 - 1; i >= 0; --i){
            maxHeapify(i);
        }
    }
    


};

#endif