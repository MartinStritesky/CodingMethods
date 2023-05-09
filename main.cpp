#include <QApplication>
#include <cmath>
#include <iostream>
#include <array>
#include <stdlib.h>

#include "main.h"
#include "widget.h"
#include "codingMethods.h"


using namespace std;
SymbolProb alp[10] = {
    {'A', 0.10},
    {'B', 0.08},
    {'C', 0.06},
    {'D', 0.03},
    {'E', 0.15},
    {'F', 0.12},
    {'G', 0.04},
    {'H', 0.17},
    {'I', 0.07},
    {'J', 0.18}
};

double avgWordLengthSF = 0;  // Average length of binary code word from Shannon Fano method.
double avgWordLengthHuff = 0; // Average length of binary code word from Huffman method.
double entrophy = 0;  // Enthrophy of the code.
double avgInfoQty = 0;  // Average quantity of information of the alphabet.

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);   // Initialization of the application.


    Widget w ; // Initialization of new QWidget object

    encode(alp, 10, &avgInfoQty, &avgWordLengthSF, &avgWordLengthHuff, &entrophy);


    w.addAlphabet(alp,10, &entrophy, &avgWordLengthSF, &avgWordLengthHuff, &avgInfoQty);  // sending all information to be displayed in QWidget
    w.show();   // showing the widget

    return a.exec();
}

void encode(SymbolProb alp[], int size, double *avgInfoQty, double *avgWordLengthSF, double *avgWordLengthHuff, double *entrophy){

    for (int i = 0; i< size; i++){
        *entrophy = *entrophy + abs(alp[i].prob * log2(alp[i].prob));
    }

    setUpAlphabet(alp, size, avgInfoQty);
    ShannonFan(alp, size, avgWordLengthSF);
    Huffman(alp, size, avgWordLengthHuff);
    secureEven(alp, size);

}

void changeProb(double newProb[], Widget *w){

    for (int i = 0; i < 10; i++){
        alp[i].prob = newProb[i];
        cout << alp[i].prob<< endl;
    }

    encode(alp, 10, &avgInfoQty, &avgWordLengthSF, &avgWordLengthHuff, &entrophy);

    w->addAlphabet(alp,10, &entrophy, &avgWordLengthSF, &avgWordLengthHuff, &avgInfoQty);
    w->repaint();
    w->update();
    w->show();

}
