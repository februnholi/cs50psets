#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LOWERCASE_A 97
#define LOWERCASE_Z 122
#define UPPERCASE_A 65
#define UPPERCASE_Z 90


void cipher(string p, int k);

int main(int argc, string argv[])
{
    // verify if number of arguments is correct
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    
    // Convert string to int
    int k = atoi(argv[1]);
        
    // ask for plaintext and store it in p
    printf("plaintext: ");
    string p = get_string();

    // call function to criptography
    cipher(p,k);

    // Change line to end code
    printf("\n");
    return 0;
}

void cipher(string p, int k)
{
    printf("ciphertext: ");
    int aux;
    
    // iterate over characters in p
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        aux = (int) p[i];
        // verify if letter is lowercase
        if (aux >= LOWERCASE_A && aux <= LOWERCASE_Z)
        {
            aux = (((aux % (LOWERCASE_A - 1)) + (k % 26)) % 26) + (LOWERCASE_A - 1);
            // (letter to be converted + k) converted to 1 - 26, then back to its range in ASCII
        }
        // verify if letter is uppercase
        else if (aux >= UPPERCASE_A && aux <= UPPERCASE_Z)
        {
            aux = (((aux % (UPPERCASE_A - 1)) + (k % 26)) % 26) + (UPPERCASE_A - 1);
            // (letter to be converted + k) converted to 1 - 26, then back to its range in ASCII
        }

        printf("%c", (char) aux);
    }
}