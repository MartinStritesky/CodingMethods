#include "main.h"
#include "codingMethods.h"

#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <map>


using namespace std;
/*!
 * \brief setUpAlphabet Initial method to calculate average information quantity and information per symbol.
 * \param alp Struct representing the symbol array 10 long.
 * \param size
 * \param avgInfoQty  A number calculated as sum of p(i) * log2(p(i)) through the array.
 * \param infoQty  A number calculated as - log2(p(i)) for particular symbol.
 */
void setUpAlphabet(SymbolProb alp[], int size, double avgInfoQty, double infoQty[]){

    double soucetProb;   // number used to verify that sum of probabilities is 100%
    soucetProb = 0;
    avgInfoQty = 0;

    for (int i = 0; i < size; i++){
        soucetProb += alp[i].prob;
        avgInfoQty += alp[i].prob * log2(1/alp[i].prob);  // Calculation of average  information quantity of the alphabet.
        infoQty[i] = - log2(alp[i].prob);  // Calculation of information quantity per symbol.
    }

    if (round(10 * soucetProb) != 10.0){
        cout << "Probability sum is not 100%! It is " << (100*soucetProb);
        return;  // exits the programme if sum of probabilities is not 100%.
    }
}

/*!
 * \brief sortDesc Method sorting array of SymbolProb by probability in descending order.
 * \param alp SymbolProb struct object containing symbols, probabilities and code words.
 * \param size
 */
void sortDesc(SymbolProb alp[], int size){

    for (int j = 0; j < size -1; j++){
        for (int i = 0; i < size - j -1 ; i++){
            double tmp;  // Temporary variable to hold a value during swapping.
            char temp;   // Temporary variable to hold a value during swapping.
            if (alp[i].prob < alp[i+1].prob){
                tmp = alp[i].prob;
                temp = alp[i].symbol;
                alp[i].prob = alp[i+1].prob;
                alp[i].symbol = alp[i+1].symbol;
                alp[i+1].prob = tmp;
                alp[i+1].symbol = temp;
            }
        }
    }
}

/*!
 * \brief sortAsc Method sorting array of SymbolProb by probability in ascending order.
 * \param alp SymbolProb struct object containing symbols, probabilities and code words.
 * \param size
 */
void sortAsc(SymbolProb alp[], int size){

    for (int j = 0; j < size -1; j++){
        for (int i = 0; i < size - j -1 ; i++){
            double tmp;     // Temporary variable to hold a value during swapping.
            char temp;       // Temporary variable to hold a value during swapping.
            if (alp[i].prob > alp[i+1].prob){
                tmp = alp[i].prob;
                temp = alp[i].symbol;
                alp[i].prob = alp[i+1].prob;
                alp[i].symbol = alp[i+1].symbol;
                alp[i+1].prob = tmp;
                alp[i+1].symbol = temp;
            }
        }
    }
}

/*!
 * \brief sortBack Method sorting array of SymbolProb by symbols in ascending order.
 * \param alp SymbolProb struct object containing symbols, probabilities and code words.
 * \param size
 */
void sortBack (SymbolProb alp[], int size){
    for (int i = 0; i < size -1; i++){
        for (int j = 0; j < size - i - 1; j++){
            double tmpProb;  // Temporary variable to hold a value during swapping.
            char tmpChar;    // Temporary variable to hold a value during swapping.
            std::string tmpStr;  // Temporary variable to hold a value during swapping.
            if (alp[j].symbol > alp[j+1].symbol){
                tmpChar = alp[j].symbol;
                tmpProb = alp[j].prob;
                tmpStr = alp[j].code;
                alp[j].symbol = alp[j+1].symbol;
                alp[j].code = alp[j+1].code;
                alp[j].prob = alp[j+1].prob;
                alp[j+1].symbol = tmpChar;
                alp[j+1].code = tmpStr;
                alp[j+1].prob = tmpProb;
            }
        }
    }

}
/*!
 * \brief ShannonFan Method generating binary code words using Shannon-Fano algorithm.
 * \param alp SymbolProb struct object containing symbols, probabilities and code words. Hete this method fills property ".code" with binary code words.
 * \param size
 */
void ShannonFan(SymbolProb alp[], int size){

    sortDesc(alp,size);  // sort the array of struct to desceding order.

    std::function<void(int, int, double)> divideProb = [&](int start, int end, double probSum) { // recursive function to determine dividing index at current array of symbols and assigning '0! or '1'
        if (start == end) {  // if the array is of one member the algorithm is at the end
            return;
        }

        double firstProb = alp[start].prob;  // defining the first divided half based on probability sum
        double secondProb = probSum - firstProb;  // defining the second divided half based on probability sum
        int divIndex = start; // initialization of dividing index at the beginning
        double originalDiff = std::abs(firstProb-secondProb);  // initialization of default difference between first array member and sum of the rest probabilities

        for (int i = start +1 ; i <= end ; i++){  // iterating through the section of array symbols
                firstProb += alp[i].prob; // adding probabilities together
                secondProb = probSum - firstProb;  // updating the probability sum of second half
                double diff = std::abs(firstProb-secondProb);  // getting the current differente between first and second half

                if (diff < originalDiff){  // in case the current difference is smaller that the defautl one, update dividing index to current iteration index
                    divIndex = i;
                    originalDiff = diff; // update the default difference
                    break;
                }
        }

        for (int i = start; i <= divIndex; i++) {  // assign '1' to all members from the first half
            alp[i].code += "1";
        }
        for (int i = divIndex + 1; i <= end; i++) {  // assign '0' ti all member from the second half
            alp[i].code += "0";
        }
        divideProb(start, divIndex, firstProb);   // recursively call the function to its first half
        divideProb(divIndex+1,end, probSum - firstProb); // recursively call the function to its second half

    };

    divideProb(0, size -1, 1.0);  // first calling of the recursive function
    sortBack(alp, size);    // sorting the alphabet to its original state - by symbol characters
 };

/*!
  * \brief Huffman Method generating binary code words using HUffman´s algorithm.
  * \param alp SymbolProb struct object containing symbols, probabilities and code words. Here this method fills property ".code" with binary code words.
  * \param size
  */
 void Huffman(SymbolProb alp[], int size){


    vector<Node*> nodes;  // creating the initial list of nodes held in Vector
    for (int i = 0; i < size; i++) {
        nodes.push_back(new Node(alp[i].prob, i));  // using vector method pushback to create nodes from the current array of probabilities, indexing
    }

    while (nodes.size() > 1) {
        Node* min1 = nodes[0];   // initial min1 node
        int minIndex1 = 0;         // initial min1 index
        Node* min2 = nodes[1];   // initial min2 node
        int minIndex2 = 1;      // initial min2 index
        if (min1->prob > min2->prob) {
            swap(min1, min2);
            swap(minIndex1, minIndex2); // getting both nodes and indexes 0 and 1 sorted
        }
        for (int i = 2; i < nodes.size(); i++) {
            Node* node = nodes[i];   // defining new node of current node to allow comparation
            if (node->prob < min1->prob) {
                min2 = min1;
                minIndex2 = minIndex1;
                min1 = node;
                minIndex1 = i;
            } else if (node->prob < min2->prob) {
                min2 = node;
                minIndex2 = i;      // if current node from original array has lower probability than min 1 or min 2 node, its swaps them
            }
        }

        Node* combined = new Node(min1->prob + min2->prob, -1);     //node node combined from both lowest nodes
        nodes.erase(nodes.begin() + max(minIndex1, minIndex2));     //erasing first node that went into combination
        nodes.erase(nodes.begin() + min(minIndex1, minIndex2));     //erasing second node that went into combination
        nodes.push_back(combined);      //attaching the combined node at the end of nodes

        if (minIndex1 < minIndex2) {  // setting the left and right pointes in nodes based on where the first and second minimum is
            combined->left = min1;
            combined->right = min2;
        } else {
            combined->left = min2;
            combined->right = min1;
        }
    }

    string code = "";  // initialization of code word
    generateCodeWords(nodes[0], code, alp, size);  // calling method that rercurdsively calls itself and generates either 0 or 1 to the code word

    delete nodes[0];  // free memory after nodes

 }

 /*!
 * \brief generateCodeWords  Recursive method generating actual code words from the Huffman´s method.
 * \param node Actual node correnponding with index of original alphabet array alp
 * \param code A code word generated till now.
 * \param alp  Original alphabet array.
 * \param size
 */
void generateCodeWords(Node* node, string code, SymbolProb alp[], int size) {
    if (node == NULL) {
    return;
    }
    if (node->index != -1) { // if the node index is not -1 (pointing to combined node), assign code word to the code words array of SymbolProb alp[]
    alp[node->index].code = code;
    }
    generateCodeWords(node->left, code + "0", alp, size); // recursive calling with the left pointer and assigning '0'
    generateCodeWords(node->right, code + "1", alp, size); // recursive calling with the right pointer and assigning '1'
}

/*!
 * \brief secureEven Method securing created vinary code words of alphabet by Even Parity.
 * \param alp  SymbolProb struct object containing symbols, probabilities and code words.
 * \param size
 */
void secureEven(SymbolProb alp[], int size){

    int count = 0; // counting number of '1's
    for (int i = 0; i < size; i++){ // iterating through all code words
        for (int j = 0; j < alp[i].code.length(); j++){  // iterating through all code word characters
            if(alp[i].code[j] == '1') count ++;
        }
        if (count % 2 == 0) alp[i].codeSecured = alp[i].code + '0'; // if the number of '1's is even, add '0'
        else alp[i].codeSecured = alp[i].code + '1';   // if it is odd, add '1'
        count = 0; //resetting the counter
    }
}

















