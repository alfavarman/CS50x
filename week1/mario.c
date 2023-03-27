#include <cs50.h>
#include <stdio.h>

void print_pyramid(int number);

int main(void)
{
    // prompt user for int height
    int height;
    do
    {
        height = get_int("Pyramid Height 1-8: ");
    }
    while (1 > height || height > 8);

    // print piramid of >height<
    print_pyramid(height);

}

void print_pyramid(int number)
{
    for (int i = 1; i <= number; i++)
    {
        // print (number of spaces - number of hashes, number of hashes, double spaces, and number of hashes, next line)
        // printf(8-i * " " + i * "#" + "  " + i * "#" + "\n");
        // change number to 8 (constant height)
        for (int j = 1; j <= number - i; j++)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");

    }
}