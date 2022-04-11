
//  Created by ege on 21.10.2021.


#include <iostream>
#include <string>

using namespace std;

bool BudgetCheck(int a);
bool QuantityCheck(int a, int b, int c);
int CalculateTotalPrice(int a, int b, int c);
int ConditionalMaxOperation(int previous_max_price, int current_price, int budget);
void MaxPriceCalculator(int q1, int q2, int q3, int budget, int &max_price);
int MaxPricePermutation(int q1, int q2, int q3, int budget);
int Runner();

int main(){
    Runner();
    Runner();
    
    cout << "Goodbye!"<< endl;
    
    return 0;
}

bool BudgetCheck(int a){
    if (a < 0){
        return false;
        
    }
    else{
        return true;
    }
}
bool QuantityCheck(int a, int b, int c){
    if (a > 0 && b > 0 && c > 0){
        return true;
        
    }
    else{
        return false;
        
    }
}

int CalculateTotalPrice(int a, int b, int c){
    int total = a * 5 + b * 10 + c * 15;
    return total;
}

int ConditionalMaxOperation(int previous_max_price, int current_price, int budget){
    if (previous_max_price > current_price || current_price > budget){
        return previous_max_price;
    }
    else{
        return current_price;
    }
}

void MaxPriceCalculator(int q1, int q2, int q3, int budget, int &max_price){
    int current_price = CalculateTotalPrice(q1, q2, q3);
    int max = ConditionalMaxOperation(max_price, current_price, budget);
    max_price = max;
    
}

int MaxPricePermutation(int q1, int q2, int q3, int budget){
    int max_price = 0;
    MaxPriceCalculator(q1, q2, q3, budget, max_price);
    MaxPriceCalculator(q2, q1, q3, budget, max_price);
    MaxPriceCalculator(q1, q3, q2, budget, max_price);
    MaxPriceCalculator(q3, q2, q1, budget, max_price);
    MaxPriceCalculator(q2, q3, q1, budget, max_price);
    MaxPriceCalculator(q3, q1, q2, budget, max_price);
    return max_price;
}
int Runner(){
    int q1,q2,q3,budget,max_price;
    cout << "Please enter your budget: ";
    cin >> budget;
    if (budget < 0){
        cout << "Budget cannot be negative.\n";
        cout << endl;
        return 0;
    }
    cout << "Please enter three quantities: ";
    cin >> q1 >> q2 >> q3;

    if (QuantityCheck(q1, q2, q3) == false){
        cout << "All quantities must be positive.\n";
        cout << endl;
        return 0;
    }
    max_price = MaxPricePermutation(q1,q2,q3,budget);
    if (max_price == 0){
        cout << "You cannot afford any of the permutations with these quantities and budget.\n";
        cout << endl;
        return 0;
    }
    else{
        cout << "You have " << budget - max_price << " liras left.\n";
        cout << endl;
        
    }
    return 0;
}

