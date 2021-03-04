#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// TODO: ensure the original case of the message is preserved, current I force everything to lowercase

int main(int argc, string argv[]) {

    int key_len = strlen(argv[1]);

    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    if(argc != 2) {
        printf("Usage: %s\n", argv[0]);
        return 1;

    }

    else if(key_len != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string plaintext = get_string("Pass in your text to be enciphered: \n");
    int text_len = strlen(plaintext);

    for(int i = 0; i < text_len; i++) {
        if(isalpha(plaintext[i])) {
            plaintext[i] = tolower(plaintext[i]);
    } else {
        plaintext[i] = plaintext[i];
    }}

    for(int i = 0; i < key_len; i++) {
        argv[1][i] = tolower(argv[1][i]);
    }

    int loc[text_len];


    for(int i = 0; i < text_len; i ++){
        for(int j = 0; j < 26; j++) {
            if(ispunct(plaintext[i]) != 0 || isdigit(plaintext[i]) != 0) {
                loc[i] = plaintext[i];
            }
            else if(plaintext[i] == ' ') {
                loc[i] = ' ';
            }
            else if(isalpha(plaintext[i]) != 0 && (char) plaintext[i] == (char) alphabet[j]) {
                loc[i] = j;
            }
        }

        }

    for(int i = 0; i < text_len; i++) {
        for(int j = 0; j < key_len; j++) {
            if(loc[i] == j) {
                printf("%c",argv[1][j]);
            }}
        if(ispunct(loc[i]) != 0 || isdigit(loc[i]) != 0 ){
            printf("%c", loc[i]);
        }
        else if(loc[i] == ' ') {
            printf("%c",loc[i]);
        }
        }
    printf("\n");

}



