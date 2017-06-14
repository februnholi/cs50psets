#include <cs50.h>
#include <stdio.h>

void pyramid(int height);

int main(void)
{
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
    for (int i = height; i > 0; i--)
    {
        for (int j = 0; j < height; j++)
        {
            if (j < i - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
    
            
        }
        printf("  ");
        for (int k = height; k > 0; k--)
        {
            if (k < i)
            {
                k = 0;
            }
            else
            {
                printf("#");
            }
        }
        printf("\n"); 
    }
}   