#include <vector>
#include <iostream>

using namespace std;

class Node {
public:
    int ID;
    int key;

    Node() {}

    Node(int ID, int key) : ID(ID) , key(key) {}
    
    //compareTo() basically7
    bool operator<(const Node& other) const {
        return key < other.key;
    }
};

class Heap
{
protected:
    
    int heapsize;
    vector<Node> heap;
    vector<int> location;

public:
    
    Heap(int maxsize) : heap(maxsize), heapsize(0), location(20) { }

    int parent(int i){
        return (i - 1) / 2;
    }

    int left(int i){
        return 2 * i + 1;
    }

    int right(int i){
     return 2 * i + 2;
    }

    void maxHeapify(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if(l < heapsize && heap[l] < heap[smallest]){
            smallest = l;
        }
        if(r < heapsize && heap[r] < heap[smallest]) {
            smallest = r;
        }
        if(smallest != i){
            swap(heap[i], heap[smallest]);
            swap(location[heap[i].ID], location[heap[smallest].ID]);
            maxHeapify(smallest);
        }

    }
     void sort() {
        buildMaxHeap();
        for(int i = heapsize - 1; i > 0; --i) {
            swap(heap[0], heap[i]);
            --heapsize;
            maxHeapify(0);
        }
    }
    void buildMaxHeap() {
        for(int i = heapsize / 2 - 1; i >= 0; --i){
            maxHeapify(i);
        }
    }
};
            

class PriorityQueue : public Heap {
public:
    PriorityQueue(int maxsize) : Heap(maxsize) {}

    void insert(Node newNode) {

            if (heapsize == heap.size()) {
            cout << "full" << endl;
            return;
        }

        int i = heapsize;
        heap[heapsize] = newNode;
        location[newNode.ID] = heapsize;
        heapsize++;

        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            swap(location[heap[i].ID], location[heap[parent(i)].ID]);
            i = parent(i);
        }
    }

    Node extract() {
        if (heapsize == 0) {
            cout << "empty" << endl;
            return Node(-1, -1);
        }

        Node maxNode = heap[0];
        Node lastNode = heap[heapsize - 1];
        heap[0] = lastNode;
        location[lastNode.ID] = 0;
        heapsize--;
        maxHeapify(0);
        return maxNode;
    }

    void changeKey(int lookID, int newKey) {
        int i = location[lookID];
        if (newKey < heap[i].key) {
            heap[i].key = newKey;

            while (i > 0 && heap[parent(i)] < heap[i]) {
                swap(heap[i], heap[parent(i)]);
                swap(location[heap[i].ID], location[heap[parent(i)].ID]);
                i = parent(i);
            }
        } else if (newKey > heap[i].key) {
            heap[i].key = newKey;
            maxHeapify(i);
        }
    }

    Node peek() {
        return heap[0];
    }
};

int main() {

    int size;
    cout << "Enter Size for Q" << endl;
    cin >> size;

    //INSERT


    PriorityQueue pq = PriorityQueue(size);
    pq.insert( Node(0,3));
    pq.insert( Node(1,14));
    pq.insert( Node(2,7));
    pq.insert( Node(3,9));
    pq.insert( Node(4,99));
    pq.insert( Node(5,2));
    pq.insert( Node(6,46));

    

    // PEEK

    Node pqPeek = pq.peek();
    
    if (pqPeek.ID != -1) {
        cout << "Peeked Node ID: " << pqPeek.ID << " Key: " << pqPeek.key << endl;
    } else {
        cout << "empty" << endl;
    }

    //CHANGE KEY

    pq.changeKey(7,-10);

    Node pqPeek2 = pq.peek();
    
    if (pqPeek2.ID != -1) {
        cout << "Peeked Node ID: " << pqPeek2.ID << " Key: " << pqPeek2.key << endl;
    } else {
        cout << "empty" << endl;
    }

    //EXTRACT THINGS FROM PQ AND SEE WHAT WAS IN IT 

    cout << "Using Extract to see what is in queue as it leaves:" << endl;
    int i = size;
    while (i > 0) {
        Node node = pq.extract();
        cout << "ID: " << node.ID << ", Key: " << node.key << endl;
        i--;
    }


}