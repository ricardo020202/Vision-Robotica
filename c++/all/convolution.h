#ifndef CONVOLUTION_H
#define CONVOLUTION_H

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

void convHeading(void);     /* Displays program heading */
void convOpenfiles(void);   /* Opens input and output files in binary */
void convUserdefined(void); /* Here, the user will implement his routine */
void convReadhdr(void);     /* Read header from input image file */
void convAddhdr(void);      /* Add header to output image file */
void convClosefiles(void);  /* Close all files used in program */

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

int convolution()
{
  // Display heading
  convHeading();
  // Open Input and Output Image Files
  convOpenfiles();
  // Read header from image file
  convReadhdr();
  // Add header to output file
  convAddhdr();
  // Execute userdefined procedure
  convUserdefined();
  // Close all image files
  convClosefiles();

  printf("\n Bye! Bye!\n");
  system("PAUSE");
  return (1);
} // end main ();

//----------------------------------------------------------------------------//
//         Headings                                                           //
//----------------------------------------------------------------------------//

void convHeading()
{
  int i;
  for (i = 0; i < 16; i++)
    printf("                                    +                       \n");
  printf("                      Convolutional vision         \n");
  printf("                         Date: March 10, 2023            \n");
  printf("                            Author: Ricardo Rosales                \n");
  for (i = 0; i < 3; i++)
    printf("                                    +                       \n");
  return;
} // end heading ()

//----------------------------------------------------------------------------//
//         Openfiles                                                          //
//----------------------------------------------------------------------------//

void convOpenfiles()
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

void convReadhdr()
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

void convAdhdr()
{
  fprintf(outfptr, "P5\n%d %d\n%d\n", NCols, MRows, 255);
} // addhdr ()

//----------------------------------------------------------------------------//
//         Image Convolution                                                  //
//         Applying several masks                                             //
//----------------------------------------------------------------------------//

void convUserdefined()
{
  unsigned char Pixel;
  unsigned char mat[512][512];
  unsigned char conv[512][512];

  // Blur mask
  int blur[3][3] = {{1, 1, 1},
                    {1, 1, 1},
                    {1, 1, 1}};

  // Sobel horizontal mask (edge detection)
  int sobelH[3][3] = {{1, 2, 1},
                      {0, 0, 0},
                      {-1, -2, -1}};

  // Sobel vertical mask (edge detection)
  int sobelV[3][3] = {{-1, 0, 1},
                      {-2, 0, 2},
                      {-1, 0, 1}};

  // Sharpening mask (second derivative)
  int sharpening[3][3] = {{0, 1, 0},
                          {1, -4, 1},
                          {0, 1, 0}};

  // Sharpening mask (second derivative)
  int sharpening2[3][3] = {{1, 1, 1},
                           {1, -8, 1},
                           {1, 1, 1}};

  // Ask user for mask
  int mask[3][3];
  int option;
  printf("Select mask: \n");
  printf("1. Blur \n");
  printf("2. Sobel Horizontal \n");
  printf("3. Sobel Vertical \n");
  printf("4. Sharpening \n");
  printf("5. Sharpening 2 \n");
  scanf("%d", &option);

  // Select mask
  switch (option)
  {
  case 1:
    printf("Blur mask selected \n");
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        mask[i][j] = blur[i][j];
    break;
  case 2:
    printf("Sobel Horizontal mask selected \n");
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        mask[i][j] = sobelH[i][j];
    break;
  case 3:
    printf("Sobel Vertical mask selected \n");
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        mask[i][j] = sobelV[i][j];
    break;
  case 4:
    printf("Sharpening mask selected \n");
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        mask[i][j] = sharpening[i][j];
    break;
  case 5:
    printf("Sharpening 2 mask selected \n");
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        mask[i][j] = sharpening2[i][j];
    break;
  default:
    printf("Invalid option, exiting program \n");
    system("PAUSE");
    exit(0);
  }

  int col, row, value;

  int dividefactor = 0;
  // Calcula dividefactor
  for (row = 0; row < 3; row++)
    for (col = 0; col < 3; col++)
    {
      dividefactor += mask[col][row];
    }

  printf("dividefactor (antes) = %d \n", dividefactor);

  if (dividefactor == 0)
    dividefactor = 1;

  printf("dividefactor (despues) = %d \n", dividefactor);

  // Read input image and store en matrix
  for (row = 0; row < MRows; row++)
    for (col = 0; col < NCols; col++)
    {
      Pixel = fgetc(infptr);
      mat[col][row] = Pixel;
    }

  // Clear convolution matrix
  for (row = 0; row < MRows; row++)
    for (col = 0; col < NCols; col++)
      conv[col][row] = 0;

  // Convolve image with mask
  for (row = 1; row < MRows - 1; row++)
    for (col = 1; col < NCols - 1; col++)
    {
      value = ((mask[0][0] * mat[col - 1][row - 1] +
                mask[1][0] * mat[col][row - 1] +
                mask[2][0] * mat[col + 1][row - 1] +
                mask[0][1] * mat[col - 1][row] +
                mask[1][1] * mat[col][row] +
                mask[2][1] * mat[col + 1][row] +
                mask[0][2] * mat[col - 1][row + 1] +
                mask[1][2] * mat[col][row + 1] +
                mask[2][2] * mat[col + 1][row + 1]) /
               dividefactor);
      conv[col][row] = value;
      if (value < 0)
        conv[col][row] = 0;
      else if (value > 255)
        conv[col][row] = 255;
      else
        conv[col][row] = value;
    }

  // printf("Fisrt convolved pixel = %d \n",conv[1][1]);

  // Save convolved image
  for (row = 0; row < MRows; row++)
    for (col = 0; col < NCols; col++)
    {
      Pixel = conv[col][row];
      fputc(Pixel, outfptr);
    }
} // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void convClosefiles()
{
  fclose(infptr);
  fclose(outfptr);
} // end closefiles ()

#endif