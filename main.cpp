#include <QApplication>
#include <cmath>
#include <iostream>
#include <array>
#include <stdlib.h>
#include <QPushButton>
#include <QEventLoop>

#include "main.h"
#include "widget.h"
#include "codingMethods.h"

using namespace std;

SymbolProb alp[10] = {
    {'A'},
    {'B'},
    {'C'},
    {'D'},
    {'E'},
    {'F'},
    {'G'},
    {'H'},
    {'I'},
    {'J'}
};

int bClicked = 0;

double avgWordLengthSF = 0;  // Average length of binary code word from Shannon Fano method.
double avgWordLengthHuff = 0; // Average length of binary code word from Huffman method.
double entrophy = 0;  // Enthrophy of the code.
double avgInfoQty = 0;  // Average quantity of information of the alphabet.

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);   // Initialization of the application.
    Widget w ; // Initialization of new QWidget object
    w.show();

    while(bClicked==0){
        a.processEvents();
    }

    w.getAlp(alp);

    encode(alp, 10, &avgInfoQty, &avgWordLengthSF, &avgWordLengthHuff, &entrophy); // getting average info quantity and code words
    w.addAlphabet(alp,10, &entrophy, &avgWordLengthSF, &avgWordLengthHuff, &avgInfoQty);  // sending all information to be displayed in QWidget

    w.repaint();
    w.update();
    w.show();   // showing the widget

    return a.exec();
}
/*!
 * \brief encode Method that created code words, calculates quantum of information and secures the code by Even parity.
 * \param alp  Array of struct representing alphabet and its coding
 * \param size
 * \param avgInfoQty   Average quantity of information of the alphabet.
 * \param avgWordLengthSF   Average length of binary code word from Shannon Fano method.
 * \param avgWordLengthHuff   Average length of binary code word from Huffman method.
 * \param entrophy   Enthrophy of the code.
 */
void encode(SymbolProb alp[], int size, double *avgInfoQty, double *avgWordLengthSF, double *avgWordLengthHuff, double *entrophy){

    for (int i = 0; i< size; i++){
        *entrophy = *entrophy + abs(alp[i].prob * log2(alp[i].prob));  // Calculating entrophy of the alphabet
    }

    setUpAlphabet(alp, size, avgInfoQty);   // get the average info quantity
    ShannonFan(alp, size, avgWordLengthSF);  // get SF code words
    Huffman(alp, size, avgWordLengthHuff);   // get Huffman code words
    secureEven(alp, size);  // secure the Huffman code words with Even parity

}

//void getProb(SymbolProb alp[], int size){


//}
