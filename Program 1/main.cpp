#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(string payload) {
    
    Node *newNode = new Node();//construct newnode
    newNode->payload = payload;//set  payload to parameter payload passed in
    newNode->next = nullptr;// initialize next to point to nothing for now
    return newNode;
    
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        Node *knewNode = newNode(name);// construct a starting point
        if (head == nullptr) {
            head = knewNode;//(name); // initialize head specially, first name  
        } else {
            prev->next = knewNode;//(name);// set next name to be added
        }
        prev = knewNode;// set prev to knewnode, passing up the old prev and moving list forward allowing to make the loop go again to keep adding names
        
    }

    if (prev != nullptr) {
        // make circular, circular list
        prev->next = head;
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) {
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing, while start does not equal start
        for (int i = 0; i < k; ++i) { // find kth node
          prev = curr;//prev is value behind curr, so as curr goes to next, prev follows
          curr = curr->next;// set to next name
        }

        // delete kth node
        prev->next = curr->next;// set prev->next to the value after curr
        Node* val = curr;// save curr into a variable to delete later on
        curr = curr->next;// set curr to the next value
        delete val;// delete the curr stored in val, eliminated person gets deleted
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1, max; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}

