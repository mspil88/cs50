#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size

    int initial_population;
    int end_population;

    do {
        initial_population = get_int("Provide an initial population size: \n");

    } while (initial_population < 9);

    do {
        end_population = get_int("Provide a terminal population size: \n");
    } while (initial_population > end_population);

    int number_of_years = 0;
    int population = initial_population;

    while (population < end_population) {
        population += (population/3) - (population/4);
        number_of_years ++;

    }

    printf("Start size: %d\n", initial_population);
    printf("End size: %d\n", end_population);
    printf("Years: %d\n", number_of_years);

}