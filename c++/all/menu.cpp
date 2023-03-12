#include "convolution.h"
#include "GreyToBin.h"
#include "GreyToNeg.h"
#include "Histogram.h"
#include "HistogramStretching.h"
#include "MedianFiltering.h"
#include "Mirror.h"
#include "RGBtoGrey.h"

int main(){
    int option;
    printf(" 1. Mirror \n");
    printf(" 2. Grey to Negative \n");
    printf(" 3. Grey to Binary \n");
    printf(" 4. RGB to Grey \n");
    printf(" 5. Histogram \n");
    printf(" 6. Histogram Stretching \n");
    printf(" 7. Median Filtering \n");
    printf(" 8. Convolution \n");
    printf(" 9. Exit \n");

    printf(" Enter your option: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        mirror();
        break;
    case 2:
        greyToNeg();
        break;
    case 3:
        greyToBin();
        break;
    case 4:
        rgbToGrey();
        break;
    
    case 5:
        histogram();
        break;
    case 6:
        histSt();
        break;
    case 7:
        medianFiltering();
        break;
    case 8:
        convolution();
        break;
    case 9:
        exit(0);
        break;
    default:
        printf(" Invalid option! \n");
        break;
    }
    return 0;
}