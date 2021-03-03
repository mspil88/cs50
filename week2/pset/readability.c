#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_characters(int n, string array);
int count_words(int n, string array);
int count_sentences(int n, string array);
int coleman_lau_index(int character_count, int word_count, int sentence_count);

int main(void) {

    string text = get_string("Enter your text: \n");
    int n = strlen(text);

    int n_chars = count_characters(n, text);
    int n_words = count_words(n, text);
    int n_sents = count_sentences(n, text);

    printf("Number of characters: %i\n", n_chars);
    printf("Number of words: %i\n", n_words);
    printf("Number of sentences: %i\n", n_sents);


    int cl_index = coleman_lau_index(n_chars, n_words, n_sents);

    if(cl_index < 1) {
        printf("Below Grade 1\n");
    }
    else if (cl_index >= 16) {
        printf("Above Grade 16\n");
    }
    else {
        printf("Grade: %i\n", cl_index);
    }

}

int count_characters(int n, string array) {

    int char_count = 0;
    int word_count = 0;

    for(int i = 0; i < n; i++ ) {
        if (isalpha(array[i]) > 0){
            char_count +=1;
        }
    }
    return char_count;
}

int count_words(int n, string array) {

    int word_count = 0;

    for(int i = 0; i < n; i++) {
        if(array[i] == ' ') {
            word_count += 1;
        }
    }
    return word_count+1;
}

int count_sentences(int n, string array) {

    int sentence_count = 0;

    for(int i = 0; i < n; i ++) {
        if(array[i] == '.' || array[i] == '?' || array[i] == '!') {
            sentence_count += 1;
        }
    }
    return sentence_count;
}

int coleman_lau_index(int character_count, int word_count, int sentence_count) {

    float word_per_100 = ((double) character_count / (double) word_count)*100;
    float sentence_per_100 = ((double) sentence_count / (double)word_count)*100;

    float cl_index = (0.0588 * word_per_100) - (0.296 * sentence_per_100) - 15.8;

    return round(cl_index);
}