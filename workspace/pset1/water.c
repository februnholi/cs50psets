#include <cs50.h>
#include <stdio.h>

int convert(int minutes);

int main(void)
{
    // Do while used to ensure user inserts a positive and more than zero number
    int minutes = -1;
    do
    {
    // ask for minutes from user
    printf("Minutes: ");    
    minutes = get_int();
    }
    while (minutes < 0);
    printf("Bottles: %i\n", convert(minutes));
}

int convert(int minutes)
{
    return minutes * 12;
}