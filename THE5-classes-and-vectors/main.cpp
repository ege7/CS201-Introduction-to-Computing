
// Created by ege on 02.01.2022
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // to print with alligned
#include "Products.h"

void printMenu()
{
    cout << "MENU" << endl;
    cout << "1. Add item to the shopping list" << endl;
    cout << "2. Delete item from the shopping list" << endl;
    cout << "3. Edit the amount of existing item" << endl;
    cout << "4. Print current receipt" << endl;
    cout << "5. Print current receipt in order" << endl;
    cout << "6. Print current receipt in reverse order" << endl;
    cout << "7. Exit" << endl;
    cout << "---" << endl;
}

ifstream tryToOpenFile(string takeInputStr, string errorStr)
{
    ifstream file;
    do
    {
        cout << takeInputStr;
        string qr_file_name;
        cin >> qr_file_name;
        file.open(qr_file_name);
        if (!file.is_open())
        {
            cout << endl;
            cout << errorStr << endl;
        }

    } while (!file.is_open());

    return file;
}
ifstream tryToOpenFilee(string takeInputStr, string errorStr)
{
    ifstream file;
    do
    {
        cout << takeInputStr;
        string qr_file_name;
        cin >> qr_file_name;
        cout << endl;
        file.open(qr_file_name);

        if (!file.is_open())
        {
            cout << errorStr << endl;
        }


    } while (!file.is_open());

    return file;
}

int main()
{
    Products products;
    ifstream qr_file = tryToOpenFilee("Please enter a filename for QR database: ", "The QR file does not exists");

    ifstream price_file = tryToOpenFile("Please enter a filename for Price database: ", "The price file does not exists");
    products.read_files(qr_file, price_file);

    int choice = -1;

    while (choice != 7)
    {
        // clear cin
        cin.clear();
        cin.ignore();
        printMenu();
        string temp_qr_code = "";
        int temp_amount = 0;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Please enter the QR code to add: ";
            cin >> temp_qr_code;
            if (!products.find(temp_qr_code))
            {
                cout << "Invalid QR code, try again" << endl;
                break;
            }

            if (products.findInShopList(temp_qr_code))
            {
                cout << "Item is already in the shoplist, if you want to edit the amount please choose option 3" << endl;
                break;
            }

            cout << "Please enter the amount to add: ";
            cin >> temp_amount;
            if (temp_amount < 1 || temp_amount > 25)
            {
                cout << "Invalid amount, try again" << endl;
                break;
            }

            products.add_item(temp_qr_code, temp_amount);
            break;
        case 2:
            cout << "Please enter the QR code to delete: ";
            cin >> temp_qr_code;

            if (!products.findInShopList(temp_qr_code))
            {
                cout << "Shoplist does not contain given QR code" << endl;
                break;
            }

            products.remove_item(temp_qr_code);
            break;

        case 3:
            cout << "Please enter the QR code to edit: ";
            cin >> temp_qr_code;

            if (!products.findInShopList(temp_qr_code))
            {
                cout << "Shoplist does not contain given QR code" << endl;
                break;
            }

            cout << "Please enter the amount to edit: ";
            cin >> temp_amount;
            if (temp_amount < 1 || temp_amount > 25)
            {
                cout << "Invalid amount, try again" << endl;
                break;
            }

            products.edit_item(temp_qr_code, temp_amount);
            break;

        case 4:
            products.printCurrentReceipt();
            break;
        case 5:
            products.printCurrentReceiptAscending();
            break;
        case 6:
            products.printCurrentReceiptDescending();
            break;
        case 7:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice, try again" << endl;
            break;
        }
    }


}
