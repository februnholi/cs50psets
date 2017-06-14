#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void print_initials (string s);

int main (void)
{
    // Ask user's name
    string name = get_string();
    
    // Call function to print name's initials
    print_initials(name);
    
    // Print a line in the end
    printf("\n");
}

void print_initials (string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //If it is at first, and not a space, it's an initial -> should be printed in uppercase
        if (i == 0 && s[i] != ' ')
        {
            printf("%c", toupper(s[i]));
        }
        //If it is preceded by space and is not a space, it's an initial -> should be printed in uppercase
        else if (s[i] != ' ' && s[i - 1] ==  ' ')
        {
            printf("%c", toupper(s[i]));
        }
    }
}