#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Contact name: ");
    int age = get_int("Age: ");
    string number = get_string("Mobile: ");

    printf("Contact name: %s\n Age: %i\n Mobile: %s", name, age, number);

}