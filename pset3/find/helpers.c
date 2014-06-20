/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0)
        return false;
        
    // TODO: implement a searching algorithm
    for (int i = 0; i < n; i++)
        if (values[i] == value)
            return true;        
        return false;
        
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int i,j,min_val;
    for(i = 0; i < n; i++)
        for(j = i + 1; j < n; j++)
            if(values[i] > values[j])
            {
                min_val = values[j];
                values[j] = values[i];
                values[i] = min_val; 
                i = 0; //need to revalidate from beginning after swapping
            }
    return;
}
