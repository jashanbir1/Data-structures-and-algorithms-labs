#include <iostream>
#include <string>

using namespace std;

#include "IntList.h"

int main() {

    cout << "Constructing new list" << endl;// creating list to test my IntList.cpp
    IntList list; //variable declared
    

    cout << "Push_front 10" << endl;// check push_front
    list.push_front(10);
    cout << list << endl;
    cout << "Push_back 30" << endl;//check push_back
    list.push_back(30);
    cout << list << endl;
    cout << "Push_front(20)" << endl;
    list.push_front(20);
    cout << list << endl;
    cout << "Push_back(40)" << endl;
    list.push_back(40);
    cout << list << endl;
    cout << "Push_back 50" << endl;
    list.push_back(50);
    cout << list << endl;
    cout << "Push_front 70" << endl;
    list.push_front(70);
    cout << list << endl;

    cout << endl;
    cout << "print reverse" << endl;// check printReverse
    list.printReverse();
    cout << endl;
    cout << endl;

    cout << list << endl;
    cout<<endl;
    cout << "Pop_front() 70" << endl;// check pop front
    list.pop_front();
    cout << list << endl;
    cout << "Pop_front() 20" << endl;
    list.pop_front();
    cout << list << endl;
    cout << "pop_front 10" << endl;
    list.pop_front();
    cout << list << endl;
    cout << "Pop_back() 50" << endl;//check pop_back()
    list.pop_back();
    cout << list << endl;
    cout << "Pop_back() 40" << endl;
    list.pop_back();
    cout << list << endl;
    cout << "print reverse" << endl;
    list.printReverse();
    cout << endl;

    //testing copy assignment constructor
    int a,b;
    a = 4;
    b = 3;
    a = b;
    cout << a << endl;
}