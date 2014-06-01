#include <stdio.h>
#include <cs50.h> // allows GetInt();

int main(void)
{
    int height;
    //printf("Please enter a Height less than 23 but greater than 0.\n");
    do
    {
        printf("Height: ");
        height = GetInt();
        if (height == 0)
            return 0;
    } while (height > 23 || height < 0);
    
    for (int tall=0; tall < height ; tall++){
        for (int space=0; space <= height-tall-2; space++){
            printf(" ");
        }      
        for (int hash=0; hash <= tall+1; hash++){
            printf("#"); 
        }
        printf("\n");
    }
}
