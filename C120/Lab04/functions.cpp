# include "functions.h"
# include <string>
#include <iostream>

using std::cout, std::cin, std::endl, std::string;

void deobfuscate() {
    string userString;
    cout << "Please enter obfuscated sentence: ";
    cin >> userString;
    string deobDetails;
    cout << "Please enter deobfuscation details: ";
    cin >> deobDetails;

    int spaceIndex = 0;
    for (unsigned int i = 0; i < deobDetails.length()-1; ++i){
        spaceIndex += static_cast<int>(deobDetails.at(i)) - 48;
        userString.insert(spaceIndex + i, " ");
    }
    
    cout << "Deobfuscated sentence: " << userString << endl;
   

}

void wordFilter() {
    
    string userString;
    cout << "Please enter the sentence: ";
    getline(cin, userString);
    
    string filterWord;
    cout << "Please enter the filter word: ";
    cin >> filterWord;
    string substr;
    
    string censorReplacement = filterWord;
    int fLength = static_cast<int>(filterWord.length());
    censorReplacement.replace(0, fLength, fLength, '#');

    for (unsigned int i = 0; i < userString.length() - 1; ++i){
        substr = userString.substr(i, filterWord.length());
        if (substr == filterWord){
            userString.replace(i, filterWord.length(), censorReplacement);
        }
    }
    cout << "Filtered sentence: " << userString << endl;

}

void passwordConverter() {
    string password;
    cout << "Please enter your text input: ";
    cin >> password;
    char letter;
    for (unsigned int i = 0; i < password.length(); ++i){
        letter = password.at(i);
        switch(letter){
            case 'a':
                password.replace(i, 1, "@");
                break;
            case 'e':
                password.replace(i, 1, "3");
                break;
            case 'i':
                password.replace(i, 1, "!");
                break;
            case 'o':
                password.replace(i, 1, "0");
                break;
            case 'u':
                password.replace(i, 1, "^");
                break;
            default:
                break;
        } 
    }
    string temp = "";
    for(int i = static_cast<int>(password.length()) - 1; i != -1; --i){
        temp += password.at(i);
    }
    password.append(temp);
    cout << "output: " << password;
}

void wordCalculator() {
    // TODO
}

void palindromeCounter() {
    // TODO
}