#include <iostream>
#include <string>

using namespace std;

#include "Heap.h"

Heap:: Heap()
{
    numItems = 0;
}

void Heap:: enqueue(PrintJob* val)// add a node to end of queue
{
    if(numItems != MAX_HEAP_SIZE)
    {
        if(numItems == 0)
        {
            arr[numItems++] = val;// add new val to root and increment queue
        }
        else
        {
            int newIndex = numItems;//set newIndex to size of array
            while(newIndex > 0 && arr[(newIndex - 1) / 2]->getPriority() < val->getPriority())// while the parents priority is less than the new vals priority
            {
                arr[newIndex] = arr[(newIndex - 1) / 2];// set arr at newIndex to the parent nodes index
                newIndex = (newIndex - 1) / 2;// newIndex is the parents index
            }
            arr[newIndex] = val;// set new val to the parent index
            numItems++;// increment size
        }
    }
}

void Heap:: dequeue()// remove item from queue
{
    if(numItems == 0)
    {
        return;// nothing to dequeue, return
    }
    else
    {
        if(!empty())// if not empty
        {
            if(numItems != 1)// if size is not 1
            {
                arr[0] = arr[numItems -1];// set root to last node in last level
            }
            numItems--;// decrement because one less node
            trickleDown(0);// percolate to find good order
        }
    }
}

void Heap:: trickleDown(int val)// move new root to proper location
{
    if(numItems < val * 2 + 2)// one element, no children
    {
        return;
    }
    else if(numItems == val * 2 + 2)// one child
    {
        if(arr[val]->getPriority() < arr[numItems - 1]->getPriority())// if new val has less priority than last val
        {
            swap(val,numItems - 1);
        }
    }
    else
    {
        PrintJob* leftChildInd = arr[2 * val + 1];//left child
        PrintJob* rightChildInd = arr[2 * val + 2];//right child

        if (leftChildInd->getPriority() > rightChildInd->getPriority())
        {
            if (arr[val]->getPriority() < arr[val * 2 + 1]->getPriority())
            {
                swap(val, val * 2 + 1);// swap vals in order of priority
            }

            trickleDown(val * 2 + 1);
        }
        else
        {
            if (arr[val]->getPriority() < arr[val * 2 + 2]->getPriority())
            {
                swap(val, val * 2 + 2);// swap vals in order of priority
            }

            trickleDown(val * 2 + 2);
        }
    }
}
void Heap:: swap(int val1, int val2)// helper function, used to swap vals
{
    PrintJob* swapVal = arr[val1];// save val to be swapped into a temp val
    arr[val1] = arr[val2];//put val1 value with where val2 val was
    arr[val2] = swapVal;// put val1 val in for val2
}

PrintJob* Heap:: highest()// retireve highest priority val
{
    if(empty())
    {
        return nullptr;// no priority val to return
    }
    else
    {
        return arr[0];// return root, highest priority
    }
}

bool Heap:: empty() const
{
    return (numItems == 0);// size equals 0, no vals
}

void Heap:: print()// print in order of highest priority, highest job number, and highest pages
{
    if(empty())
    {
        throw runtime_error("nothing to print, empty queue");
    }
    else
    {
        cout << "Priority: " << highest()->getPriority() << ", Job Number: " 
             << highest()->getJobNumber() 
             << ", Number of Pages: " << highest()->getPages() << endl;
    }
}
