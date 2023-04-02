#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    // prompt user for a min of range
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    // prompt user for a max of range
    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    // put each number in range into prime function
    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // 2 is first prime number
    if (number < 2)
    {
        return false;
    }
    else
    {
        // for int in range(2, number):
        for (int i = 2; i < number; i++)
        {
            // if number is divisible by int its not prmie.
            if (number % i == 0)
            {
                return false;
            }
        }
        return true;
    }

}
