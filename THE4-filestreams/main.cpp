// Created by ege on 13.12.2021.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "strutils.h"

using namespace std;

string checkFile(string, bool);
void readList(string, string, string);
string getItem(string, string);
float getPrice(string, string);
string toLowerCase(string str);


int main(){
    string itemFile = checkFile("QR", true);
    string priceFile = checkFile("Price", true);
    string listFile = checkFile("shopping list", false);
    
    readList(listFile, itemFile, priceFile);
    
    
    return 0;
}

string checkFile(string fileName, bool isDB){
    ifstream input;
    string filename;
    
    do{
        cout << "Please enter a filename for " << (isDB ? "" : "your ") << fileName << (isDB ? " database: " : ": ");
        cin >> filename;
        cout << endl;
        
        input.open(filename);
        if(!input.is_open()){
            cout << "The " << fileName << " file does not exists\n";
        }
    }while(!input.is_open());
    
    input.close();
    return filename;
    
}

void readList(string listFile, string itemFile, string priceFile){
    ifstream input;
    string line;
    float sum = 0;
    
    input.open(listFile.c_str());
    int counter = 1;
    while(getline(input,line)){
        istringstream iss(line);
        string qr;
        int no;
        string space = "";
        if(!(iss >> qr >> no)){
            break;
        }
        string name = getItem(qr, itemFile);
        StripWhite(name);
        if(name.length() > 0){
            double cost = getPrice(qr, priceFile) * (double)no;
            if(counter == 1){
                counter ++;
                int length = 36 - (name.length() + to_string(no).length() + 4);
                cout << setfill(' ');
                cout << name + " *  " + to_string(no) << setw(length) << cost;
                cout << endl;
            }
            else if(counter > 1){
                int blanknum = 0;
                for(int k = 0; k < name.length(); k++){
                    if(name[k] == ' '){
                        blanknum ++;
                    }
                }
                if(blanknum % 2 == 0){
                    int length = 36 - (name.length() + to_string(no).length() + 3);
                    for(int i = 0; i < length ; i++){
                        space += " ";
                    }
                    cout << setfill(' ');
                    cout << name  + " * " + to_string(no) << setw(length) << cost;
                    cout << endl;
                }
                else{
                    int length = 36 - (name.length() + to_string(no).length()+4);
                    for(int i = 0; i < length; i++){
                        space += " ";
                    }
                    cout << setfill(' ');
                    cout << name + " *  " + to_string(no) << right << setw(length) << cost;
                    cout << endl;
                }
            }
            sum += cost;
        }
    }
    cout << endl;
    input.close();
    int VAT_RATE = 18;
    int length = 36 - (to_string(VAT_RATE).length() + 7);
    cout << setfill(' ');
    cout << "VAT(" + to_string(VAT_RATE) + "%):" << right << setw(length) << sum * VAT_RATE/100 << endl;
    cout << "_______________________________________";
    cout << endl;
    length = 36 - (7);
    cout << "Total: " << right << setw(length) << (sum*(1.0 + VAT_RATE / 100.0)) << endl;
}

string getItem(string query, string itemFile){
    ifstream input;
    string line, qr;
    input.open(itemFile.c_str());
    while(getline(input,line)){
        istringstream iss(line);
        if(!(iss >> qr)){
            break;
        }
        if(toLowerCase(query) == toLowerCase(qr)){
            input.close();
            return line.erase(line.find(qr),qr.length()+1);
            
        }
    }
    input.close();
    return "";
    
}

float getPrice(string query, string priceFile){
    ifstream input;
    string line;
    string qr;
    float price;
    input.open(priceFile.c_str());
    
    while(getline(input,line)){
        istringstream iss(line);
        if(!(iss >> qr >> price)){
            break;
        }
        if(toLowerCase(query) == toLowerCase(qr)){
            input.close();
            return price;
        }
    }
    input.close();
    return 0;
}

string toLowerCase(string str){
    string res = "";
    for(char c : str){
        if(c <= 'Z' && c >= 'A'){
            c -= ('Z' - 'z');
        }
        res += c;
    }
    return res;
}
