#include <string>
using namespace std;
#ifndef ALPHABET_H
#define ALPHABET_H

enum AlphabetName {
    Custom,
    Latin
};

struct CustomAlphabet{
    string UpperCaseLetters;
    string LowerCaseLetters;
    string Numbers;
    string Symbols;
};

class Alphabet{
private:
    AlphabetName alphabetName;
    string UpperCaseLetters;
    string LowerCaseLetters;
    string Numbers;
    string Symbols;
public:
    Alphabet(AlphabetName alphabetName);
    Alphabet(CustomAlphabet customAlphabet);
    AlphabetName getAlphabetName();
    string getUpperCaseLetters();
    string getLowerCaseLetters();
    string getNumbers();
    string getSymbols();
};

#endif // ALPHABET_H
