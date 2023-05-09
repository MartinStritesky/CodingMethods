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
    std::string codeSF;
    std::string codeHuff;   // Binary code word created by this program.
    std::string codeSecured;    // The same binary code secure by Even Parity.
};

class Widget;

void changeProb(double newProb[], Widget  *w);
void encode(SymbolProb alp[], int size , double *avgInfoQty, double *avgWordLengthSF, double *avgWordLengthHuff, double *entrophy);


#endif // MAIN_H
