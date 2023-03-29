#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int validate_cm_arg(int cm_arg);

int main(int argc, int argv[])
{
    int cm_arg = argv[1];

    validate_cm_arg(cm_arg);




}

int validate_cm_arg(int cm_arg)
{
    if (!cm_arg)
    {
        printf("Usage: ./wordle wordsize");
        return 1;
    }
    else if (cm_arg < 5 && cm_arg > 8)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8");
        return 1;
    }
}

// get lenght of string
int len(string word)
{
    int len_w = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        len_w++;
    }

    return len_w;
}

bool isvalid_guess(int lword, string guess)
{
    if (isalpha(guess) && len(guess) == lword)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string get_guess(int lword)
{
    string guess;
    do
    {
        guess = get_string("You have 6 tires, to guess %i-letter word", lword);
    } while (isvalid_guess(lword, guess));
    return tolower(guess)    

}

