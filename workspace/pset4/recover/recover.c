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
    
    // open file to be recovered
    FILE *file = fopen(argv[1], "r");
    
    // ensure it opens or crash 
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    
    int count = 0;
    //int z = 0;
    BYTE jpg[BLOCKSIZE] = {};
    FILE *img = NULL;
    
    while (1)
    {
        for (int k = 0; k < BLOCKSIZE; k++)
        {
            if (feof(file))
            {
                fclose(file);
                fclose(img);
                return 0;
            }
        
            fread(&jpg[k], sizeof(BYTE), 1, file);
        }
        
        // if it reads a JPG header -> close current .jpg file and opens a new one
        if (jpg[0] == 0xff && jpg[1] == 0xd8 && jpg[2] == 0xff && (jpg[3] & 0xf0) == 0xe0)
        {
            // if a jpg was started, closes it to open a new one
            if(img != NULL)
            {
                fclose(img);    
            }
            
            //open new jpg with name like "000.jpg"
            char filename[7];
            sprintf(filename,"%03d.jpg", count);
            img = fopen(filename, "w");
            
            // ensures no problem opening a new file
            if (img == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", filename);
                return 2;
            }
            
            fwrite(&jpg, sizeof(BYTE) * BLOCKSIZE, 1, img);
            count++;
            
        }
        // if not a new jpg (and a jpg is already initiated), continues copying blocks
        else if (img != NULL)
        {
            fwrite(&jpg, sizeof(BYTE) * BLOCKSIZE, 1, img);
        }
        

        //z++;
    }
    fclose(file);
    return 0;
}