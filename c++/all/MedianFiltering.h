#ifndef MEDIANFILTERING_H
#define MEDIANFILTERING_H

//----------------------------------------------------------------------------//
// Template for reading portable gray map files (*.pgm)                       //
//                                                                            //
//                                                Ricardo Rosales                    //
//                                                March 1, 2023               //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//         Prototype declarations                                             //
//----------------------------------------------------------------------------//

void medianHeading();
void medianOpenfiles();
void medianReadhdr();
void medianAddhdr();
void medianUserdefined();
void medianClosefiles();

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

int medianFiltering()
{
  // Display heading
  medianHeading();
  // Open Input and Output Image Files
  medianOpenfiles();
  // Read header from image file
  medianReadhdr();
  // Add header to output file
  medianAddhdr();
  // Execute userdefined procedure
  medianUserdefined();
  // Close all image files
  medianClosefiles();

  printf("\n Bye! Bye!\n");
  system("PAUSE");
  return(1);
} // end main ()

//----------------------------------------------------------------------------//
//         Headings                                                           //
//----------------------------------------------------------------------------//

void medianHeading()
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

void medianOpenfiles()
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

void medianReadhdr()
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

void medianAddhdr()
{
  fprintf(outfptr, "P5\n%d %d\n%d\n", NCols, MRows, 255);
} // addhdr ()

//----------------------------------------------------------------------------//
//         sort Mask, based on bubble sort                                    //
//----------------------------------------------------------------------------//

void sort(unsigned char arr[], int n)
{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

//----------------------------------------------------------------------------//
//         Median Filtering                                                   //
//         To remove salt and pepper noise                                    //
//----------------------------------------------------------------------------//

void medianUserdefined()
{
  unsigned char Pixel;
  unsigned char mat[512][512];
  unsigned char medianmat[512][512];
  int col, row;
  unsigned char mask[9];

  // Read input image and store in both matrices
  for (row = 0; row < MRows; row++)
    for (col = 0; col < NCols; col++)
    {
      Pixel = fgetc(infptr);
      mat[col][row] = Pixel;
      medianmat[col][row] = Pixel;
    }

  // Fill Neighborhood
  for (row = 1; row < MRows - 1; row++)
    for (col = 1; col < NCols - 1; col++)
    {
      mask[0] = mat[col - 1][row - 1];
      mask[1] = mat[col][row - 1];
      mask[2] = mat[col + 1][row - 1];
      mask[3] = mat[col - 1][row];
      mask[4] = mat[col][row];
      mask[5] = mat[col + 1][row];
      mask[6] = mat[col - 1][row + 1];
      mask[7] = mat[col][row + 1];
      mask[8] = mat[col + 1][row + 1];
      // Sort Neighborhood
      sort(mask, 9);
      // Save median value
      medianmat[col][row] = mask[4];
    }

  // printf("Fisrt convolved pixel = %d \n",conv[1][1]);

  // Save convolved image
  for (row = 0; row < MRows; row++)
    for (col = 0; col < NCols; col++)
    {
      Pixel = medianmat[col][row];
      fputc(Pixel, outfptr);
    }
} // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void medianClosefiles()
{
  fclose(infptr);
  fclose(outfptr);
} // end closefiles ()

#endif