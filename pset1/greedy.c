#include <stdio.h>
#include <cs50.h> // allows GetFloat()
#include <math.h> // allows round()

int main(void)
{
    float change;
    int count=0;
    
    printf("O hai! ");
    
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    } while (change <= 0);
    
    int cents = (int) round(change*100);
    
    //printf("You entered float: %f \n",change);
    //printf("You entered cents: %d \n",cents);     

    while (cents >= 25){
        cents -= 25;
        count++;
        //printf("Amt cents left: %d\n", cents);
        //printf("Count: %d\n", count);
    };
    
    while (cents >= 10){
        cents -= 10;
        count++;
        //printf("Amt cents left: %d\n", cents);
        //printf("Count: %d\n", count);
    };
    
    while (cents >= 5){
        cents -= 5;
        count++;
        //printf("Amt cents left: %d\n", cents);
        //printf("Count: %d\n", count);
    };
    
    while (cents >= 1){
        cents -= 1;
        count++;
    };

    printf("%d\n", count);
}
