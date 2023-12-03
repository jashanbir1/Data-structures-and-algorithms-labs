#include <iostream>
#include <ctime>


using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;

int genRandInt(int low, int high) { // function given to us in zybooks, generate random integer
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){// function given to us in zybooks, used to fill array with random integers
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}
void InsertionSort(int numbers[], int size)//this function sorts the given array using InsertionSort method
{
    for(int i = 0; i < size; ++i)// traverse lower
    {
        for(int j = i; j < size; ++j)// traverse upper
        {
            if(numbers[j] < numbers[i])// if index after i is greater than i (example: 1,4,3 --- i is 4, j is 3)
            {
                int swapVal = numbers[j];// set swapVal to number after i
                numbers[j] = numbers[i];// set number at j to val at i
                numbers[i] = swapVal;// set number at i to the lesser val
            }
        }
    }
}

void Quicksort_midpoint(int numbers[], int i, int k)// this function sorts the given array in the range from i to k using quicksort method. 
//In this function, pivot is the midpoint element (numbers[(i+k)/2]).
{
    if(i >= k)// invalid
    {
        return;
    }
    int midPoint = i + (k - i) / 2;// middle pivot val
    int pivot = numbers[midPoint];// set pivot to middle val

    int low = i;
    int high = k;

    while(true)// while array has vals
    {
        while(numbers[low] < pivot)// increment low to get closer to pivot
        {
            ++low;
        }
        while(numbers[high] > pivot)// decrement high to get pivot
        {
            --high;
        }
        if(low >= high)// invalid, exit function
        {
            break;
        }
        else
        {
            int swapVal = numbers[high];// set swapVal to num at high index
            numbers[high] = numbers[low];// set num at high to num at low
            numbers[low] = swapVal;// set num at low to swap val
            ++low;// increment to reach pivot
            --high;// decrement to reach pivot
        }
    }
    Quicksort_midpoint(numbers, i , high);// call on low partition
    Quicksort_midpoint(numbers, high + 1 , k);// call on high partition

}

int medianOfThree(int left, int mid, int right)// fidn median between three nums
{
    if(left < mid)// if left is less than middle number
    {
        if(mid < right)// if middle is greater than right
        {
            return mid;// median is middle
        }
        else if(left < right)// if left is less than right
        {
            return right;// median is right
        }
        else{
            return left;// median is left;
        }
    }
    else// if mid is greater than left
    {
        if(left < right)// if left is less than right
        {
            return left;// median is left
        }
        else if (mid < right)// if mid is less than right
        {
            return right;// median is right
        }
        else
        {
            return mid;// median is middle
        }
    }
}
void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    if(i >= k)// invalid
    {
        return;
    }

    int midPoint = medianOfThree(numbers[i], numbers[i + ((k-i)/2)], numbers[k]);// The pivot is the median of the following three values

    int low = i;
    int high = k;

    while(true)// while array has vals
    {
        while(numbers[low] < midPoint)// increment low to get to midpoint
        {
            ++low;
        }
        while(numbers[high] > midPoint)// decrement high to get to midpoint
        {
            --high;
        }
        if(low >= high)// invalid, exit function
        {
            break;
        }
        else
        {
            int swapVal = numbers[high];// set swapVal to num at high index
            numbers[high] = numbers[low];// set num at high to num at low
            numbers[low] = swapVal;// set num at low to swapVal
            ++low;// incremment low to get to pivot
            --high;// decrement high to get to pivot
        }
    }
    Quicksort_medianOfThree(numbers, i , high);// call on low partition
    Quicksort_medianOfThree(numbers, high + 1 , k);// call on high partition
}

int main(){

}