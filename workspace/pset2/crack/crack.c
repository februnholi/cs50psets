#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <crypt.h>

#define _XOPEN_SOURCE
#define _GNU_SOURCE         /* See feature_test_macros(7) */


int main(int argc, string argv[])
{
    // verify if number of arguments is correct
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    
    char alphabet[65];
    int i, j, k, l;
    
    // insert every possible character to array alphabet -> using ASCII table 
    for (i = 0; i < 64; i++)
    {
        if(i < 12)
        {
            j = i + 46;
            alphabet[i] = (char) j;
        }
        else if(i < 38)
        {
            j = i + 53;
            alphabet[i] = (char) j;
        }
        else 
        {
            j = i + 59;
            alphabet[i] = (char) j;
        }
    }

    // get salt from users input in argv
    char salt[3];
    strncpy(salt, argv[1], 2);
    salt[2] = '\0';


    int a, b, c, d;    
    char result[5];
    result[4] = '\0';
    
    // try every combination of password 64 ^ 4
    for (i = 0; i < 64; i++)
    {
        for (j = 0; j < 64; j++)
        {
            for (k = 0; k < 64; k++)
            {
                for (l = 0; l < 64; l++)
                {
                    // get i,j,k and l and store character value in int and then convert it back to char to store in result array, which will try passwords
                    // I know that there should be another way of copying strings, characters, but I could not find a better solution...
                    a = (int) alphabet[i];
                    b = (int) alphabet[j];
                    c = (int) alphabet[k];
                    d = (int) alphabet[l];
                    result[0] = (char) a;
                    result[1] = (char) b;
                    result[2] = (char) c;
                    result[3] = (char) d;
                    /* printf("%c%c%c%c\n", result[0], result[1], result[2], result [3]);
                    printf("%s\n", result); */
                    
                    // if hash using crypt function (password, salt) matches hash inputed, you cracked it! and print it.
                    if(strcmp(argv[1],crypt(result, salt)) == 0)
                    {
                        printf ("%s", result);
                        break;
                    } 
                }
            }
        }
    }
    return 0;
}