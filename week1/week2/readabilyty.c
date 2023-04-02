#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <cs50.h>

void print_grade(string text);

int main(void)
{
    string user_input_text;
    // get valid user text input - assuming single char string
    do
    {
        user_input_text = get_string("Text: ");
    }
    while (strlen(user_input_text) < 0);

    // print correct grade
    print_grade(user_input_text);

    return 0;
}

// count total letters of text
int get_text_letters(string text)
{
    int letters_count = 0;
    // loop thru string and increase letters counter if character is alphabetic
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            letters_count += 1;
        }
    }

    return letters_count;
}

// count total sentences of text
int get_text_sentences(string text)
{
    int sentence_count = 0;
    // loop thru the string and increase counter if string char is agreed end of sentence
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            sentence_count++;
        }
    }

    return sentence_count;
}

int get_text_words(string text)
// count number of words in the string. based on whitespaces +1
{
    int word_count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isspace(text[i]) && (!isspace(text[i + 1])))
        {
            word_count++;
        }
    }

    word_count++;
    return word_count;
}

int get_text_grade(string text)
// Coleman Liau index
{
    int grade;
    int words = get_text_words(text);
    float letters_per_100_words = ((float) get_text_letters(text) / words) * 100;
    float sentences_per_100_words = ((float) get_text_sentences(text) / words) * 100;
    grade = round((0.0588 * letters_per_100_words) - (0.296 * sentences_per_100_words) - 15.8);
    return grade;
}

void print_grade(string text)
// print grade according to the assigment
{
    int grade = get_text_grade(text);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", grade);
    }
}
