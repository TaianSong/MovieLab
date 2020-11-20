/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2016                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/13/2016                                                  */
/*                                                                   */
/* ImageList.h: header file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <stdio.h>
#include "Image.h"

typedef struct ImageEntry IENTRY;
typedef struct ImageList ILIST;

struct ImageEntry {
    ILIST *List; /* Pointer to the list which this entry belongs to */
    IENTRY *Next; /* Pointer to the next entry, or NULL */
    IENTRY *Prev; /* Pointer to the previous entry, or NULL */
    IMAGE *RGBImage; /* Pointer to the RGB image, or NULL */
    YUVIMAGE *YUVImage; /* Pointer to the YUV image, or NULL */
};

struct ImageList {
    unsigned int Length; /* Length of the list */
    IENTRY *First; /* Pointer to the first entry, or NULL */
    IENTRY *Last; /* Pointer to the last entry, or NULL */
};

/* Create a new image entry */
IENTRY *CreateImageEntry(void);

/* Delete an image entry (and all contained images) */
void DeleteImageEntry(IENTRY *entry);

/* Create a new image list */
ILIST *CreateImageList(void);

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list);

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage);

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage);

/* Reverse an image list */
void ReverseImageList(ILIST *list);

#endif
