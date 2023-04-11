// Declares a dictionary's functionality

// 4,5,20 make sure clang compiles lib once!
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define TABLE_SIZE 26  //4999 //9973 //29983  //65536 // 112501

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H







