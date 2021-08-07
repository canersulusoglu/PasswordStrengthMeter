#include <QDebug>
#include <string>
#include <algorithm>
#ifndef ALPHABET_H
#include "alphabet.h"
#endif
using namespace std;

#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

struct State{
    int Count;
    int Score;
};

struct PasswordStrengthValues{
    State numberOfCharacters;
    State upperCaseLetters;
    State lowerCaseLetters;
    State numbers;
    State symbols;
    State middleNumbersOrSymbols;
    State minimumRequirements;
    State lettersOnly;
    State numbersOnly;
    State repeatCharacters;
    State consecutiveUppercaseLetters;
    State consecutiveLowercaseLetters;
    State consecutiveNumbers;
    State sequentialLetters;
    State sequentialNumbers;
    State sequentialSymbols;
};

class PasswordGenerator{
protected:
    PasswordGenerator(Alphabet* alphabet);
    ~PasswordGenerator();
    static PasswordGenerator* instance;
public:
    PasswordGenerator(PasswordGenerator &other) = delete;
    void operator=(const PasswordGenerator &) = delete;
    static PasswordGenerator *GetInstance(Alphabet* alphabet = new Alphabet(AlphabetName::Latin));

    void setAlphabet(Alphabet* alphabet);
    Alphabet* getAlphabet();
    string GenerateRandomPassword(int numberOfLetters = 8);
    PasswordStrengthValues calculatePasswordStrength(string password);
    void printPasswordStrengthValues(PasswordStrengthValues values);
    int getPasswordScore(PasswordStrengthValues values);
private:
    Alphabet* alphabet;
    bool isLetter(char character);
    bool isUpperCaseLetter(char character);
    bool isLowerCaseLetter(char character);
    bool isNumber(char character);
    bool isSymbol(char character);
    int generateRandomNumber(int start, int end);
    char selectRandomUpperCaseLetterFromAlphabet();
    char selectRandomLowerCaseLetterFromAlphabet();
    char selectRandomNumberFromAlphabet();
    char selectRandomSymbolFromAlphabet();
};

#endif // PASSWORDGENERATOR_H
