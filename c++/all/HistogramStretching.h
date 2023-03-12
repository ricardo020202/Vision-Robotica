#ifndef HISTOGRAMSTRETCHING_H
#define HISTOGRAMSTRETCHING_H

//----------------------------------------------------------------------------//
// Template for reading portable gray map files (*.pgm)                       //
//                                                                            //
//                                                Ricardo Rosales                    //
//                                                March 10, 2023           //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//         Prototype declarations                                             //
//----------------------------------------------------------------------------//

void histStHeading();
void histStOpenfiles();
void histStReadhdr();
void histStAddhdr();
void histStUserdefined();
void histStClosefiles();

//----------------------------------------------------------------------------//
//         Include declarations                                               //
//----------------------------------------------------------------------------//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------//
//         Variable declarations                                              //
//----------------------------------------------------------------------------//

int MRows, NCols;                  /* Number of Rows and columns in image */
FILE *infptr, *outfptr, *outfptrh; /* Input and output file pointers */
char infile[40];                   /* Name of input file */
char outfile[40];                  /* Name of output file */

//----------------------------------------------------------------------------//
//         Main program                                                       //
//----------------------------------------------------------------------------//

int histSt()
{
  // Display heading
  histStHeading();
  // Open Input and Output Image Files
  histStOpenfiles();
  // Read header from image file
  histStReadhdr();
  // Add header to output file
  histStAddhdr();
  // Execute userdefined procedure
  histStUserdefined();
  // Close all image files
  histStClosefiles();

  printf("\n Bye! Bye!\n");
  system("PAUSE");
  return (1);
}

//----------------------------------------------------------------------------//
//         Headings                                                           //
//----------------------------------------------------------------------------//

void histStHeading()
{
  int i;
  for (i = 0; i < 16; i++)
    printf("                                    +                       \n");
  printf("                      Digital Image Processing in C         \n");
  printf("                         Date: March 10, 2023            \n");
  printf("                            Author: Ricardo Rosales                \n");
  for (i = 0; i < 3; i++)
    printf("                                    +                       \n");
  return;
} // end heading ()

//----------------------------------------------------------------------------//
//         Openfiles                                                          //
//----------------------------------------------------------------------------//

void histStOpenfiles()
{
  printf("\n Opening Input and Output image files\n");
  printf(" Enter name of *.pgm INPUT image file (example: lena.pgm) ");
  scanf("%s", &infile);

  // Check if input file exists
  if ((infptr = fopen(infile, "rb")) == NULL)
  {
    printf(" Cannot open input image file: %s\n", infile);
    printf(" Exiting program...\n");
    system("PAUSE");
    exit(1);
  }

  printf(" Enter name of *.pgm OUTPUT image file (example: lenaout.pgm) ");
  scanf("%s", &outfile);

  // Check if output file was created succesfully
  if ((outfptr = fopen(outfile, "wb")) == NULL)
  {
    printf(" Cannot create output image file: %s\n", outfile);
    printf(" Exiting program...\n");
    system("PAUSE");
    exit(1);
  }

  // If this point is reached, file are OK
  printf(" File opened and created OK! \n\n");

} // end openfiles ()

//----------------------------------------------------------------------------//
//         Read Header                                                        //
//----------------------------------------------------------------------------//

void histStReadhdr()
{
  int i = 0, MaxRGB;
  char c, buffer[128];

  // Read header of PGM file
  printf("\n\n File <%s> Header: \n", infile);

  do
  {
    c = fgetc(infptr);
    buffer[i] = c;
    i++;
  } while (c != '\n');

  // Check if file is P5 (pgm) format
  if (buffer[1] == '5')
    printf("\n Input file is pgm, OK\n");
  else
  {
    printf("\n Input file is NOT pgm, Exiting program...\n");
    system("PAUSE");
    exit(0);
  }

  // File is pgm, read rest of header
  fscanf(infptr, "%d %d %d", &NCols, &MRows, &MaxRGB);
  c = fgetc(infptr);
  printf("%d ", NCols);
  printf("%d   <---- Width x Height) \n", MRows);
  printf("%d   <---- Max. Grayscale level) \n\n", MaxRGB);
} // end readhdr ()

//----------------------------------------------------------------------------//
//         Add Header                                                         //
//----------------------------------------------------------------------------//

void histStAddhdr()
{
  fprintf(outfptr, "P5\n%d %d\n%d\n", NCols, MRows, 255);
} // addhdr ()

//----------------------------------------------------------------------------//
//         Histogram stretching                                               //
//----------------------------------------------------------------------------//

void histStUserdefined()
{
  unsigned char Pixel;
  // Matrix variables
  unsigned char mat[512][512];
  int col, row;
  // Initial Maximum and Minimum pixel values
  int max = 0;
  int min = 255;
  // Correction factor
  float ScaleFactor;

  // Read input image
  for (row = 0; row < MRows; row++)
    for (col = 0; col < NCols; col++)
    {
      // Read Pixel
      Pixel = fgetc(infptr);
      // Store Pixel in Matrix
      mat[col][row] = Pixel;
      // Determine if a new minimum or maximum pixel value is found
      if (Pixel < min)
        min = Pixel;
      if (Pixel > max)
        max = Pixel;
    }

  printf("Minimum pixel value found:%d\n", min);
  printf("Maximum pixel value found:%d\n", max);

  // Calculate correction Factor
  ScaleFactor = 255.0 / (max - min);

  // Adjust image to stretch histogram
  for (row = 0; row < MRows; row++)
    for (col = 0; col < NCols; col++)
    {
      // Real Pixel from matrix
      Pixel = mat[col][row];
      // Shift and apply ScaleFactor
      Pixel = (Pixel - min) * ScaleFactor;
      // Save in outpu file
      fputc(Pixel, outfptr);
    }

} // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void histStClosefiles()
{
  fclose(infptr);
  fclose(outfptr);
} // end closefiles ()

#endif