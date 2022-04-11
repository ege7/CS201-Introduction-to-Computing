
// Created by ege on 10.10.2021.


#include <iostream>
#include <string>

using namespace std;

int main()

{
    string nameofclassroom;
    int originalroomcapacity;
    double coefficient;
    int numofstudents;
    
    cout << "Welcome to CS201 physical classroom capacity checker." << endl;
    
    cout << "Please enter the room name: ";
    cin >> nameofclassroom;
    
    cout << "Please enter the room capacity: ";
    cin >> originalroomcapacity;
    
    if (originalroomcapacity < 0) {
        cout << "You have entered an invalid value for room capacity." << endl;
        return 0;
        
    }
    
    cout << "Please enter the allowed capacity coefficient: ";
    cin >> coefficient;
    
    if (coefficient > 1 || coefficient < 0){
        cout << "You have entered an invalid value for capacity coefficient." << endl;
        return 0;
    }
    
    int allowed_capacity = originalroomcapacity * coefficient;
    cout << "Please enter how many students are registered to your course: ";
    cin >> numofstudents;
    
    if (numofstudents <0) {
        cout << "You have entered an invalid value for registered students." << endl;
        return 0;
    }
    if (numofstudents <= allowed_capacity){
        cout << nameofclassroom << " can allow all students to attend physical lectures." << endl;
        
    }
    if (numofstudents > allowed_capacity){
        int zoom_students = numofstudents - allowed_capacity;
        cout << nameofclassroom << " cannot allow all students to attend physical lectures."<< endl;
        cout << "For each lecture " << zoom_students << " students must be selected to watch on Zoom." << endl;
    }
    
    
    
    
    return 0;
}
