#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define BUFFER_SIZE 1024

typedef struct {
    unsigned int hash;
    unsigned int count;
} hash_count;

int compare_hash_count(const void* a, const void* b)
{
    const hash_count* ha = (const hash_count*)a;
    const hash_count* hb = (const hash_count*)b;
    return hb->count - ha->count;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s dictionary_file table_size\n", argv[0]);
        return 1;
    }

    FILE *fp;
    char buffer[BUFFER_SIZE];


    // Initialize hash count array
    unsigned int table_size = atoi(argv[2]);
    hash_count hash_counts[table_size];
    memset(hash_counts, 0, table_size * sizeof(hash_count));

    // Open dictionary file
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read words from dictionary file and hash them
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Hash word
        unsigned int h = hash(buffer) % table_size;

        // Increment hash count
        hash_counts[h].count++;
        hash_counts[h].hash = h;
    }

    // Close dictionary file
    fclose(fp);

    // Count number of different hashes and collisions
    int num_hashes = 0;
    int num_collisions = 0;
    for (int i = 0; i < table_size; i++) {
        if (hash_counts[i].count > 0) {
            num_hashes++;
            if (hash_counts[i].count > 1) {
                num_collisions += hash_counts[i].count - 1;
            }
        }
    }
    // Sort and print the top 10 hash counts
    qsort(hash_counts, table_size, sizeof(hash_count), compare_hash_count);

    printf("Table size: %d ", table_size);
    printf("Number of collisions: %d \n", num_collisions);
    printf("Number of different hashes used: %d\n ", num_hashes);

    printf("Top 10 most frequently occurring hashes:\n");
    for (int i = 0; i < 10 && i < table_size; i++) {
        printf("%d: %d occurrences\n", hash_counts[i].hash, hash_counts[i].count);
    }

    return 0;
}
