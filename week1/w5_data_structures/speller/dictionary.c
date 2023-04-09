// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "dictionary.h"

// def constants
#define SHORT 4
#define MEDIUM 9
#define LONG 13


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table

// PRIME NUMBER, and load factor = 0.8 of loaded data

// Hash table
node *table[TABLE_SIZE];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int standard_hash(const char *word, int len_word)
{
    unsigned int hash = 0;
    for (int i = 0; i < len_word; i++)
    {
        hash += (int) word[i] * (i + 1);
    }
    return hash % TABLE_SIZE;
}

unsigned int advanced_hash(const char *word, int len_word)
{
    unsigned int hash = 0;
    char first_l = tolower(word[0]);
    char last_l = tolower(word[len_word - 1]);
    double x = (pow((double) first_l, 2.0) * pow((double) last_l, 2.0) + (len_word - 2) * 0.1) / log(len_word);
    hash = x;
    return hash % TABLE_SIZE;
}

unsigned int complex_hash(const char *word, int len_word)
{
    unsigned int hash = 0;
    char first_l = tolower(word[0]);
    char last_l = tolower(word[len_word - 1]);
    double factor_a, factor_b, factor_c;

    if (len_word % 2 == 0)
    {
        factor_a = len_word * 0.1;
    }
    else
    {
        factor_a = len_word * 100;
    }
    if (first_l == 'a' || first_l == 'e' || first_l == 'i' || first_l == 'o' || first_l == 'u' || first_l == 'y')
    {
        factor_b = 2468;
    }
    else
    {
        factor_b = 13579;
    }
    if ((int) last_l % 2 == 0)
    {
        factor_c = log10((int) last_l * (int) first_l);
    }
    else
    {
        factor_c = log10(len_word);
    }
    double x = (((double) first_l - 'a') * ('z' - (double) last_l) * factor_a) / factor_c + factor_b;
    hash = x;
    return hash % TABLE_SIZE;
}

unsigned int long_hash(const char *word, int len_word)
{
    unsigned int hash;
    hash = ((len_word / 2)* (int)(tolower(word[0])) * (int)(tolower(word[len_word - 1]) - 'z')) % TABLE_SIZE;
    return (unsigned int) hash;

}

unsigned int hash(const char *word)
{
    int len_word = strlen(word);
    if (len_word <= SHORT)
    {
        return standard_hash(word, len_word);
    }

    else if (SHORT < len_word && len_word <= MEDIUM)
    {
        return advanced_hash(word, len_word);
    }

    else if (MEDIUM < len_word && len_word <= LONG)
    {
    	return complex_hash(word, len_word);
    }

    else if (len_word > LONG)
    {
        return long_hash(word, len_word);
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
