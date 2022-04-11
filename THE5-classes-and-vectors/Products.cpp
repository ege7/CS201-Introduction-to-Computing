#include "Products.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // to print with alligned

// constructor for product struct
Product::Product(string qr, string name, double price)
{
    this->qr = qr;
    this->name = name;
    this->price = price;
    this->amount = 0;
}

Products::Products(){
    // make sure to this vectors are empty
    item_list.clear();
    shop_list.clear();

    total = 0;
}

vector<Product> Products::get_item_list()const {
    return item_list;
}
vector<Product> Products::get_shop_list()const {
    return shop_list;
}

Products::Products(const Products& p) {
    item_list = p.get_item_list();
    shop_list = p.get_shop_list();
}



void Products::read_files(ifstream& qr, ifstream& price)
{
    string qr_code;
    string name;
    double price_;

    string line;

    while (getline(qr, line)) {

        // reset qr_code and name
        qr_code = "";
        name = "";

        // take qr code part
        int qr_code_end = -1;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                qr_code_end = i;
                break;
            }
            else
            {
                qr_code += line[i];
            }
        }

        // after finding qr code, find name
        for (int i = qr_code_end + 1; i < line.length(); i++)
        {
            name += line[i];
        }

        // if there is a new line at end of the name, remove it
        // '\r' means carriage return, if file edited in Windows, it leaves a carriage return at the end of the line
        // '\n' means new line
        if (name[name.length() - 1] == '\n' || name[name.length() - 1] == '\r')
        {
            name = name.substr(0, name.length() - 1);
        }


        // add product to item_list
        Product p(qr_code, name, 0);
        item_list.push_back(p);
    }

    while (getline(price, line)) {

        // reset qr_code amd price
        string temp_price_str = "";
        qr_code = "";
        price_ = 0;


        // take qr code part
        int qr_code_end = -1;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                qr_code_end = i;
                break;
            }
            else
            {
                qr_code += line[i];
            }
        }

        // find price in string
        for (int i = qr_code_end + 1; i < line.length(); i++)
        {
            temp_price_str += line[i];
        }

        // convert string to double
        price_ = stod(temp_price_str);
        // find correspending qr_code and set price
        for (int i = 0; i < item_list.size(); i++)
        {
            if (item_list[i].qr == qr_code)
            {
                item_list[i].price = price_;
                break;
            }
        }
    }
}

string Products::toLowerHelper(string s)
{
    string temp = "";
    for (int i = 0; i < s.length(); i++)
    {
        temp += tolower(s[i]);
    }
    return temp;
}

bool Products::find(string qr_code)
{
    // convert to lower case with string method
    string qr_code_lower = toLowerHelper(qr_code);
    // find qr code in item_list
    for (int i = 0; i < item_list.size(); i++)
    {
        // convert item_list qr code to lower case
        string item_list_qr_code_lower = toLowerHelper(item_list[i].qr);
        // if qr code is found, return true
        if (item_list_qr_code_lower == qr_code_lower)
        {
            return true;
        }

    }

    return false;
}

bool Products::findInShopList(string qr_code)
{
    // convert to lower case with string method
    string qr_code_lower = toLowerHelper(qr_code);
    // find qr code in shop_list
    for (int i = 0; i < shop_list.size(); i++)
    {
        // convert shop_list qr code to lower case
        string shop_list_qr_code_lower = toLowerHelper(shop_list[i].qr);
        // if qr code is found, return true
        if (shop_list_qr_code_lower == qr_code_lower)
        {
            return true;
        }
    }

    return false;
}

void Products::add_item(string qr, int amount)
{
    // convert to lower case with string method
    string qr_code_lower = toLowerHelper(qr);
    // find product in item_list and add to shop_list
    for (int i = 0; i < item_list.size(); i++)
    {
        // convert item_list qr code to lower case
        string item_list_qr_code_lower = toLowerHelper(item_list[i].qr);
        // if qr code is found, add to shop_list
        if (item_list_qr_code_lower == qr_code_lower)
        {
            Product p(item_list[i].qr, item_list[i].name, item_list[i].price);
            p.amount = amount;
            shop_list.push_back(p);

            // add price to total
            total += p.price * (double)p.amount;

            break;
        }
    }
}

void Products::edit_item(string qr, int amount)
{
    // convert to lower case with string method
    string qr_code_lower = toLowerHelper(qr);
    // find product in shop_list and edit amount
    for (int i = 0; i < shop_list.size(); i++)
    {
        // convert shop_list qr code to lower case
        string shop_list_qr_code_lower = toLowerHelper(shop_list[i].qr);
        // if qr code is found, edit amount
        if (shop_list_qr_code_lower == qr_code_lower)
        {
            // edit total
            // remove old amount
            total -= shop_list[i].price * (double)shop_list[i].amount;

            shop_list[i].amount = amount;

            // add new amount
            total += shop_list[i].price * shop_list[i].amount;
            break;
        }
    }
}

void Products::remove_item(string qr)
{
    // convert to lower case with string method
    string qr_code_lower = toLowerHelper(qr);
    // find product in shop_list and remove
    for (int i = 0; i < shop_list.size(); i++)
    {
        // convert shop_list qr code to lower case
        string shop_list_qr_code_lower = toLowerHelper(shop_list[i].qr);
        // if qr code is found, remove
        if (shop_list_qr_code_lower == qr_code_lower)
        {
            // remove from total
            total -= shop_list[i].price * (double)shop_list[i].amount;

            shop_list.erase(shop_list.begin() + i);
            break;
        }
    }
}

void Products::print(vector<Product> p)
{
    for (int i = 0; i < p.size(); i++)
    {
        string leftSide = p[i].name + " *  " + to_string(p[i].amount) + " ";
        int leftSideLen = leftSide.length();

        double res = (double)p[i].amount * (double)p[i].price;
        if (p[i].amount >= 10) {
            string leftSide = p[i].name + " * " + to_string(p[i].amount) + " ";
            cout << leftSide << setw(37 - leftSideLen) << res << endl;
        }
        else {
            cout << leftSide << setw(36 - leftSideLen) << res << endl;
        }
    }    cout << endl;
    double vat = total * 0.18;
    double tempTotal = total + vat;
    cout << "VAT(18%): " << setw(26) << vat << endl;
    cout << "_______________________________________" << endl;
    cout << "Total: " << setw(29) << tempTotal << endl << endl;
}

void Products::printCurrentReceipt()
{
    print(this->shop_list);
}


void Products::printCurrentReceiptAscending()
{
    // order shop_list by amount with for loop without changing the original shop_list
    vector<Product> temp_shop_list;
    for (int i = 0; i < shop_list.size(); i++)
    {
        temp_shop_list.push_back(shop_list[i]);
    }

    // sort shop_list by amount with for loop
    for (int i = 0; i < temp_shop_list.size(); i++)
    {
        for (int j = 0; j < temp_shop_list.size() - 1; j++)
        {
            if (temp_shop_list[j].amount * temp_shop_list[j].price > temp_shop_list[j + 1].amount * temp_shop_list[j + 1].price)
            {
                Product temp = temp_shop_list[j];
                temp_shop_list[j] = temp_shop_list[j + 1];
                temp_shop_list[j + 1] = temp;
            }
            else if (temp_shop_list[j].amount * temp_shop_list[j].price == temp_shop_list[j + 1].amount * temp_shop_list[j + 1].price) {
                if (temp_shop_list[j].name > temp_shop_list[j + 1].name) {
                    Product temp = temp_shop_list[j];
                    temp_shop_list[j] = temp_shop_list[j + 1];
                    temp_shop_list[j + 1] = temp;
                }
            }
        }
    }

    // print after sort
    print(temp_shop_list);
}

void Products::printCurrentReceiptDescending()
{
    // order shop_list by amount with for loop without changing the original shop_list
    vector<Product> temp_shop_list;
    for (int i = 0; i < shop_list.size(); i++)
    {
        temp_shop_list.push_back(shop_list[i]);
    }

    // sort shop_list by amount with for loop
    for (int i = 0; i < temp_shop_list.size(); i++)
    {
        for (int j = 0; j < temp_shop_list.size() - 1; j++)
        {
            if (temp_shop_list[j].amount * temp_shop_list[j].price < temp_shop_list[j + 1].amount * temp_shop_list[j + 1].price)
            {
                Product temp = temp_shop_list[j];
                temp_shop_list[j] = temp_shop_list[j + 1];
                temp_shop_list[j + 1] = temp;
            }
            else if (temp_shop_list[j].amount * temp_shop_list[j].price == temp_shop_list[j + 1].amount * temp_shop_list[j + 1].price) {
                if (temp_shop_list[j].name < temp_shop_list[j + 1].name) {
                    Product temp = temp_shop_list[j];
                    temp_shop_list[j] = temp_shop_list[j + 1];
                    temp_shop_list[j + 1] = temp;
                }
            }
        }
    }

    // print after sort
    print(temp_shop_list);
}
