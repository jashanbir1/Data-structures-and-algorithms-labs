#ifndef _STACK_H
#define _STACK_H_

using namespace std;

template <typename T>
class stack{

    private:
    static const int MAX_SIZE = 20;
    T data[MAX_SIZE];
    int size;

    public:
    stack()// construct stack with array size = 0
    {
        size = 0;
    };
    void push (T val)// push value to top of stack
    {
        if (size == MAX_SIZE)
        {
            throw overflow_error("Called push on full stack.");
        }
        data[size++] = val;// push value to top of stack at size then incrementing
    };
    void pop()// remove value from top of stack
    {
        if(size == 0)
        {
            throw out_of_range("Called pop on empty stack.");// if empty, stack has nothing to pop
        }
        --size;// decrement size of array from top
    };
    void pop_two()// remove two values from the top
    {

        if(size == 0)
        {
            throw out_of_range("Called pop_two on empty stack");// if size is empty, cannot call pop_two on empty stack
        }
        if (size == 1)
        {
            throw out_of_range("Called pop_two on a stack of size 1.");// if size is 1, cannot pop two values with array with 1 element
        }
        if(!empty())
        {
            --size;
            --size;
            // decrement size twice
        }


    };
    T top()// return top value
    {
        if (size == 0)
        {
            throw underflow_error("Called top on empty stack.");// cannot return top value if stack is empty
        }
        return data[size - 1];// return val at top
    };
    bool empty()
    {
        return (size == 0);
        // return true if stack is empty
    };
    stack<T>& operator=(const stack<T>& cpyArray)// copies array data
    {
        while (this != cpyArray)// while the array from which is being copied does not equal the array to which values are being copied
        {
            size = cpyArray.size;//set size equal to new array size
            for(unsigned i = 0; i < size; ++i)//loop through old array
            {
                data[i] = cpyArray.data[i];//assign vals from data array to new array
            }
        }
        return *this;// return copy array
    };
    void destructArray()
    {
        
        while(!empty())
        {
            pop();
        }
    };
};
#endif