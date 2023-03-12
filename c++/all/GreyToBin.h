#ifndef GREYTOBIN_H
#define GREYTOBIN_H
//----------------------------------------------------------------------------//
// Template for reading portable gray map files (*.pgm)                       //
//                                                                            //
//                                                Ricardo Rosales                    //
//                                                Macrh 10, 2023           //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//         Prototype declarations                                             //
//----------------------------------------------------------------------------//

void g2bHeading();
void g2bOpenfiles();
void g2bReadhdr();
void g2bAddhdr();
void g2bUserdefined();
void g2bClosefiles();

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

int greyToBin()
{
  // Display heading
  g2bHeading();
  // Open Input and Output Image Files
  g2bOpenfiles();
  // Read header from image file
  g2bReadhdr();
  // Add header to output file
  g2bAddhdr();
  // Execute userdefined procedure
  g2bUserdefined();
  // Close all image files
  g2bClosefiles();

  printf("\n Bye! Bye!\n");
  system("PAUSE");
  return (1);
} // end main ()

//----------------------------------------------------------------------------//
//         Headings                                                           //
//----------------------------------------------------------------------------//

void g2bHeading()
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

void g2bOpenfiles()
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

void g2bReadhdr()
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

void g2bAddhdr()
{
  fprintf(outfptr, "P5\n%d %d\n%d\n", NCols, MRows, 255);
} // addhdr ()

//----------------------------------------------------------------------------//
//         User defined section                                               //
//----------------------------------------------------------------------------//

void g2bUserdefined()
{
  unsigned char Pixel;
  unsigned char Threshold = 127;

  // Read first pixel
  Pixel = fgetc(infptr);

  do
  {
    Pixel = (Pixel > Threshold) ? 255 : 0;

    // save pixel to output file
    fputc(Pixel, outfptr);

    // Read next pixel
    Pixel = fgetc(infptr);
  } while (!feof(infptr));

} // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void g2bClosefiles()
{
  fclose(infptr);
  fclose(outfptr);
} // end closefiles ()

#endif