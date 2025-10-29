//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;




struct MinHeap {
    int data[64]; // the array that holds the min heap
    int size;     // this is the number of current elements in the heap

    MinHeap() { size = 0; } // constructor for the heap, init size to 0

private:
    int getParentIndex(int childIndex) { return (childIndex-1) / 2; };
    int getLeftChildIndex(int parentIndex) { return (parentIndex * 2) + 1; }
    int getRightChildIndex(int parentIndex) { return (parentIndex * 2) + 2; }

    bool hasParent(int index) { return getParentIndex(index) >= 0; }
    bool hasLeftChild(int index) { return getLeftChildIndex(index) < size; }
    bool hasRightChild(int index) { return getRightChildIndex(index) < size; }




public:
    int peek() {
        if (size == 0) { return -1; }
        return data[0];
    }

    // add the new element to heap index
    // 3(a) -> +1(b) -> 3(a),1(b) -> 1(b),3(a) ...
    void push(int idx, int weightArr[]) {
        data[size] = weightArr[idx]; // update the heaps data at the next free index with the combined weight/frequency at the current given index
        upheap(size, weightArr); // compair with parents until min heap is restored
        size++; // increment the size
    }

    // remove the root element and replace it with the last element
    int pop(int weightArr[]) {
        int temp = data[0]; // store the first value in data in a temp var
        data[0] = data[size]; // move the last element to the first element's spot
        downheap(0, weightArr); // move the element down until min heap it restored
        size--; // decrement the count
        return temp; // return the temp that holds the old first value
    }

    // take in the position of the newest element and the weight array
    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while less than all parents
        // pos is the size of the heap
        // weightArr[] is the combined weights/frequencies of the letters in the message
        // we need to move the newly added element to the up the heap until min heap is restored
        //    3(a)
        //    /  \
        //  1(b)   <--- while case
        //
        //    1(b)
        //    /  \
        //  3(a)
        //
        //    1(b)
        //    /  \
        //  3(a) 2(n)

        while (hasParent(data[pos]) && data[pos] < data[getParentIndex(pos)]) {
            // the node has a parent AND its parent is greater than it, swap
            int temp = data[getParentIndex(pos)]; // create a temp var to hold the parent node
            data[getParentIndex(pos)] = data[pos]; // move the value of the current element to its parents location
            data[pos] = temp; // move the parent elements value to the current nodes position
        }
    }

    // the last element was just moved to the top, we need to check and move it down
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        // pos is the first element in data

        // while the parent is greater than the child, swap
        while (hasLeftChild(pos)) {
            if (hasLeftChild(pos)) {
                
            }
        }
    }
};

#endif