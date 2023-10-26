#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
//GIVEN CODE TO US FROM ZYBOOKS
vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}


template<typename T>  // function template with type parameter 'T'
unsigned min_index(const vector<T> &vals, unsigned index)
{
    int minIndex = index;// set a minIndex variable to represent a index that can potentially be changed
    for(unsigned int i = index + 1; i < vals.size(); i++)// for loop to iterate through vector starting from passed in index to end of vector
    {
        if(vals.at(i) < vals.at(minIndex))// if val at i is less than val at index passed in
        {
        minIndex = i;// set min index to that index
        }
    }
    return minIndex;//return index with smallest value
}

template<typename T>
void selection_sort(vector<T> &vals)
{
    try// Try,throw,catch block
    {
        if(vals.empty())// if vector is empty
        {
            throw runtime_error("nothing inside vector");// throw block sends error message
        }
        for (unsigned i = 0; i < vals.size() - 1; ++i)// loop to go through vector vals
        {
            //TO HELP VISUALIZE, USING IMAGINARY LIST: 7,9,3,18,8
            unsigned minSort = min_index(vals,i);// use function min_index to find smallest val in vals vector
            T storeVal = vals.at(i);// stores larger val in a variable of template type T (stores 7 in storeVal)
            vals.at(i) = vals.at(minSort);// makes larger val assigned to the possition of the smaller val that is further ahead in the list (puts 7 where 3 was)
            vals.at(minSort) = storeVal; // stores larger val in place of where smaller val was (puts 3 where 7 was, ultimately switching their places)
        }
    }
        catch (const exception& e)//catch 
        {
            cout << e.what() << endl;// output error message
        }
}

template<typename T>
T getElement(vector<T> vals, int index)
{
    unsigned indx = index;
    if (index < 0 || indx >= vals.size())// if the index is negative or larger than the specified range to be searched
    {
        throw out_of_range("Out of range exception occured");// send out of range error
    }
    return vals.at(index);// return the item stored at the index

}

int main() {

    int testCase;
    cout << "Which test case" << endl;
    cin >> testCase;

    if(testCase == 1)
    {
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0)
    {
        cout << "Enter a number: " << endl;
        cin >> index;
        try
        {
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
        catch(out_of_range& e)
        {
            cout << e.what() << endl;
        }
    }
    return 0;
    }

    if(testCase == 2)
    {
        vector<int> intVec;
        intVec.push_back(13);
        intVec.push_back(12);
        intVec.push_back(3);
        intVec.push_back(1);
        intVec.push_back(9);
        for(unsigned i = 0; i < intVec.size(); i++)
        {
            cout << intVec.at(i) << ' ';
        }
        cout << endl;

        selection_sort(intVec);
        cout << "IntVec selection sorted" << endl;
        for(unsigned k = 0; k < intVec.size(); k++)
        {
            cout << intVec.at(k) << ' ';
        }
        cout << endl;
    }
    if(testCase == 3)
    {
        vector<double> doubleVec;
        doubleVec.push_back(13.1);
        doubleVec.push_back(12.2);
        doubleVec.push_back(3.3);
        doubleVec.push_back(1.4);
        doubleVec.push_back(9.5);
        
        for(unsigned i = 0; i < doubleVec.size(); i++)
        {
            cout << doubleVec.at(i) << ' ';
        }
        cout << endl;

        selection_sort(doubleVec);
        cout << "IntVec selection sorted" << endl;
        for(unsigned k = 0; k < doubleVec.size(); k++)
        {
            cout << doubleVec.at(k) << ' ';
        }
        cout << endl;
    }
    if(testCase == 4)
    {
        vector<string> stringVec;
        stringVec.push_back("jashan");
        stringVec.push_back("pat miller");
        stringVec.push_back("jash");
        stringVec.push_back("cs010c");

        for(unsigned i = 0; i < stringVec.size(); i++)
        {
            cout << stringVec.at(i) << ' ';
        }
        cout << endl;

        selection_sort(stringVec);
        cout << "IntVec selection sorted" << endl;
        for(unsigned k = 0; k < stringVec.size(); k++)
        {
            cout << stringVec.at(k) << ' ';
        }
        cout << endl;
    }


}

