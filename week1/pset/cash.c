# include <stdio.h>
# include <cs50.h>
# include <math.h>

/* This works but it is a bit ugly, I'd like to investigate a more elegant way to do this one */

int main(void) {
    float paid;

    do {
        paid = get_float("Give me some cash: \n");
    } while (paid <= 0);

    paid = round(paid*100);

    float remaining = paid;
    int coins = 0;

    while(true) {

        while(remaining > 0) {
            remaining -= 25;
            coins ++;
                if(remaining < 0) {
                remaining +=25;
                coins -=1;
                break;

        } }

        while(remaining > 0) {
            remaining -= 10;
            coins ++;
                if(remaining < 0) {
                remaining +=10;
                coins -=1;
                break;

        } }

        while(remaining > 0) {
            remaining -= 5;
            coins ++;
                if(remaining < 0) {
                remaining +=5;
                coins -=1;
                break;

        } }

        while(remaining > 0) {
            remaining -= 1;
            coins ++;
                if(remaining < 0) {
                remaining +=1;
                coins -=1;
                break;

        } }
    break;


    } printf("The minimum number of coins is %d\n", coins);
}