#ifndef GREYTONEG_H
#define GREYTONEG_H

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

void g2nHeading();
void g2nOpenfiles();
void g2nReadhdr();
void g2nAddhdr();
void g2nUserdefined();
void g2nClosefiles();

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

int greyToNeg()
{
  // Display heading
  g2nHeading();
  // Open Input and Output Image Files
  g2nOpenfiles();
  // Read header from image file
  g2nReadhdr();
  // Add header to output file
  g2nAddhdr();
  // Execute userdefined procedure
  g2nUserdefined();
  // Close all image files
  g2nClosefiles();

  printf("\n Bye! Bye!\n");
  system("PAUSE");
  return (1);
} // end main ()

//----------------------------------------------------------------------------//
//         Headings                                                           //
//----------------------------------------------------------------------------//

void g2nHeading()
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

void g2nOpenfiles()
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

void g2nReadhdr()
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

void g2nAddhdr()
{
  fprintf(outfptr, "P5\n%d %d\n%d\n", NCols, MRows, 255);
} // addhdr ()

//----------------------------------------------------------------------------//
//         User defined section                                               //
//----------------------------------------------------------------------------//

void g2nUserdefined()
{
  // Pixel to read and transforms
  unsigned char Pixel;

  // Read image pixels and obtain negative value
  Pixel = fgetc(infptr);
  do
  {
    // Obtain 1s complement
    Pixel = 255 - Pixel;
    // Save pixel in output image
    fputc(Pixel, outfptr);
    // Read next pixel and check if last
    Pixel = fgetc(infptr);
  } while (!feof(infptr));
} // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void g2nClosefiles()
{
  fclose(infptr);
  fclose(outfptr);
} // end closefiles ()

#endif