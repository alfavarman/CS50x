#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int population;
    do
    {
        population = get_int("Enter initial size of population: ");
    }
    while (population < 9);

    // TODO: Prompt for end size
    int expected_population;
    do
    {
        expected_population = get_int("Enter expexted size of population: ");
    }
    while (expected_population <= population);


    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (population < expected_population)
    {
        population += population / 12;
        years++;
    }

    // TODO: Print number of years
    printf("To reach expected size of population it will take %i years\n", years);
}
