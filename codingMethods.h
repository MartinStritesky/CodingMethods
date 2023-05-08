#ifndef CODINGMETHODS_H
#define CODINGMETHODS_H

#include "main.h"
#include <algorithm>

/*!
 * \brief The Node struct
 *
 * A struct used in Huffman's method of creating effective code. It includes use of left and right pointers.
 */
struct Node {
    double prob; // Frequency of use copied from SymbolProb struct.
    int index;  // An index of a node.
    Node *left, *right; // Left and irhgt pointers.
    //! A constructor of Node.
    Node(double p, int i) {
        prob = p;
        index = i;
        left = right = NULL;
    }
    //! A destructor of Node.
    ~Node() {
        delete left;
        delete right;
    }
};

//!  Initial method to calculate average information quantity and information per symbol.
void setUpAlphabet(SymbolProb alp[],int size, double avgInfoQty, double infoQty[]);

//!  Method sorting array of SymbolProb by probability in descending order.
void sortDesc(SymbolProb alp[], int size);

//!  Method sorting array of SymbolProb by probability in ascending order.
void sortAsc(SymbolProb alp[], int size);

//!  Method sorting array of SymbolProb by symbols in ascending order.
void sortBack (SymbolProb alp[], int size);

//! Method generating binary code words using Shannon-Fano algorithm.
void ShannonFan(SymbolProb alp[], int size);

//! Method generating binary code words using HUffman´s algorithm.
void Huffman(SymbolProb alp[], int size);

//! Recursive function inside the ShannonFan method dividing each division further into two halves with simillar probability sums.
std::function<void(int, int, double)> divideProb(int start, int end, double probSum);

//! Method generating actual code words from the Huffman´s method.
void generateCodeWords(Node* node, std::string code, SymbolProb alp[], int size);

//! Method securing created vinary code words of alphabet by Even Parity.
void secureEven(SymbolProb alp[], int size);

#endif // CODINGMETHODS_H
