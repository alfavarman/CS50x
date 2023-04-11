// Implements a dictionary's functionality

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "dictionary.h"

#define TABLE_SIZE 65536

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = TABLE_SIZE;

// Hash table
node *table[N] = { NULL };

unsigned int dict_size = 0;

// is aeiouy
bool is_aeiouy(char letter)
{
    letter = tolower(letter);
    if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' || letter == 'y')
    {
        return true;
    }
    return false;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase
    char word_lc[LENGTH + 1];
    int wrord_len = strlen(word);
    for (int i = 0; i < wrord_len; i++)
    {
        word_lc[i] = tolower(word[i]);
    }
    word_lc[wrord_len] = '\0';

    node *cursor = table[hash(word_lc)];
    while (cursor)
    {
        if (strcmp(cursor->word, word_lc) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
// TODO: Improve this hash function
// return (toupper(word[0]) - 'A') ;
// unsigned int hash(const char* word)
{
    // is used on lowercase words only
    const unsigned int small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
    const unsigned int high_primes[] = {131, 137, 139, 149, 151, 157, 163, 167};

    const char *phrase = "LxS+;k0mqC=/";
    int len_word = strlen(word);

    unsigned int hash = 0;
    char first_l = word[0];
    char midd_l = word[(len_word - 1) / 2];
    char last_l = word[len_word - 1];

    hash += (is_aeiouy(first_l) ? high_primes[5] : small_primes[0]);
    hash += (is_aeiouy(midd_l) ? high_primes[3] : small_primes[1]);
    hash += (is_aeiouy(last_l) ? high_primes[0] : small_primes[2]);
    hash += (first_l == midd_l) ? high_primes[6] : small_primes[5];
    hash += (first_l == last_l) ? high_primes[7] : small_primes[6];
    hash += (last_l == midd_l) ? high_primes[4] : small_primes[7];

    unsigned int hash_first_l = (((int) first_l + (int) phrase[0] * len_word) % high_primes[4]);
    unsigned int hash_midd_l = (((int) midd_l * len_word * (len_word - 1) * phrase[1]) % high_primes[7]);
    unsigned int hash_last_l = (((int) last_l / phrase[2]) - ('Z' - len_word) % high_primes[5]);

    unsigned int factor_a = (len_word % 2 == 0) ? len_word * small_primes[len_word % 8] * (word[len_word / 4]) :
                            len_word + high_primes[len_word % 8] * (word[len_word / 4]);

    unsigned int factor_b = ((hash_first_l + hash_midd_l + hash_last_l) % 2 == 0) ?
                            pow(hash_first_l - (word[len_word / 2]) + hash_midd_l + hash_last_l + phrase[6], 1.3) :
                            pow(hash_first_l - hash_midd_l + (word[3 * len_word / 4]) - len_word - phrase[7], 1.7);

    unsigned int factor_c = (last_l % 2 == 0) ?
                            sin(hash_last_l * hash_first_l * phrase[8]) + (word[len_word / 2]) :
                            sin(len_word) / hash_midd_l - phrase[9];

    unsigned int factor_d = (last_l % 2 == 0) ?
                            log10(hash_last_l * hash_first_l * (word[3 * len_word / 4])) :
                            log10(len_word) + phrase[10] + (word[3 * len_word / 4]);

    hash += ((hash_first_l - phrase[3] * 0.3) * ('z' - (double) last_l) * factor_a) * (factor_c + factor_b) * factor_d * 0.001;

    return hash % TABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open file %s\n", dictionary);
        return false;
    }

    char word_buffer[LENGTH + 1];

    // while (fread(word_buffer, sizeof(char * (LENGTH + 1)), 1, dict) == 1) fread is faster than fscanf
    //  while (read string) is successful
    while (fscanf(dict, "%s", word_buffer) != EOF)
    {

        // create node and allocate memory for it
        node *new_word = calloc(1, sizeof(node));
        if (new_word == NULL)
        {
            printf("Error allocating memory...");
            return false;
        }

        // copy string buffer to node
        // if (strcpy(new_word->word, word_buffer) == NULL) hadle overflow
        if (strncpy(new_word->word, word_buffer, sizeof(new_word->word)) == NULL)
        {
            printf("Copying error...");
            // free all previously successful allocations before exiting
            free(new_word);
            // free_ll(table);
            return false;
        }

        // hash hash(word) == get index
        unsigned int index = hash(word_buffer);

        new_word->next = table[index];
        table[index] = new_word;

        // increment the dict_size count
        dict_size++;


        // Clear word_buffer before reading the next word
        memset(word_buffer, 0, sizeof(word_buffer));

    }

    // close the dictionary file
    fclose(dict);

    // return success
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

bool free_ll(node *ll_head)
{
    node *cursor = ll_head;
    while (cursor != NULL)
    {
        node *next = cursor->next;
        free(cursor);
        cursor = next;
    }
    return true;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    unsigned int i = 0;
    while (i < TABLE_SIZE)
    {
        if (table[i] != NULL)
        {
            if (!free_ll(table[i]))
            {
                return false;
            }
        }

        i++;
    }
    return true;
}


///////////////////////////////////////////

// inside dictionaries counter.c helps understand data input to be hashed.
// hash_validator.c helps validate collisions

// sources of knowelage:
// "Choosing a good hashing function" by Jeff Preshing: This blog post discusses the importance of using a good hash function, and provides some tips for choosing one. It recommends using a prime number for the table size, as this can help to reduce collisions.
// Link: https://preshing.com/20110504/hash-collision-probabilities/

// "Hash Tables" by Data Structures and Algorithms in Python: This book provides an overview of hash tables and discusses various techniques for choosing a good hash function. It recommends using a load factor in the range of 0.7 to 0.8 for best performance.
// Link: https://books.google.com/books?id=ZnFtDwAAQBAJ&pg=PA387

// "Hash table" on Wikipedia: This article provides a general overview of hash tables, including information about hash functions and load factors. It notes that using a prime number for the table size can help to reduce collisions, and that a load factor of around 0.7 to 0.8 is typically used in practice.
// Link: https://en.wikipedia.org/wiki/Hash_table

// Oxford English Corpus: This corpus contains over 2 billion words of English from a range of sources, including books,
// newspapers, and websites. According to a report on the corpus published in 2014, the most common word length in English
// is 5 letters, and words of length 15 or more make up less than 0.1% of all words.
// https://ota.bodleian.ox.ac.uk/repository/xmlui/bitstream/handle/20.500.12024/2554/2554.html

// Google Books Ngram Viewer: This tool allows you to search for the frequency of words or phrases in a large corpus of
// books from different time periods. According to the Ngram Viewer, words of length 15 or more are relatively rare in English,
// making up less than 0.05% of all words.
// https://books.google.com/ngrams

// Merriam-Webster Dictionary: According to a blog post on the Merriam-Webster website, the average length of words in
// the dictionary is around 9 letters, and only about 2% of words have more than 15 letters.
// https://www.merriam-webster.com/words-at-play/how-many-words-in-the-english-language


///////////////////////////////////////////
// code generated on the way to achive final function
// Hashes word to a number
// unsigned int standard_hash(const char *word, int len_word)
// {
//     unsigned int hash = 0;
//     for (int i = 0; i < len_word; i++)
//     {
//         hash += (int) word[i] * (i + 1);
//     }
//     return hash % TABLE_SIZE;
// }

// unsigned int advanced_hash(const char *word, int len_word)
// {
//     unsigned int hash = 0;
//     char first_l = tolower(word[0]);
//     char last_l = tolower(word[len_word - 1]);
//     double x = (pow((double) first_l, 2.0) * pow((double) last_l, 2.0) + (len_word - 2) * 0.1) / log(len_word);
//     hash = x;
//     return hash % TABLE_SIZE;
// }
// unsigned int long_hash(const char *word, int len_word)
// {
//     unsigned int hash;
//     hash = ((len_word / 2)* (int)(tolower(word[0]))/2 * (int)(tolower(word[len_word - 1]) - 'z')) % TABLE_SIZE;
//     return (unsigned int) hash;

// }
// unsigned int hash(const char *word)
// {
//     int len_word = strlen(word);
//     if (len_word <= SHORT)
//     {
//         return complex_hash(word, len_word, "LxS+;k0mqC=/");
//     }

//     else if (SHORT < len_word && len_word <= MEDIUM)
//     {
//         return complex_hash(word, len_word, "LxS+;k0mqC=/");
//     }

//     else if (MEDIUM < len_word && len_word <= LONG)
//     {
//     return complex_hash(word, len_word, "LxS+;k0mqC=/");
//     }

//     else if (len_word > LONG)
//     {
//         return complex_hash(word, len_word, "LxS+;k0mqC=/");
//     }

//     return 0;
// }
