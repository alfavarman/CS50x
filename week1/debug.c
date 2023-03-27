#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user name and location
    string name = get_string("What is your name? ");
    string location = get_string("Where do you live? ");

    // printout welcome message
    printf("Hello, %s, from %s!", name, location);
}
