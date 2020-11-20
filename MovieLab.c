
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{
    /* allocate necessary variables */
    IMAGE *my_image = NULL;
    MOVIE *my_movie = NULL;
    int importFlag = 0;
    int width, height;

    /* movie input name */
    char *file_in_Name = NULL;

    /* movie output name*/
    char *file_out_Name = NULL;

    /* movie input frame number */
    int movie_Frame;

    /* Reverse parameter*/
    int Reverse = 0;

    /*  Name of filter */
    iterableFilter filter = NULL;

    /* Hue Parameter*/
    int Hue = 0;

    /* step number parameter*/
    float start, end, step;

    /* bw parameter*/
    int bw = 0;


    /* loop through each argument for the main function */
    for(int n = 0; n < argc; n++)
    {
        /* If the user wants to import an image */
        if(!strcmp(argv[n], "-i"))
        {
            /* If they are at the last argument */
            if(n == argc - 1)
            {
                printf("\n\tPlease provide the name of the image you want to import\n");
                return 0;
            }

            file_in_Name = argv[++n];

            /* Let the program know an image has succesfully been imported */
            importFlag = 1;
        }

        /* If the user wants to import a movie */
        else if(!strcmp(argv[n], "-m"))
        {
            file_in_Name = argv[++n];
            if (n == argc - 1)
            {
                printf("\n\tPlease provide the name of the movie you want to import\n");
                return 0;
            }
            /* Let the program know a movie has successfully been imported */
            importFlag = 2;
        }
        /* other arguments to be implemented */

        /* export movie */
        else if(!strcmp(argv[n], "-o"))
        {
            if (n == argc - 1)
            {
                printf("\n\tPlease provide the name of the output file\n");
                return 0;
            }
            file_out_Name = argv[++n];
        }

        /* number of frames in the input movie */
        else if(!strcmp(argv[n], "-f"))
        {
            if (n == argc - 1)
            {
                printf("\n\tMissing argument for the number of frames!\n");
                return 0;
            }
            sscanf(argv[++n], "%d", &movie_Frame);
        }

        /* set start parameter */
        else if(!strcmp(argv[n], "-start"))
        {
            if (n == argc - 1)
            {
                printf("\n\tPlease provide the start parameter\n");
                return 0;
            }
            sscanf(argv[++n], "%d", &start);
        }

        /* set end parameter */
        else if(!strcmp(argv[n], "-end"))
        {
            if (n == argc - 1)
            {
                printf("\n\tPlease provide the end parameter\n");
                return 0;
            }
            sscanf(argv[++n], "%d", &end);
        }

        /* set step parameter */
        else if(!strcmp(argv[n], "-step"))
        {
            if (n == argc - 1)
            {
                printf("\n\tPlease provide the step parameter\n");
                return 0;
            }
            sscanf(argv[++n], "%d", &step);
        }

        /*  use hue filter */
        else if(!strcmp(argv[n], "-hue"))
        {
            filter = &HueRotate;
            Hue = 1;
        }

        /* use black and white filter */
        else if(!strcmp(argv[n], "-bw"))
        {
            filter = &BlackNWhite;
            bw = 1;
        }

        /* size of a movie frame */
        else if(!strcmp(argv[n], "-s"))
        {
            if (n == argc - 1)
            {
                printf("\n\tMissing argument for the resolution of the frame!\n");
                return 0;
            }
            sscanf(argv[++n], "%dx%d", &width, &height);
        }

        /*  use reverse filter */
        else if(!strcmp(argv[n], "-reverse"))
        {
            Reverse = 1;
        }
    }




    /* Load the default image if no argument was specified */
    if(!importFlag)
    {
        printf("\nNo -i nor -m for input file to read\n");
        return 0;
    }

    if(importFlag == 1){
        my_image = LoadImage(file_in_Name);
    }
    if(importFlag == 2){
        my_movie = LoadMovie(file_in_Name, movie_Frame, width, height);
    }
    if(Reverse == 1){
        ReverseImageList(my_movie->Frames);
    }
    if(Hue == 1){
        my_movie = doIterativeFilter(my_image,filter,start,end,step);
    }
    if(bw == 1){
        my_movie = doIterativeFilter(my_image,filter,start,end,step);
    }
    if(my_movie != NULL){
        SaveMovie(file_out_Name,my_movie);
        DeleteMovie(my_movie);
    }

    if(importFlag == 1){
        DeleteImage(my_image);
    }
    return 0;
}

/* EOF */
