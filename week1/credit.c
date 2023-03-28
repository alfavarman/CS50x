#include <cs50.h>
#include <stdio.h>

void get_type_or_invalid(long number);

int main(void)
{
    // prompt user for positive number
    long card_no;

    do
    {
        card_no = get_long("Type Card Number(digits only): ");
    }
    while (card_no < 0);

    // validate number
    get_type_or_invalid(card_no);
    return 0;
}

// get lenght of number
int len(long number)
{
    int len_n = 0;

    while (number != 0)
    {
        number /= 10;
        len_n++;
    }

    return len_n;
}

// get_sum_of_numbers_from_last_digit 
int get_sum_1(long number)
{
    int sum_1 = 0;

    while (number != 0)
    {
        sum_1 += (number % 10);
        number /= 100;
    }
    return sum_1;
}

// get_sum_of_digits_multiplied_from_second_last
int get_sum_2(long number)
{
    int sum_2 = 0;
    number /= 10;
    while (number != 0)
    {
        sum_2 += (number % 10) * 2;
        number /= 100;
    }
    return sum_2;
}

// check if last digit of sums is 0
bool luhn(long number)
{
    if ((get_sum_1(number) + get_sum_2(number)) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// get a frist digit of a number
int first_digit(long number)
{
    int digit;
    while (number >= 10)
    {

        number /= 10;
    }
    digit = number % 10;
    return digit;

}

// get second digit of a number
int second_digit(long number)
{
    int digit;
    while (number >= 100)
    {
        number /= 10;
    }
    digit = number % 10;
    return digit;

}

// validator if valid get card provider else invalid 
void get_type_or_invalid(long number)
{
    int len_n = len(number);
    bool luhn_alg = luhn(number);

    if (len_n > 12 && len_n < 17 && luhn_alg)
    {
        int first = first_digit(number);
        int second = second_digit(number);
        if (len_n == 15 && first == 3 && (second == 4 || second == 7))
        {
            printf("AMEX\n");
        }

        else if (len_n == 16 && first == 5 && (second >= 1 && second <= 5))
        {
            printf("MASTERCARD\n");
        }

        else if ((len_n == 16 || len_n == 13) && first == 4)
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}


