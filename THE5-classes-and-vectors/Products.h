#pragma once

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "strutils.h"

using namespace std;

struct Product{
    Product(string, string, double);
    string qr;
    string name;
    double price;
    int amount;
};


class Products{

private:
    vector<Product> item_list;
    vector<Product> shop_list;
    double total;

    void print(vector<Product> p); // helper functions, since it is a helper function, it can be private
    string toLowerHelper(string s); // converts given string to lowercase

public:
    Products();
    Products(const Products & p);
    vector<Product> get_item_list() const;
    vector<Product> get_shop_list() const;
    // you are going to implement these member functions
    void read_files(ifstream & qr, ifstream & price);
    // it reads qr and price files and stores them into item_list
    bool find(string qr_code);
    // given qr code it searches that inside item_list
    bool findInShopList(string qr_code);
    // given qr code it searches that inside shop_list
    void add_item(string qr, int amount);
    // adds an item to the shop_list
    void edit_item(string qr, int amount);
    // edits an item in teh shop_list
    void remove_item(string qr);
    // removes an item from the shop_list
    void printCurrentReceipt(); // prints the current receipt
    void printCurrentReceiptAscending();
    // prints the current receipt in ascending order
    void printCurrentReceiptDescending();
    // prints the current receipt in descending order

    // setter and getter for total
    void setTotal(double total) {this->total = total;};
    double getTotal() {return this->total;};
};

