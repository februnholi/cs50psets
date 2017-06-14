#include <cs50.h>
#include <stdio.h>

void pyramid(int height);

int main(void)
{
    // assure that height is positive and not higher than 23
    int height = -1;
    do
    {
    printf("Height: ");    
    height = get_int();
    }
    while (height < 0 || height > 23);
    pyramid(height);

}

void pyramid(int height)
{
int j;
    for (int i = 0; i < height; i++)
    {
        for (j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        for (j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("  ");
        for (j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n"); 
    }
}   