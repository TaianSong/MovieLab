/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
    MOVIE *movie;
    movie = (MOVIE *)malloc(sizeof(MOVIE));
    if (! movie){
        perror("Out of memory!\n");
        exit(10);
    }
    movie->Frames = CreateImageList();
    return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
    assert(movie);
    assert(movie->Frames);
    DeleteImageList(movie->Frames);
    free(movie);
    movie = NULL;
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
    assert(movie);
    assert(movie->Frames);
    int x,y;
    int Y,U,V,R,G,B,C,D,E;
    IENTRY * entry;
    entry = movie->Frames->First;
    while(entry){
        entry->RGBImage = CreateImage(entry->YUVImage->W, entry->YUVImage->H);
        for (x = 0; x < entry->YUVImage->W; x++) {
            for (y = 0; y < entry->YUVImage->H; y++) {
                Y = GetPixelY(entry->YUVImage, x, y);
                U = GetPixelU(entry->YUVImage, x, y);
                V = GetPixelV(entry->YUVImage, x, y);
                C = Y - 16;
                D = U - 128;
                E = V - 128;
                R = ( 298 * C + 409 * E + 128) >> 8;
                G = ( 298 * C - 100 * D - 208 * E + 128) >> 8 ;
                B = ( 298 * C + 516 * D + 128) >> 8;
                if (R < 0)
                {R = 0;}
                if (R > 255)
                {R = 255;}
                if (G < 0)
                {G = 0;}
                if (G > 255)
                {G = 255;}
                if (B < 0)
                {B = 0;}
                if (B > 255)
                {B = 255;}
                SetPixelR(entry->RGBImage, x, y, R);
                SetPixelG(entry->RGBImage, x, y, G);
                SetPixelB(entry->RGBImage, x, y, B);
            }
        }
        DeleteYUVImage(entry->YUVImage);
        entry->YUVImage = NULL;
        entry = entry->Next;
    }
}


/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie) {
    assert(movie);
    assert(movie->Frames);
    int x, y;
    int Y, U, V, R, G, B;
    IENTRY *e;
    e = movie->Frames->First;
    while (e) {
        e->YUVImage = CreateYUVImage(e->YUVImage->W, e->YUVImage->H);
        for (x = 0; x < e->RGBImage->W; x++) {
            for (y = 0; y < e->RGBImage->H; y++) {
                R = GetPixelR(e->RGBImage, x, y);
                G = GetPixelG(e->RGBImage, x, y);
                B = GetPixelB(e->RGBImage, x, y);
                Y = ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16;
                U = ((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128;
                V = ((112 * R - 94 * G - 18 * B + 128) >> 8) + 128;
                if (Y < 0)
                { Y = 0; }
                if (Y > 255)
                { Y = 255; }
                if (U < 0)
                { U = 0; }
                if (U > 255)
                { U = 255; }
                if (V < 0)
                { V = 0; }
                if (V > 255)
                { V = 255; }
                SetPixelY(e->YUVImage, x, y, Y);
                SetPixelU(e->YUVImage, x, y, U);
                SetPixelV(e->YUVImage, x, y, V);
            }
        }
        e = e->Next;
    }
}

int MovieLength(const MOVIE *movie)
{
    assert(movie);
    assert(movie->Frames);
    return movie->Frames->Length;
}

int MovieHeight(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
    {
        return movie->Frames->First->RGBImage->H;
    }//fi

    else if(movie->Frames->First->YUVImage)
    {
        return movie->Frames->First->YUVImage->H;
    }//fi else

    else
    return 0;
}

int MovieWidth(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
        {
                return movie->Frames->First->RGBImage->W;
        }//fi

    else if(movie->Frames->First->YUVImage)
        {
                return movie->Frames->First->YUVImage->W;
        }//fi esle

    else
    return 0;
}

/* EOF */
