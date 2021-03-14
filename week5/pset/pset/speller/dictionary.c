// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <strings.h>

char* lower_case(char* word);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    int hash_value;
    char word_cpy[strlen(word)+1];

    strcpy(word_cpy, word);
    puts(lower_case(word_cpy));


    hash_value = hash(word_cpy);


    for(node *temp = table[hash_value]; temp != NULL; temp = temp-> next) {
        if(strcmp(temp->word, word_cpy) == 0) {
            return true;
        }
    }  return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    for(int i = 0; word[i] != '\0'; i++){
        hash = 31*hash + word[i];

    }
    return hash % N;


}

int word_count = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if(file == NULL) {
        return 1;
    }




    char word[LENGTH+1]; //revist this, seems too large

    while(fscanf(file, "%s", word)==1) {
        //printf("%s\n", word);
        node *n = malloc(sizeof(node));
        if(n == NULL) {
            return 1;
        }

        n -> next = NULL;

        int hash_value;
        word_count ++;
        //strcpy(n->word, lower_case(word));
        strcpy(n->word, word);
        //printf("%s\n", n->word);
        hash_value = hash(word);
        //printf("%i\n", hash_value);
        n -> next = table[hash_value];
        table[hash_value] = n;
        //printf("%n\n", n->next);

    }
    fclose(file);

    return true;
}

char* lower_case(char* word) {

    for(char *p = word; *p; p++) *p = tolower(*p);
    return word;

}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++) {
        for(node *cursor = table[i]; cursor != NULL; cursor = cursor-> next) {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
            return true;

        }
    }
    return false;
}
