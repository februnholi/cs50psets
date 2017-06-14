#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LOWERCASE_A 97
#define LOWERCASE_Z 122
#define UPPERCASE_A 65
#define UPPERCASE_Z 90


void cipher(char p, char k);

int main(int argc, string argv[])
{
    // verify if argument is incorrect
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    string k = argv[1];
    int k_length = strlen(k);

    // verify if all elements are alphanumeric
    for (int j = 0; j < k_length; j++)
    {
        if(isalpha(k[j]))
        {
        }
        else
        {
        printf("Usage: ./vigenere k\n");
        return 1;
        }
    }
    
    // ask for plaintext and store it in p
    printf("plaintext: ");
    string p = get_string();
    int p_length = strlen(p);
    k[p_length] = '\0';
    
    // call function to criptography
    printf("ciphertext: ");

    int i = -1;
    for(int z = 0; z < p_length; z++)
    {
        if(isalpha(p[z]))
        {
            i++;
        }
            cipher(p[z],k[i % k_length]);
    }

    // Change line to end code
    printf("\n");
    return 0;
}

void cipher(char p, char k)
{
    int aux = (int) p;

    //since K does not matter if uppercase or lowercase, set in lowercase and treated it in each if below as lowercase
    int c = (int) tolower(k);
        
        // verify if letter is lowercase
        if (aux >= LOWERCASE_A && aux <= LOWERCASE_Z)
        {
            aux = (((aux % (LOWERCASE_A)) + (c % LOWERCASE_A)) % 26) + (LOWERCASE_A);
            // (letter to be converted + k) converted to 1 - 26, then back to its range in ASCII
        }
        // verify if letter is uppercase
        else if (aux >= UPPERCASE_A && aux <= UPPERCASE_Z)
        {
            aux = (((aux % (UPPERCASE_A)) + (c % LOWERCASE_A)) % 26) + (UPPERCASE_A);
            // (letter to be converted + k) converted to 1 - 26, then back to its range in ASCII
        }

        printf("%c", (char) aux);
}