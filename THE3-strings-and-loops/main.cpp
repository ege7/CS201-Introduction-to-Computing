
// Created by ege on 27.11.2021.

#include <iostream>
#include <string>

using namespace std;


bool isNumber(string word);
bool isEmpty(string input);
bool isDot(string input);
string noSpecialCharacter(string s);
void polindrome(string a, string b);



int main(){
    string input;
    string eSentence;
    while(true){
        bool notAlpha = true;
        cout << "Please enter the input sentences: ";
        cin >> input;
        bool ege = true;
        eSentence = "";
        while(ege){
            eSentence += input + " ";
            if(isNumber(input)){
                notAlpha = false;
            }
            if(input != "@"){
                cin >> input;
            }
            else{
                ege = false;
            }
        }
    
            if(isEmpty(eSentence) == true){
                cout << "Input string should not be empty." << endl;
                cout << endl;
                continue;
                
            }
            else if(isDot(eSentence) == false){
                cout << "There should be at least one sentence." << endl;
                cout << endl;
                continue;
            }
            else if(notAlpha == false){
                cout << "There should be no words without alphabetical characters." << endl;
                cout << endl;
            }
            else{
                eSentence = eSentence.substr(0,eSentence.length()-2);
                string reverse = string(eSentence.rbegin(),eSentence.rend());
                reverse = reverse.substr(2,eSentence.length()-1);
                reverse += " .";
                for(int i = 0; i < reverse.length();i++){
                    reverse[i] = tolower(reverse[i]);
                    eSentence[i] = tolower(eSentence[i]);
                    
                }
                cout << endl;
                reverse = noSpecialCharacter(reverse);
                eSentence = noSpecialCharacter(eSentence);
                polindrome(reverse, eSentence);
                break;
            }
    
    }
    
    return 0;
}

bool isNumber(string word){
    int count = 0;
    for(int i = 0; i < word.length(); i++){
        if(word == "."){
            return true;
        }
        else{
            if(isdigit(word[i])){
                count++;
            }
        }
    }
    if(word.back() == '.'){
        if(count == word.length()-1){
            return true;
            
        }
        else{
            return false;
        }
    }
    else{
        if(count == word.length()){
            return true;
            
        }
        else{
            return false;
        }
    }
}

bool isEmpty(string input){
    if(input.length() == 2){
        return true;
    }
    else{
        return false;
    }
}

bool isDot(string input){
    if(input.find(".") != string::npos){ // string::npos = does have it inside.
        return true;
    }
    else{
        return false;
    }
}

string noSpecialCharacter(string s){
    for(int i = 0; i< s.length();i++){
        if((s[i] < 'A' || s[i] > 'Z') && (s[i] < 'a' || s[i] > 'z')){
            if(s[i] == ' ' || s[i] == '.'){
                
            }
            else{
                s.erase(i,1);
                i--;
            }
        }
    }
    return s;
}
void polindrome(string a, string b){
    string temp = "";
    string out = "";
    int sentence = 0;
    for(int j = 0;j<a.length();j++){
        if(a[j] == '.'){
            sentence++;
            
        }
    }
    int maxsent = sentence;
    while(sentence > 0){
        for(int i = 0; i<b.length()+1;i++){
            if(a[i] == '.'){
                cout << "Sentence (" << std::to_string(sentence) << "/" << std::to_string(maxsent) << "):" << endl;
                out = out.substr(0,out.length()-1);
                cout << out << endl;
                sentence --;
                out = "";
                
            }
            else if(a[i] == ' '){
                if(b.find(temp) != std::string::npos){
                    if(temp == "ab" || temp == "ba"){
                        out += "notpalindrome ";
                        temp = "";
                        
                    }
                    else{
                        out += temp + " ";
                        temp = "";
                        
                    }
                }
                else{
                    out += "notpalindrome ";
                    temp = "";
                }
            }
            else{
                temp += a[i];
            }
        }
    }
}

