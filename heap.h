//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

/*
         *      BANANA
         *      [a(3), b(1), n(2)]
         *  ===================
         *      a(3)
         *=======================
         *      a(3)
         *      /
         *    b(1)
         *========================
         *      b(1)
         *      /
         *    a(3)
         *========================
         *      b(1)
         *      /  \
         *    a(3) n(2)
         *=========================
         *    b(1)
         *
         *      n(2)
         *      /
         *    a(3)
         *============================
         *    b(1), n(2) = (3)
         *                 / \
         *              b(1) n(2)
         *=============================
         *         a(3)
         *         /
         *       (3)
         *       / \
         *    b(1) n(2)2
         * ============================
         *       a(3), (3)    =    (6)
         *             / \         / \
         *          b(1) n(2)   a(3) (3)
         *                           / \
         *                        b(1) n(2)
         *=============================
        *                 (6)
         *                / \
         *             a(3) (3)
         *                  / \
         *               b(1) n(2)
         *
         *  data stores the indices of
         */


struct MinHeap {
    int data[64]; // the indices into weightArr[]
    int size;     // this is the number of current elements in the heap

    MinHeap() { size = 0; } // constructor for the heap, init size to 0

private:
    int getParentOf(int childIndex) { return (childIndex-1) / 2; };
    int getLeftChildOf(int parentIndex) { return (parentIndex * 2) + 1; }
    int getRightChildOf(int parentIndex) { return (parentIndex * 2) + 2; }

    bool hasParent(int index) { return getParentOf(index) >= 0; }
    bool hasLeftChild(int index) { return getLeftChildOf(index) < size; }
    bool hasRightChild(int index) { return getRightChildOf(index) < size; }

public:
    int peek() {
        if (size == 0) { return -1; }
        return data[0]; // index of smallest weight node
    }

    // add the new element to heap index
    // 3(a) -> +1(b) -> 3(a),1(b) -> 1(b),3(a) ...
    void push(int idx, int weightArr[]) {
        data[size] = idx; // store the nodes index
        upheap(size, weightArr); // move element up, restore min heap
        size++; // increment the size
    }

    // remove the root element and replace it with the last element
    int pop(int weightArr[]) {
        if (size == 0) { return -1; } // null check
        int minIndex = data[0];       // index of the smallest node
        data[0] = data[size - 1];     // move last index to top
        size--; // decrement the size
        downheap(0, weightArr);   // restore heap property
        return minIndex; // return the minIndex
    }

    // take in the index of the newest element and the weight array
    void upheap(int pos, int weightArr[]) {
        // while the element has a parent AND the weight of that element is less than the weight if that elements parent
        while (hasParent(pos) && weightArr[data[pos]] < weightArr[data[getParentOf(pos)]]) {
            swap(data[pos], data[getParentOf(pos)]); // swap the values of the indices in data
            pos = getParentOf(pos); // move the position to the parent, it follows the element that we added
        }
    }

    // the last element was just moved to the top, we need to check and move it down
    void downheap(int pos, int weightArr[]) {
        // the init pos is 0, we then need to check if it has sub nodes
        while (hasLeftChild(pos)) {
            int smallerChild = getLeftChildOf(pos); // initially make the smaller child the left one
            // check if there is a right child
            if ()

        }
    }

};

#endif