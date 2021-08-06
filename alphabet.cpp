#include "alphabet.h"

Alphabet::Alphabet(AlphabetName alphabetName){
    switch (alphabetName){
        case AlphabetName::Latin:
            this->alphabetName = AlphabetName::Latin;
            this->UpperCaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            this->LowerCaseLetters = "abcdefghıjklmnopqrstuvwxyz";
            this->Numbers = "1234567890";
            this->Symbols = "!#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~";
            break;
        default:
            throw "You need to declare CustomAlphabet!";
            break;
    }
};

Alphabet::Alphabet(CustomAlphabet customAlphabet){
    this->alphabetName = AlphabetName::Custom;
    this->UpperCaseLetters = customAlphabet.UpperCaseLetters;
    this->LowerCaseLetters = customAlphabet.LowerCaseLetters;
    this->Numbers = customAlphabet.Numbers;
    this->Symbols = customAlphabet.Symbols;
}

AlphabetName Alphabet::getAlphabetName(){
    return this->alphabetName;
}

string Alphabet::getUpperCaseLetters(){
    return this->UpperCaseLetters;
}

string Alphabet::getLowerCaseLetters(){
    return this->LowerCaseLetters;
}

string Alphabet::getNumbers(){
    return this->Numbers;
}

string Alphabet::getSymbols(){
    return this->Symbols;
}
