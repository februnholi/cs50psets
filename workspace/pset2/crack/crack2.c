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
    
    

    char salt[3];
    char password[] = "rofl";
    strncpy(salt, argv[1], 2);
    salt[2] = '\0';
    printf ("%s\n", salt);
    printf ("%s\n", password);
    printf ("%s\n", crypt(password, salt));
    return 0;
}