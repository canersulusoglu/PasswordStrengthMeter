#include <QDebug>
#include <string>
#include "alphabet.h"
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

class PasswordGenerator
{
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
public:
    PasswordGenerator(Alphabet* alphabet);
    ~PasswordGenerator();

    string GenerateRandomPassword(int numberOfLetters);
    PasswordStrengthValues calculatePasswordStrength(string password);
    void printPasswordStrengthValues(PasswordStrengthValues values);
    int getPasswordScore(PasswordStrengthValues values);
};

#endif // PASSWORDGENERATOR_H
