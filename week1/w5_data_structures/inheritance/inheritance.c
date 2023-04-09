// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// return random allel from given ancestor
char get_ancestor_random_allele(person ancestor)
{
    return (char)(ancestor.alleles[rand() % (sizeof(ancestor.alleles) / sizeof(ancestor.alleles[0]))]);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    //  Allocate memory for new person
    person *new_person = calloc(1, sizeof(person));
    if (new_person == NULL)
    {
        printf("Not enough memory!");
        free(new_person);
        return NULL;
    }

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set parent pointers for current person
        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        //  Randomly assign current person's alleles based on the alleles of their parents
        new_person->alleles[0] = get_ancestor_random_allele(*new_person->parents[0]);
        new_person->alleles[1] = get_ancestor_random_allele(*new_person->parents[1]);

    }

    // If there are no generations left to create
    else
    {
        // Set parent pointers to NULL
        // calloc initialize all values to 0

        //  Randomly assign alleles
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();

    }

    // Return newly created person
    return new_person;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Free parents recursively
    if (p->parents[0] != NULL)
    {
        free_family(p->parents[0]);
    }

    if (p->parents[1] != NULL)
    {
        free_family(p->parents[1]);
    }

    // Free child
    free(p);

}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}


// inheritance/ $ valgrind ./inheritance
// ==18193== Memcheck, a memory error detector
// ==18193== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
// ==18193== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
// ==18193== Command: ./inheritance
// ==18193== 
// Child (Generation 0): blood type AB
//     Parent (Generation 1): blood type AA
//         Grandparent (Generation 2): blood type BA
//         Grandparent (Generation 2): blood type AA
//     Parent (Generation 1): blood type BB
//         Grandparent (Generation 2): blood type BO
//         Grandparent (Generation 2): blood type AB
// ==18193== 
// ==18193== HEAP SUMMARY:
// ==18193==     in use at exit: 0 bytes in 0 blocks
// ==18193==   total heap usage: 7 allocs, 7 frees, 168 bytes allocated
// ==18193== 
// ==18193== All heap blocks were freed -- no leaks are possible
// ==18193== 
// ==18193== For lists of detected and suppressed errors, rerun with: -s
// ==18193== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)