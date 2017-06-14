#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    
    int count = 0;
    FILE *img = NULL;
    
    while (1)
    {
        BYTE jpg[BLOCKSIZE] = {};
        for (int k = 0; k < BLOCKSIZE; k++)
        {
            if (feof(file))
            {
                fclose(file);
                if (img != NULL)
                {
                    fclose(img);
                }
                return 0;
            }
        
            fread(&jpg[k], sizeof(BYTE), 1, file);
        }
        
        if (jpg[0] == 0xff && jpg[1] == 0xd8 && jpg[2] == 0xff && (jpg[3] == 0xe0 || jpg[3] == 0xe1))
        {
            if(img != NULL)
            {
                fclose(img);    
            }
            char filename[10];
            sprintf(filename,"%3i.jpg", count);
            img = fopen(filename, "w");
            
            if (img == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", filename);
                return 2;
            }
            
            fwrite(&jpg[0], sizeof(BYTE) * BLOCKSIZE, 1, img);
            count++;
            
        }
        else if (img != NULL)
        {
            fwrite(&jpg[0], sizeof(BYTE) * BLOCKSIZE, 1, img);
        }
    }
    fclose(file);
    return 0;
}