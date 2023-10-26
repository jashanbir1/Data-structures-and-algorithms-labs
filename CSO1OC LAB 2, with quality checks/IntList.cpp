#include <iostream>
#include <string>

using namespace std;

#include "IntList.h"

IntList:: IntList()// constructs the nodes of the program, setting them to new values
{
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}
IntList::~IntList()// destructor, required to free up memory after program is done, rule of three
{
    while (dummyHead)
    {
        IntNode* curr = dummyHead->next;
        delete dummyHead;
        dummyHead = curr;
    }
}
IntList::IntList ( IntList& lhs, const IntList& rhs)// copy constructor, DEEP COPY, rule of three
{
    IntNode* curr = rhs.dummyHead;
    while (curr != nullptr)
    {
        this->push_back(curr->data);
        curr = curr->next;
    }
}
void IntList::operator=(const IntList &list)// copy assignment ,DEEP COPY, rule of three
{
    IntList(*this,list);
}
void IntList:: push_front(int val)// pushes value to the front of list
{
    
    IntNode *newVal = new IntNode(val);// allocate new node for val you want to push_front
    IntNode *dNext = dummyHead->next;// helper variable to represent dummyHead->next, easier to understand when writing dummyHead->next->prev
    dummyHead->next = newVal;// set value after dummyHead to newVal
    dNext->prev = newVal;// set prev of dummyHead to newVal (drawing helps)
    newVal->prev = dummyHead;// set previous of newVal to the dummyHead
    newVal->next = dNext;//make newVal point to node after dummyHead->next

}
void IntList:: pop_front()// removes value at front of list
{
    if(empty())
    {
        throw runtime_error("list is empty already, nothing to pop front");
    }
    else
    {
    IntNode* val = dummyHead->next;// assign a val with the value after dummyHead
    dummyHead->next = val->next;//assign the value after dummy head with the value AFTER the val value, which we previously set val=dummyHead->next, so val aftet this
    val->next->prev = dummyHead;// assign the previous of the value we assigned dummyHead->next with on the previous line to be dummy head
    delete val; // delete the value holding the value after dummyHead
    }
}
bool IntList:: empty() const// checks if list is empty
{
    return (dummyHead->next == dummyTail);// if dummyHead->next == dummyTail, that means there is no elements since both are dummy nodes and dont have values in them
}
void IntList:: push_back(int val)// push value to back of list
{
    
    IntNode* newVal = new IntNode(val);// allocate space for new node,called newVal which will be pushed back
    IntNode* dPrev = dummyTail->prev;//helper to represent dummyTail->prev, easier to understand and see when writing dummyTail->prev->next
    dummyTail->prev = newVal;// set prev of dummyTail to newVal
    newVal->next = dummyTail;
    dPrev->next = newVal;
    newVal->prev = dPrev;
}
void IntList:: pop_back()// remove value at back of list
{
    if (empty())
    {
        throw runtime_error("list is empty, nothing to pop_back");
    }
    else {
    IntNode* val = dummyTail;// set val equal to the tail

		if (dummyTail == dummyHead) //if only one element
        {
			delete val;// delete the val
			dummyHead = nullptr;// set head to nothing
			dummyTail = nullptr;// set tail to nothing
		}

		else {
            //helped out drawing this
			dummyTail = dummyTail->prev;// set to val before dummyTail val
			dummyTail->next = nullptr;//set the value that was after dummy tail on last step to nothing
			delete val;//delete val in between the two steps in previous two lines
		}
	}

}
ostream& operator<< (ostream& o, const IntList& rhs)// output operator
{
    IntNode *list = rhs.dummyHead->next;// set list to value after rhs.dummyHead
    while(list != rhs.dummyTail)// while there is elements in the list
    {
        if(list->next == rhs.dummyTail)
        o << list->data;// output with no space after because if it is last item, we want the space to end here
        else
        {
            o << list->data << ' ';// output with space because it is not last item
        }
        list = list->next;// set to next item and repeat process
        
    }
    return o;
}
void IntList:: printReverse() const// print list in reverse order
{
    if (empty())
    {
        throw runtime_error("nothing to print in reverse");
    }
    else
    {
        IntNode* lastVal = dummyTail->prev;// start at tail and go backwards
        while (lastVal->prev != nullptr)// checks to make sure list is not empty
        {
            cout << lastVal->data << " ";
            lastVal = lastVal->prev;
        }
        
    }
    
}