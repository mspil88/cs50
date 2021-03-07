#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>


//Small program exploring recursion, enter a number as a command line argument and see it's factorial

long int fact(int n);

int main(int argc, string argv[]){

    if(argc != 2) {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }

    long conv = strtol(argv[1], NULL, 10);
    printf("The factorial of %s is %li\n", argv[1], fact(conv));


}

long int fact(int n) {
    if(n==0) {
        return 1;
    }
    else if(n==1) {
        return 1;
    }
    else {
        return n*fact(n-1);
    }
}