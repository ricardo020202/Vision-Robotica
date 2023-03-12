#ifndef RGBTOGREY_H
#define RGBTOGREY_H

//----------------------------------------------------------------------------//
// Template for reading portable pixel map files (*.ppm)                       //
//                                                                            //
//                                                Ricardo Rosales                    //
//                                                March 10, 2023           //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//         Prototype declarations                                             //
//----------------------------------------------------------------------------//

void rgb2gHeading();
void rgb2gOpenfiles();
void rgb2gReadhdr();
void rgb2gAddhdr();
void rgb2gUserdefined();
void rgb2gClosefiles();

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

int rgbToGrey()
{
  // Display heading
  rgb2gHeading();
  // Open Input and Output Image Files
  rgb2gOpenfiles();
  // Read header from image file
  rgb2gReadhdr();
  // Add header to output file
  rgb2gAddhdr();
  // Execute userdefined procedure
  rgb2gUserdefined();
  // Close all image files
  rgb2gClosefiles();

  printf("\n Bye! Bye!\n");
  system("PAUSE");
  return(1);
} // end main ()

//----------------------------------------------------------------------------//
//         Headings                                                           //
//----------------------------------------------------------------------------//

void rgb2gHeading()
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

void rgb2gOpenfiles()
{
  printf("\n Opening Input and Output image files\n");
  printf(" Enter name of *.ppm INPUT image file (example: lena.ppm) ");
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

void rgb2gReadhdr()
{
  int i = 0, MaxRGB;
  char c, buffer[128];

  // Read header of PPM file
  printf("\n\n File <%s> Header: \n", infile);

  do
  {
    c = fgetc(infptr);
    buffer[i] = c;
    i++;
  } while (c != '\n');

  // Check if file is P6 (ppm) format
  if (buffer[1] == '6')
    printf("\n Input file is ppm, OK\n");
  else
  {
    printf("\n Input file is NOT pgm, Exiting program...\n");
    system("PAUSE");
    exit(0);
  }

  // File is ppm, read rest of header
  fscanf(infptr, "%d %d %d", &NCols, &MRows, &MaxRGB);
  c = fgetc(infptr);
  printf("%d ", NCols);
  printf("%d   <---- Width x Height) \n", MRows);
  printf("%d   <---- Max. Grayscale level) \n\n", MaxRGB);
} // end readhdr ()

//----------------------------------------------------------------------------//
//         Add Header                                                         //
//----------------------------------------------------------------------------//

void rgb2gAddhdr()
{
  fprintf(outfptr, "P5\n%d %d\n%d\n", NCols, MRows, 255);
} // addhdr ()

//----------------------------------------------------------------------------//
//         User defined section                                               //
//----------------------------------------------------------------------------//

void rgb2gUserdefined()
{
  unsigned char R, G, B; // RGB values
  unsigned char Gray;    // Gray value

  // read first pixel
  R = fgetc(infptr);

  do
  {
    // Read G and B values
    G = fgetc(infptr);
    B = fgetc(infptr);

    // Convert RGB to Gray
    Gray = (unsigned char)(0.299 * R + 0.587 * G + 0.114 * B);

    // Write Gray value to output file
    fputc(Gray, outfptr);

    // Read next R value
    R = fgetc(infptr);
  } while (!feof(infptr));

} // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void rgb2gClosefiles()
{
  fclose(infptr);
  fclose(outfptr);
} // end closefiles ()

#endif