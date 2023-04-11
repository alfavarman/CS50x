#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Whats Your name?: ");
    printf("hello, %s world\n", name);
}