#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <chrono>
#include <fstream>
#include <vector>
#include "HeapSort.h"
#include "InsertionSort.h"


using namespace std;

std::vector<int> randomArray(int size)
{
    srand(time(NULL));

    std::vector<int> arr(size);

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;
    }

    return arr;
}

std::vector<int> sortedArray(int size)
{
    std::vector<int> arr(size); 
    for (int i = 0; i < size; ++i) {
        arr[i] = i; 
    }

    return arr;
}

/**************************************/


int main(){

    

    int size;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    //outdata is like cin
    ofstream outdata;

    //opens file
    outdata.open("data.txt");

    outdata << "Last Run: " << __DATE__ << ", " << __TIME__ << "\n" << endl;

    cout << "Enter Size for random/sorted Array: " << endl;
    cin >> size;
   
    for(int i = 0; i < 5; i++){


        /************************INSERTION RANDOM**********************************************/
    
        outdata << "\nRandom Array Size for Insertion Sort: " << size << endl;

        std::vector<int> ranArray = randomArray(size);

        InsertionSort insertionSort(ranArray);

        auto t1 = high_resolution_clock::now();
        insertionSort.sort();
        auto t2 = high_resolution_clock::now();

        auto millisecRan = duration_cast<milliseconds>(t2 - t1);
        outdata << "Milliseconds it took for Insertion Sort: " << millisecRan.count() << endl;

        outdata << "\n**************************END OF RANDOM " << size << " ARRAY*********************************************" << endl;

        /***************************INSERTION SORTED*******************************************/

        outdata << "\nSorted Array Size for Insertion Sort: " << size << endl;
        
        std::vector<int> sortArray = sortedArray(size);

        InsertionSort insertionSort2(sortArray);

        auto t3 = high_resolution_clock::now();
        insertionSort2.sort();
        auto t4 = high_resolution_clock::now();

        auto millisecSort = duration_cast<milliseconds>(t4 - t3);
        outdata << "Milliseconds it took for Insertion Sort: " << millisecSort.count() << endl;

        outdata << "\n**************************END OF SORT " << size << " ARRAY*********************************************" << endl;

        /***************************HEAP RANDOM*******************************************/

        outdata << "\nRandom Array Size for Heap Sort: " << size << endl;

        std::vector<int> ranArray2 = randomArray(size);
        
        HeapSort heapSort(ranArray2);

        auto t5 = high_resolution_clock::now();
        heapSort.sort();
        auto t6 = high_resolution_clock::now();

        auto millisecRan2 = duration_cast<milliseconds>(t6 - t5);
        outdata << "Milliseconds it took for Heap Sort: " << millisecRan2.count() << endl;

        outdata << "\n**************************END OF RANDOM " << size << " ARRAY*********************************************" << endl;


        /***************************HEAP SORTED*******************************************/

        outdata << "\nSorted Array Size for Heap Sort: " << size << endl;

        std::vector<int> sortArray2 = sortedArray(size);
        
        
        HeapSort heapSort2(sortArray2);

        auto t7 = high_resolution_clock::now();
        heapSort2.sort();
        auto t8 = high_resolution_clock::now();

        auto millisecSort2 = duration_cast<milliseconds>(t8 - t7);
        outdata << "Milliseconds it took for Heap Sort: " << millisecSort2.count() << endl;

        outdata << "\n**************************END OF SORTED " << size << " ARRAY*********************************************" << endl;

        /***UPDATE SIZE***/
        size = 100000 + size;    
    }
    
    outdata.close();

    return 0;

}