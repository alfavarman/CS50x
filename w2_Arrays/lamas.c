#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int population;
    do
    {
        population = get_int("Enter starting population: ");
    }
    while (population < 9);

    // TODO: Prompt for end size
    int expected_population;
    do
    {
        expected_population = get_int("Enter expected population: ");
    }
    while (expected_population < population);


    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (population < expected_population)
    {
        population += (population / 3) - (population / 4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i", years);
}
