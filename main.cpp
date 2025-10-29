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

    for (int i = 0; i < 26; i++) {
        cout << freq[i] << endl;
    }

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

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
        minHeap.push(i, weightArr); // call push on minHeap and pass the current index and weightArr[i]
    }
    for (int i = 0; i < nextFree; ++i) {
        cout << minHeap.peek()<< endl;
        minHeap.pop(&weightArr[i]);
    }

    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)
    return -1; // placeholder
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
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