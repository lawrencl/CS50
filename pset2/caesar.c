#include <cs50.h> // string data type
#include <ctype.h> //isupper, islower
#include <stdio.h>
#include <stdlib.h> //  atoi (included also cs50.h)
#include <string.h> //  strlen
    
int main(int argc, string argv[])
{
    // request 2 arguments (i.e. ./caesar 2)
    if (argc != 2)
    {
        printf("Next time, enter secret key that is non-negative integer.\n");
        return 1;
    }
    // only allow second argument to be a positive integer  
    int k = atoi(argv[1]); // converts string to int
    if (k <= 0)
    {
        printf("Please enter positive integer.\n");
        return 1;
    }
    // reqeust text to encrypt
    // printf("Enter a string to encrypt: ");
    string p = GetString();
    
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        //printf("%c", p[i] + k %26);  
        if (isupper(p[i]))
            printf ("%c", ((p[i]-'A')+k)%26+'A');
        else if (islower(p[i]))
            printf ("%c", ((p[i]-'a')+k)%26+'a');
        //to account for space
        else if (p[i]==' ')
            printf (" ");
        else 
            printf ("%c", p[i]);
    }
    // return prompt on next line
    printf("\n");
    
    return 0;
}
