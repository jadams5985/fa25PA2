//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64; // constant for the max number of node
int weightArr[MAX_NODES]; // declair an array for the frequencies/combined weights
int leftArr[MAX_NODES];   // array for indices of left children, -1 if leaf
int rightArr[MAX_NODES];  // array for indices of right children, -1 if leaf
char charArr[MAX_NODES];  // array for the characters in the message

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0}; // init an array for the frequencies of the letters in the alphabet to 0

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt"); // updates the frequencies for the letters in the text

    // for (int i = 0; i < 26; i++) {
    //     cout << freq[i] << endl;
    // }
    //
    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // cout << "Root: " << weightArr[root] << endl;

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename); // try to open the file
    if (!file.is_open()) {
        // the file failed to open
        cerr << "Error: could not open " << filename << "\n";
        exit(1); // leave
    }
    // file open was good
    char ch; // make a char var to be used to read in the message and as a temp to converting to lower
    // while there are characters in the file
    while (file.get(ch)) {
        // check for letter
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a'; // normalize to lowercase

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++; // increment the index of the array to correspond to the frequency of the letters in the message
    }
    file.close(); // close the file safely

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character, adds the elements alphabetically to char/weight/left/right
int createLeafNodes(int freq[]) {
    int nextFree = 0; // this is the next available index for charArr, weightArr, left, and right
    // loop for letters a-z
    for (int i = 0; i < 26; ++i) {
        // we will only add the characters (and associated frequencies) to the charArr and weightArr in the order they are encountered
        if (freq[i] > 0) {
            // the current frequency is greater than zero so we add it
            charArr[nextFree] = 'a' + i; // add a-z if the frequency of the char is greater than 0
            weightArr[nextFree] = freq[i]; // the weights correspond to the number of child elements   that element has
            leftArr[nextFree] = -1; // init them all to -1
            rightArr[nextFree] = -1; // init them all to -1
            nextFree++; // increment the next free index
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree; // return the next free index
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    MinHeap minHeap; // Create a MinHeap object.
    // Push all leaf node indices into the heap.
    // runs for all elements we added to weights/chars/lefts/rights
    for (int i = 0; i < nextFree; ++i) {
        minHeap.push(i, weightArr); // call push on minHeap and pass the current index and weightArr
    }

    // 3. While the heap size is greater than 1:
    while (minHeap.getSize() > 1) {
        //    - Pop two smallest nodes
        int firstSmallest = minHeap.pop(weightArr); // take the index of the first smallest weight
        int secondSmallest = minHeap.pop(weightArr); // take the index of the next smallest weight
        //    - Create a new parent node with combined weight
        int parent = nextFree++; // make a parent index to hold the combined weight
        weightArr[parent] = weightArr[firstSmallest] + weightArr[secondSmallest]; // combine the two smallest weights into a singular weight, add it to the end of the weightArr
        //    - Set left/right pointers
        leftArr[parent] = firstSmallest; // set the parent index of the combined weight to the leftArr
        rightArr[parent] = secondSmallest; // set the parent index of the combined weight to the rightArr
        charArr[parent] = '*'; // add a placeholder, p for parent
        //    - Push new parent index back into the heap
        minHeap.push(parent, weightArr); // push the new element to the heap, pass in the weightArr
    }

    // 4. Return the index of the last remaining node (root)
    return minHeap.pop(weightArr); // remove the root weight
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // Use stack<pair<int, string>> to simulate DFS traversal.
    stack<pair<int, string>> stack; // crate a stack that holds pairs of ints and strings, hold the indices of each node and their code
    stack.push({root, ""}); // push the root(the max combined weight with no code), to the stack
    // while there are elements in the stack...
    while (!stack.empty()) {
        auto [node, code] = stack.top(); // create a pair for the index of the element and a string for the code
        stack.pop(); // remove the top element

        // check if it is a leaf
        if (leftArr[node] == -1 && rightArr[node] == -1) {
            codes[charArr[node] - 'a'] = code; // add the code to the codes[] at the index of the node
        }
        // not a leaf, aka has sub nodes
        else {
            // check if the right node is not a leaf
            if (rightArr[node] != -1) {
                stack.push({rightArr[node], code + "1"}); // push it back to the stack with 1 appended to its code
            }
            // check if the left node is not a leaf
            if (leftArr[node] != -1) {
                stack.push({leftArr[node], code + "0"}); // push it back to the stack with 0 appended to its code
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << setw(5) << right << char('a' + i) << setw(7) << ": " << setw(6) << left << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}