#ifndef MAIN_H
#define MAIN_H

#include <string>


/*!
 * \brief The SymbolProb struct
 *
 * A struct defining important properties of each symbol from the 10 symbol alphabet.
 */

struct SymbolProb {
    char symbol;   // An actual symbol of the alphabet.
    double prob;
    double infoQty;                // A frequency of use for the symbol.
    std::string codeSF;           // Binary code word created by this program.
    std::string codeHuff;   // Binary code word created by this program.
    std::string codeSecured;    // The Huffman binary code secured by Even Parity.
};

class Widget;

//void changeProb(double newProb[], Widget  *w);

//! Method that created code words, calculates quantum of information and secures the code by Even parity.
void encode(SymbolProb alp[], int size , double *avgInfoQty, double *avgWordLengthSF, double *avgWordLengthHuff, double *entrophy);


#endif // MAIN_H
