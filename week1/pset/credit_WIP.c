
# include <cs50.h>
# include <math.h>
# include <stdio.h>

/*I'm going to park this until I've covered arrays in C*/

int main(void) {

    int abs(int some_int);
    int card_number;
    int number_len;

    card_number = get_int("Please give me your card number: \n");
    number_len = floor(log10(abs(card_number)))+1;

    // loop backwards

    int i = -1;
    while(card_number) {
        i++;
        printf("%d", i);
        printf("%d", card_number % 10);
        card_number /= 10;
    }

    /*for(int i = number_len; i >= 0; i = i - 2) {
        printf("%d", i);
    }*/


    //for(int i )
}