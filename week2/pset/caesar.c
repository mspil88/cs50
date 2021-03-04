#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int atoi(const char *nptr);

int main(int argc, string argv[]) {

    int key;

    if(argc != 2) {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }
    else if(isdigit(*argv[1]) == 0) {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }
    else {
        printf("Looks good, the key is %s\n", argv[1]);
        key = atoi(argv[1]);


    }

    string plaintext = get_string("Pass in your text to be enciphered: \n");
    int n = strlen(plaintext);

    for(int i = 0; i < n; i++) {
        if(isdigit(plaintext[i])==0 && islower(plaintext[i]) != 0) {
        printf("%c",(int) ((plaintext[i]-97+key) % 26)+97);
    } else if(isdigit(plaintext[i])==0 && isupper(plaintext[i]) != 0)  {
        printf("%c",(int) ((plaintext[i]-65+key) % 26)+65);
    } else if(plaintext[i] == ' ') {
        printf(" ");
    } else {
        printf("%c", plaintext[i]);
    }


} printf("\n");
  return 0;
}
