#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int population;
    do
    {
        population = get_int("Enter starting population: ");
    }
    while (population < 9);

    // Prompt for end size
    int expected_population;
    do
    {
        expected_population = get_int("Enter expected population: ");
    }
    while (expected_population < population);


    //  Calculate number of years until we reach threshold
    int years = 0;
    while (population < expected_population)
    {
        population += (population / 3) - (population / 4);
        years++;
    }

    // Print number of years
    printf("Years: %i", years);
}
