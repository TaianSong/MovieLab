/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include "IterativeFilter.h"
#include "Image.h"
#include "ImageList.h"
#include "Movie.h"
#include <assert.h>

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, int start, int end, int change)
{
    assert(image);
    MOVIE *movie = CreateMovie();
    IMAGE *temp;
    if (start > end)
    {
        for(float x = start; x >=end; x -= change)
        {
            temp = filter(temp, x);
            AppendRGBImage(movie -> Frames, temp);
        }
    }
    if (start < end)
    {
        for(float x = start; x <= end; x += change)
        {
            temp = filter(temp, x);
            AppendRGBImage(movie -> Frames, temp);
        }
    }

    return movie;
}
