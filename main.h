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
    double prob;    // A frequency of use for the symbol.
    std::string code;   // Binary code word created by this program.
    std::string codeSecured;    // The same binary code secure by Even Parity.
};

#endif // MAIN_H
