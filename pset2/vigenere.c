#include <cs50.h> // string data
#include <ctype.h> //isupper, islower, isdigit, ispunct, isspace, isalpha
#include <stdio.h>
//#include <stdlib.h> //  atoi (included also cs50.h)
#include <string.h> //  strlen

//declare function
int VCipher(string, string);
    
int main(int argc, string argv[])
{
    // request 2 arguments 
    if (argc != 2)
    {
        printf("Enter only one secret key that is a string.\n");
        return 1;
    }
    // validate key to only alpha
    else if (argv[1])
    {
        int j = strlen(argv[1]);
        for (int i = 0; i < j; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Only alpha characters please for key.\n");
                return 1;
            }
        }
    }
        
    // reqeust text to encrypt
    // printf("Enter a string to encrypt: ");
    string USERTEXT = GetString();
    
    // call VCipher passing User Text and Key
    VCipher(USERTEXT, argv[1]);
    
    // comment out old code for reference
    /*
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
    */
        
    // return prompt on next line
    printf("\n");
    
    return 0;
} // end main


int VCipher(string USERTEXT, string KEY)
{   
    // counter for KEY
    int k_cnt = 0; 
    
    // for loop for USERTEXT
    for (int i = 0, n = strlen(USERTEXT); i < n; i++)
    {
        if(isalpha(USERTEXT[i]))
        {
            if (isupper(USERTEXT[i]))                
            {
                if (isupper(KEY[k_cnt]))                       
                {
                    printf ("%c", ((USERTEXT[i]-'A')+(KEY[k_cnt]-'A'))%26+'A');                    
                }
                else if (islower(KEY[k_cnt]))                    
                {        
                    printf ("%c", ((USERTEXT[i]-'A')+(KEY[k_cnt]-'a'))%26+'A');                                 
                }
            }
            else if (islower(USERTEXT[i]))
            {
                if (isupper(KEY[k_cnt]))                       
                {
                    printf ("%c", ((USERTEXT[i]-'a')+(KEY[k_cnt]-'A'))%26+'a');                    
                }
                else if (islower(KEY[k_cnt]))                    
                {        
                    printf ("%c", ((USERTEXT[i]-'a')+(KEY[k_cnt]-'a'))%26+'a');                                 
                }
            }
            // key count needs own counter
            k_cnt++;
            if(KEY[k_cnt] == '\0') // resets key
                k_cnt = 0;
        }
        // if character is a space, print space
        else if(isspace(USERTEXT[i]))
        {
            printf(" ");
        }
        // if character is punctuation, print punct
        else if(ispunct(USERTEXT[i]))
        {
            printf("%c", USERTEXT[i]);
        }
        // if character is digit, print digit
        else if(isdigit(USERTEXT[i]))
        {
            printf("%c", USERTEXT[i]);
        }
        // else, just print the character, whatever it is...
        else
        {
            printf("%c", USERTEXT[i]); 
        }
    }// end FOR loop
    
    return 0;
    
}// end VCipher
