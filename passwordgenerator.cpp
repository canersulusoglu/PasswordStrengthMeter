#include "passwordgenerator.h"

PasswordGenerator::PasswordGenerator(Alphabet* alphabet)
{
    this->alphabet = alphabet;
}


PasswordGenerator::~PasswordGenerator(){
    delete alphabet;
}

bool PasswordGenerator::isLetter(char character){
    if (isalpha(character)) {
        return true;
    }
    return false;
}

bool PasswordGenerator::isUpperCaseLetter(char character){
    if (isupper(character)) {
        return true;
    }
    return false;
}

bool PasswordGenerator::isLowerCaseLetter(char character){
    if (islower(character)) {
        return true;
    }
    return false;
}

bool PasswordGenerator::isNumber(char character){
    if (isdigit(character)) {
        return true;
    }
    return false;
}

bool PasswordGenerator::isSymbol(char character){
    if (!isalpha(character) && !isdigit(character) && !isspace(character)) {
        return true;
    }
    return false;
}

int PasswordGenerator::generateRandomNumber(int start, int end){
    return (int)((rand() % (end - start)) + start);
}

char PasswordGenerator::selectRandomUpperCaseLetterFromAlphabet(){
    string letters = alphabet->getUpperCaseLetters();
    if (letters.length() > 0) {
        int randomNumber = this->generateRandomNumber(0, letters.length());
        return letters[randomNumber];
    }
    return NULL;
}

char PasswordGenerator::selectRandomLowerCaseLetterFromAlphabet(){
    string letters = alphabet->getLowerCaseLetters();
    if (letters.length() > 0) {
        int randomNumber = this->generateRandomNumber(0, letters.length());
        return letters[randomNumber];
    }
    return NULL;
}

char PasswordGenerator::selectRandomNumberFromAlphabet(){
    string numbers = alphabet->getNumbers();
    if (numbers.length() > 0) {
        int randomNumber = this->generateRandomNumber(0, numbers.length());
        return numbers[randomNumber];
    }
    return NULL;
}

char PasswordGenerator::selectRandomSymbolFromAlphabet(){
    string symbols = alphabet->getSymbols();
    if (symbols.length() > 0) {
        int randomNumber = this->generateRandomNumber(0, symbols.length());
        return symbols[randomNumber];
    }
    return NULL;
}

string PasswordGenerator::GenerateRandomPassword(int numberOfLetters){
    string result;
    while (numberOfLetters != 0)
    {
        int randomNumber = this->generateRandomNumber(0, 4);
        switch (randomNumber)
        {
            case 0:
                result += this->selectRandomUpperCaseLetterFromAlphabet();
                break;
            case 1:
                result += this->selectRandomLowerCaseLetterFromAlphabet();
                break;
            case 2:
                result += this->selectRandomNumberFromAlphabet();
                break;
            case 3:
                result += this->selectRandomSymbolFromAlphabet();
                break;
        default:
            break;
        }
        numberOfLetters--;
    }
    return result;
};

PasswordStrengthValues PasswordGenerator::calculatePasswordStrength(string password){
    PasswordStrengthValues result = {
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0},
        State {0 ,0}
    };

    int passwordLength = password.length();

    result.numberOfCharacters.Count = passwordLength;
    result.numberOfCharacters.Score = passwordLength * 4;

    bool haveUpperCaseLetter = false;
    bool haveLowerCaseLetter = false;
    bool haveNumber = false;
    bool haveSymbol = false;
    bool isMinimum8Character = (passwordLength >= 8) ? true : false;
    bool isLetterOnly = false;
    bool isNumbersOnly = false;
    for (int i = 0; i < passwordLength; i++)
    {
        if(isUpperCaseLetter(password[i])){
            result.upperCaseLetters.Count++;
            if(!haveUpperCaseLetter){
                result.minimumRequirements.Count++;
                haveUpperCaseLetter = true;
            }
        }
        if(isLowerCaseLetter(password[i])){
            result.lowerCaseLetters.Count++;
            if(!haveLowerCaseLetter){
                result.minimumRequirements.Count++;
                haveLowerCaseLetter = true;
            }
        }
        if(isNumber(password[i])){
            result.numbers.Count++;
            if(!haveNumber){
                result.minimumRequirements.Count++;
                haveNumber = true;
            }
        }
        if(isSymbol(password[i])){
            result.symbols.Count++;
            if(!haveSymbol){
                result.minimumRequirements.Count++;
                haveSymbol = true;
            }
        }
        if (i != 0 && i != (passwordLength - 1)) {
            if (isNumber(password[i]) || isSymbol(password[i])) {
                result.middleNumbersOrSymbols.Count++;
            }
        }

        if(isLetter(password[i])){
            result.lettersOnly.Count++;
            if(result.lettersOnly.Count == passwordLength){
                isLetterOnly = true;
            }
        }
        if(isNumber(password[i])){
            result.numbersOnly.Count++;
            if(result.numbersOnly.Count == passwordLength){
                isNumbersOnly = true;
            }
        }

        for(int j = (i + 1); j < passwordLength; j++){
            if(password[i] == password[j]){
                result.repeatCharacters.Count++;
                break;
            }
        }

        if ((i + 1) < passwordLength) {

            if(isUpperCaseLetter(password[i]) && isUpperCaseLetter(password[i+1])){
                result.consecutiveUppercaseLetters.Count++;
            }

            if(isLowerCaseLetter(password[i]) && isLowerCaseLetter(password[i+1])){
                result.consecutiveLowercaseLetters.Count++;
            }

            if(isNumber(password[i]) && isNumber(password[i+1])){
                result.consecutiveNumbers.Count++;
            }
        }

        if ((i+1) < passwordLength && (i+2) < passwordLength) {
            if (isLetter(password[i]) && isLetter(password[i+1]) && isLetter(password[i+2])) {
                if (int(password[i]) == int(password[i+1]) -1 && int(password[i+1]) == int(password[i+2]) - 1) {
                    result.sequentialLetters.Count++;
                }
            }

            if (isNumber(password[i]) && isNumber(password[i + 1]) && isNumber(password[i+2])) {
                if (int(password[i]) == int(password[i + 1]) - 1 && int(password[i + 1]) == int(password[i + 2]) - 1) {
                    result.sequentialNumbers.Count++;
                }
            }

            if (isSymbol(password[i]) && isSymbol(password[i + 1]) && isSymbol(password[i+2])) {
                if (int(password[i]) == int(password[i + 1]) - 1 && int(password[i + 1]) == int(password[i + 2]) - 1) {
                    result.sequentialSymbols.Count++;
                }
            }
        }
    }

    result.numbers.Score = result.numbers.Count * 4;
    if (result.upperCaseLetters.Count > 0 && (result.lowerCaseLetters.Count > 0 || result.numbers.Count > 0 || result.symbols.Count > 0))
            result.upperCaseLetters.Score = (passwordLength - result.upperCaseLetters.Count) * 2;
    if (result.lowerCaseLetters.Count > 0 && (result.upperCaseLetters.Count > 0 || result.numbers.Count > 0 || result.symbols.Count > 0))
            result.lowerCaseLetters.Score = (passwordLength - result.lowerCaseLetters.Count) * 2;
    if (result.lowerCaseLetters.Count > 0 || result.upperCaseLetters.Count > 0 || result.symbols.Count > 0)
            result.numbers.Score = result.numbers.Count * 4;
    result.symbols.Score = result.symbols.Count * 6;
    result.middleNumbersOrSymbols.Score = result.middleNumbersOrSymbols.Count * 2;
    if (isMinimum8Character){
        result.minimumRequirements.Count++;
        result.minimumRequirements.Score += 2;
        if (haveUpperCaseLetter)
            result.minimumRequirements.Score += 2;
        if (haveLowerCaseLetter)
            result.minimumRequirements.Score += 2;
        if (haveNumber)
            result.minimumRequirements.Score += 2;
        if (haveSymbol)
            result.minimumRequirements.Score += 2;
        if(result.minimumRequirements.Count < 4)
            result.minimumRequirements.Score = 0;
    }else{
        result.minimumRequirements.Score = 0;
    }

    if(isLetterOnly){
        result.lettersOnly.Score -= result.lettersOnly.Count;
    }else{
        result.lettersOnly.Score = 0;
        result.lettersOnly.Count = 0;
    }
    if(isNumbersOnly){
        result.numbersOnly.Score -= result.numbersOnly.Count;
    }else{
        result.numbersOnly.Score = 0;
        result.numbersOnly.Count = 0;
    }
    result.repeatCharacters.Score -= result.repeatCharacters.Count * (result.repeatCharacters.Count - 1);
    result.consecutiveUppercaseLetters.Score -= result.consecutiveUppercaseLetters.Count * 2;
    result.consecutiveLowercaseLetters.Score -= result.consecutiveLowercaseLetters.Count * 2;
    result.consecutiveNumbers.Score -= result.consecutiveNumbers.Count * 2;
    result.sequentialLetters.Score -= result.sequentialLetters.Count * 3;
    result.sequentialNumbers.Score -= result.sequentialNumbers.Count * 3;
    result.sequentialSymbols.Score -= result.sequentialSymbols.Count * 3;

    return result;
}

int PasswordGenerator::getPasswordScore(PasswordStrengthValues values){
    int totalScore = 0;

    totalScore += values.numberOfCharacters.Score;
    totalScore += values.upperCaseLetters.Score;
    totalScore += values.lowerCaseLetters.Score;
    totalScore += values.numbers.Score;
    totalScore += values.symbols.Score;
    totalScore += values.middleNumbersOrSymbols.Score;
    totalScore += values.minimumRequirements.Score;
    totalScore += values.lettersOnly.Score;
    totalScore += values.numbersOnly.Score;
    totalScore += values.repeatCharacters.Score;
    totalScore += values.consecutiveUppercaseLetters.Score;
    totalScore += values.consecutiveLowercaseLetters.Score;
    totalScore += values.consecutiveNumbers.Score;
    totalScore += values.sequentialLetters.Score;
    totalScore += values.sequentialNumbers.Score;
    totalScore += values.sequentialSymbols.Score;

    return totalScore;
}

void PasswordGenerator::printPasswordStrengthValues(PasswordStrengthValues values){
    qInfo() << "numberOfCharactes: Count(" << values.numberOfCharacters.Count << ") Score(" << values.numberOfCharacters.Score << ")";
    qInfo() << "upperCaseLetters: Count(" << values.upperCaseLetters.Count << ") Score(" << values.upperCaseLetters.Score << ")";
    qInfo() << "lowerCaseLetters: Count(" << values.lowerCaseLetters.Count << ") Score(" << values.lowerCaseLetters.Score << ")";
    qInfo() << "numbers: Count(" << values.numbers.Count << ") Score(" << values.numbers.Score << ")";
    qInfo() << "symbols: Count(" << values.symbols.Count << ") Score(" << values.symbols.Score << ")";
    qInfo() << "middleNumbersOrSymbols: Count(" << values.middleNumbersOrSymbols.Count << ") Score(" << values.middleNumbersOrSymbols.Score << ")";
    qInfo() << "minimumRequirements: Count(" << values.minimumRequirements.Count << ") Score(" << values.minimumRequirements.Score << ")";
    qInfo() << "lettersOnly: Count(" << values.lettersOnly.Count << ") Score(" << values.lettersOnly.Score << ")";
    qInfo() << "numbersOnly: Count(" << values.numbersOnly.Count << ") Score(" << values.numbersOnly.Score << ")";
    qInfo() << "repeatCharacters: Count(" << values.repeatCharacters.Count << ") Score(" << values.repeatCharacters.Score << ")";
    qInfo() << "consecutiveUppercaseLetters: Count(" << values.consecutiveUppercaseLetters.Count << ") Score(" << values.consecutiveUppercaseLetters.Score << ")";
    qInfo() << "consecutiveLowercaseLetters: Count(" << values.consecutiveLowercaseLetters.Count << ") Score(" << values.consecutiveLowercaseLetters.Score << ")";
    qInfo() << "consecutiveNumbers: Count(" << values.consecutiveNumbers.Count << ") Score(" << values.consecutiveNumbers.Score << ")";
    qInfo() << "sequentialLetters: Count(" << values.sequentialLetters.Count << ") Score(" << values.sequentialLetters.Score << ")";
    qInfo() << "sequentialNumbers: Count(" << values.sequentialNumbers.Count << ") Score(" << values.sequentialNumbers.Score << ")";
    qInfo() << "sequentialSymbols: Count(" << values.sequentialSymbols.Count << ") Score(" << values.sequentialSymbols.Score << ")";
}
