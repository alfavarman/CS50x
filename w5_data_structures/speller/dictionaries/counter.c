#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 45

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    int total_words = 0;
    int words_up_to_4 = 0;
    int words_5 = 0;
    int words_6 = 0;
    int words_7 = 0;
    int words_8 = 0;
    int words_9 = 0;
    int words_10 = 0;
    int words_11 = 0;
    int words_12 = 0;
    int words_13 = 0;
    int words_14 = 0;
    int words_15 = 0;
    int words_16 = 0;
    int words_17_or_more = 0;

    char word[MAX_WORD_LENGTH + 1];
    int len;
    while (fscanf(fp, "%s", word) == 1)
    {
        len = 0;
        for (int i = 0; word[i] != '\0'; i++)
        {
            if (isalpha(word[i])) {
                len++;
            }
        }
        if (len > MAX_WORD_LENGTH)
        {
            continue;
        }

        total_words++;

        if (len <= 4)
        {
            words_up_to_4++;
        }
        else if (len == 5)
        {
            words_5++;
        }
        else if (len == 6)
        {
            words_6++;
        }
        else if (len == 7)
        {
            words_7++;
        }
        else if (len == 8)
        {
            words_8++;
        }
        else if (len == 9)
        {
            words_9++;
        }
        else if (len == 10)
        {
            words_10++;
        }
        else if (len == 11)
        {
            words_11++;
        }
        else if (len == 12)
        {
            words_12++;
        }
        else if (len == 13)
        {
            words_13++;
        }
        else if (len == 14)
        {
            words_14++;
        }
        else if (len == 15)
        {
            words_15++;
        }
        else if (len == 16)
        {
            words_16++;
        }
        else if (len > 16)
        {
            words_17_or_more++;
        }
    }

    printf("Total number of words: %i\n", total_words);
    printf("Number of words up to 4 letters: %i\n", words_up_to_4);
    printf("Number of words with 5 letters: %i\n", words_5);
    printf("Number of words with 6 letters: %i\n", words_6);
    printf("Number of words with 7 letters: %i\n", words_7);
    printf("Number of words with 8 letters: %i\n", words_8);
    printf("Number of words with 9 letters: %i\n", words_9);
    printf("Number of words with 10 letters: %i\n", words_10);
    printf("Number of words with 11 letters: %i\n", words_11);
    printf("Number of words with 12 letters: %i\n", words_12);
    printf("Number of words with 13 letters: %i\n", words_13);
    printf("Number of words with 14 letters: %i\n", words_14);
    printf("Number of words with 15 letters: %i\n", words_15);
    printf("Number of words with 16 letters: %i\n", words_16);
    printf("Number of words with 17+ letters: %i\n", words_17_or_more);

    fclose(fp);
    return 0;
}
