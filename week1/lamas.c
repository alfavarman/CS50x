#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt user for size of population
    int population;
    do
    {
        population = get_int("Starting population size: ");
    } while (population < 9);


    // propmpt user for expected population
    int expected_population;
    do
    {
        expected_population = get_int("Expected population size: ");
    } while (expected_population <= population);


    int years = 0;
    while (population < expected_population)
    {
        population += population/12;
        years++;
    }

    // print numbers of years rquired
    printf("years: %i\n", years);

}
