#include <cs50.h>
#include <stdio.h>

/* Function asks how many blocks to print and then prints a left align right triangle of them, e.g. if you request 8 blocks the following is printed:
#
##
###
####
#####
######
#######
########
*/  


int main(void) {
    int size;

    do {
        size = get_int("How many blocks do you want?\n");
    } while (size < 1);

    int dec = 0;
    for(int i = 0; i < size; i++) {

        dec +=1;
        for(int j = 0; j < dec; j++) {

            printf("#");
        }
        printf("\n");

    }
}

