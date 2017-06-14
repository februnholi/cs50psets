/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

const int MAX2 = 65536;

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Create variables to break problem in 2 every iteration
    int left = 0;
    int right = n - 1;
    int middle = (left + right + 1) / 2;
    
    // verify if value is in the middle before or if value searched is inside array (if not, return false), before starting search
    if (values[middle] == value)
    {
        return true;
    }
    else if (values[left] > value)
    {
        return false;
    }
    else if (values[right] < value)
    {
        return false;
    }
    else
    {
        // if limits are equal or right limit is bigger than left limite, continue searching
        while (right - left >= 0)
        {
            if (values[middle] == value)
            {
                return true;
            }
            else if (values[middle] > value)
            {
                right = middle - 1;
                middle = (right + left + 1) / 2;
            }
            else
            {
                left = middle + 1;
                middle = (right + left + 1) / 2;
            }
        }
    }
    //If not found, return false
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    if (n < 2)
    {
        return;
    }
    else
    {
        // creates counting array
        int count[MAX2];
        int aux;
        
        // Establishes zero for all elements, to start counting
        for (int i = 0; i < MAX2; i++)
        {
            count[i] = 0;
        }
        
        // Uses auxiliar array to count number of elements with same value
        for (int i = 0; i < n; i++)
        {
            aux = values[i];
            count[aux]++;
        }
        
        aux = 0;
        // uses counting array information to sort values array
        for (int i = 0; i < MAX2; i++)
        {
            // if element i is >0, there is one or more elements in values[] of value i and should be included in sorted array
            if(count[i] > 0)
            {
                // new counter j to store value i #j times in array values[]
                for(int j = 0; j < count[i]; j++)
                {
                    values[aux] = i;
                    aux++;
                }
            }            
        }
        
        
    }
    return;
}

