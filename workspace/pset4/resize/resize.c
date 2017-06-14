/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // ensure n is between 1 and 100
    if (atof(argv[1]) < 0 || atof(argv[1]) > 100)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile - n should be between 0 and 100\n");
        return 1;
    }


    // remember filenames
    float n = atof(argv[1]);

    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

// TEM QUE COLOCAR AQUI AS MUDANÇAS NO FILE HEADER E NO INFO HEADER

    BITMAPFILEHEADER bfout;
    BITMAPINFOHEADER biout;    
    
    biout = bi;
    bfout = bf;

    biout.biWidth = (int) (n * bi.biWidth);
    biout.biHeight = (int) (n * bi.biHeight);

    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine padding for scanlines
    int paddingout = (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    biout.biSizeImage = ((sizeof(RGBTRIPLE) * biout.biWidth) + paddingout) * abs(biout.biHeight);
    bfout.bfSize = biout.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfout, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // COMECA AQUI!!!
    
    if (n >= 1)
    {
        // creates variable to control how SEEK_CUR should work after reading a row
        long int rr = bi.biWidth * sizeof(RGBTRIPLE);
        
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            for (int z = 0; z < n; z++)
            {
                // iterate over pixels in scanline
                for (int j = 0, biWidth = bi.biWidth; j < biWidth; j++)
                {
                    
                    // temporary storage
                    RGBTRIPLE triple;
        
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        
                    // write RGB triple to outfile n times 
                    for (int w = 0; w < n; w++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                
                // If not in the last iteration, move back to the beginning of the row in input file (to copy again to the next line)
                if (z != n - 1) 
                {
                    // skip over padding, if any
                    fseek(inptr, 0 - rr, SEEK_CUR);
                }
                else //skip padding, and go to next line
                {
                    fseek(inptr, padding, SEEK_CUR);
                }
        
                // Add padding to outputfile
                for (int k = 0; k < paddingout; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
    
        // close infile
        fclose(inptr);
    
        // close outfile
        fclose(outptr);
    
        // success
        return 0;
    }
    else
    {
        n = (int) (1 / n);
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0, biWidth = bi.biWidth; j < biWidth; j++)
            {

                RGBTRIPLE triple;
                
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                if (i % (int) n == 0 && j % (int) n == 0)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                
                fseek(inptr, padding, SEEK_CUR);
            }

            if (i % (int) n == 0)
            {// Add padding to outputfile
                for (int k = 0; k < paddingout; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
    
        // close infile
        fclose(inptr);
    
        // close outfile
        fclose(outptr);
    
        // success
        return 0;
    }
    
}
