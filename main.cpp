#include <QApplication>
#include <cmath>
#include <iostream>
#include <array>
#include <stdlib.h>

#include "main.h"
#include "widget.h"
#include "codingMethods.h"


using namespace std;

int main(int argc, char *argv[])
{

    double avgWordLength = 0;  // Average length of binary code word from Shannon Fano method.
    double avgWordLengthHuff = 0; // Average length of binary code word from Huffman method.
    double entrophy = 0;  // Enthrophy of the code.
    double avgInfoQty=0;  // Average quantity of information of the alphabet.
    double infoQty[10];     // Information quantity of particular symbol.

    QApplication a(argc, argv);   // Initialization of the application.

    // Initialization of struct array for ShannonFano method
    SymbolProb alpShFan[10] = {
                               {'A', 0.10, "", ""},
                               {'B', 0.08, "", ""},
                               {'C', 0.06, "", ""},
                               {'D', 0.03, "", ""},
                               {'E', 0.15, "", ""},
                               {'F', 0.12, "", ""},
                               {'G', 0.04, "", ""},
                               {'H', 0.17, "", ""},
                               {'I', 0.07, "", ""},
                               {'J', 0.18, "", ""},
                               };
    // Initialization of second struct array for Huffmanns method and copying symbol and probability from the first struct array
    SymbolProb alpHuff[10];
    for(int i = 0; i< 10; i++){
        alpHuff[i].prob = alpShFan[i].prob;
        alpHuff[i].symbol = alpShFan[i].symbol;
    }

    setUpAlphabet(alpShFan, 10, avgInfoQty,infoQty);
    ShannonFan(alpShFan, 10);
    Huffman(alpHuff, 10);

    // Calculating entrophy and average word lengths for Huffman and ShannonFano code words
    for (int i = 0; i< 10; i++){
        avgWordLengthHuff += alpHuff[i].code.length() * alpHuff[i].prob;
        avgWordLength += alpShFan[i].code.length() * alpShFan[i].prob;
        entrophy += abs(alpShFan[i].prob * log2(alpShFan[i].prob));
    }

    secureEven(alpHuff, 10);
    secureEven(alpShFan, 10);

    Widget w; // Initialization of new QWidget object

    w.addAlphabet(alpShFan,alpHuff, 10, entrophy, avgWordLength, avgWordLengthHuff, avgInfoQty, infoQty);  // sending all information to be displayed in QWidget
    w.update(); // updating Widget
    w.show();   // showing the widget

    return a.exec();
}

