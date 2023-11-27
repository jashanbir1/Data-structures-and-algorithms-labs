#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

#include "HashTable.h"

HashTable:: HashTable(int numSize)
{
    size = numSize;
    hashTable = new list<WordEntry>[size];// *******
    next = nullptr;
    firstVal = nullptr;
}
void HashTable:: put(const string& putString, int score)
{
    if(contains(putString))
    {
        int wordHash = computeHash(putString);
        for(auto item = hashTable[wordHash].begin(); item != hashTable[wordHash].end();item++)
        {
            if(item->getWord() == putString)
            {
                item->addNewAppearance(score);
                return;
            }
        }
    }
    else
    {
        int newHash = computeHash(putString);
        WordEntry* newEntry = new WordEntry(putString, score);
        hashTable[newHash].push_front(*newEntry);
    }
}

int HashTable:: computeHash(const string &hashString)
{
    return hashString.size() % size;// want to place the item into the correct bucket by using the item's size of the string(which is an int) and mod(%) by size of table to find the bucket
}

double HashTable:: getAverage(const string& avgString)
{
    if(contains(avgString))
    {
        int wordHash = computeHash(avgString);
        for(auto item = hashTable[wordHash].begin(); item != hashTable[wordHash].end();++item)
        {
            if(item->getWord() == avgString)
            {
                return item->getAverage();
            }
        } 
    }
    return 2.0; //else, if word is not found and average could not be computed, return default 2.0
}

bool HashTable:: contains( const string &contString)
{
    int wordHash = computeHash(contString);
    for(auto item = hashTable[wordHash].begin(); item != hashTable[wordHash].end();++item)
    {
        if(item->getWord() == contString)//************
        {
            return true;// string found in table, return true
        }
    }
    return false;// else, if string is not in the hash table, return false
}