/**
 * copy.c ----> resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece and resizes it, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize [n] infile outfile\n");
        return 1;
    }

    // resize multiple by factor_n
    int resize_multiple = atoi(argv[1]);
    if(resize_multiple < 0 || resize_multiple > 100)
		{
				printf("The resize factor should be a positive integer <= 100.\n");
				return 2;
		}
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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

    // construct bitmap headers for outfile   
    BITMAPFILEHEADER out_bf;
	BITMAPINFOHEADER out_bi;	

    out_bf = bf;
	out_bi = bi;
    
    out_bi.biHeight = bi.biHeight * resize_multiple;
    out_bi.biWidth = bi.biWidth * resize_multiple;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for outfile
    int outpadding =  (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Calculate file and image size
	out_bf.bfSize = 54 + out_bi.biWidth * abs(out_bi.biHeight) * 3 + abs(out_bi.biHeight) *  outpadding;
	out_bi.biSizeImage = ((((out_bi.biWidth * out_bi.biBitCount) + 31) & ~31) / 8) * abs(out_bi.biHeight);

    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //write scanline [resize_multiple] times
        for (int m = 0; m < resize_multiple; m++) 
        {    
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                //write RGB [resize_multiple] times
                for (int n = 0; n < resize_multiple; n++) 
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                // write RGB triple to outfile
                // fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
         
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < outpadding; k++)
            {
                fputc(0x00, outptr);
            }
            fseek(inptr, -(bi.biWidth * 3 + padding ), SEEK_CUR);
        }
        fseek(inptr, bi.biWidth * 3 + padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
