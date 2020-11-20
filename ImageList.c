/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ImageList.h"


/* Create a new image list */
ILIST *CreateImageList(void)
{
    ILIST *List = (ILIST *)malloc(sizeof(ILIST));
    if(List == NULL){
        perror("Out of memory!\n");
        exit(10);
    }
    List->Length = 0;
    List->First = NULL;
    List->Last = NULL;
    return List;
}


/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *List)
{
    IENTRY *entry, *n;
    entry = List->First;
    while(entry){
        n = entry->Next;
        /* DeleteImageEntry(entry); */
        entry = n;
    }

    free(List);
    List = NULL;
}


/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
    IENTRY *entry;
    entry = (IENTRY *)malloc(sizeof(IENTRY));
    entry->List = NULL;
    entry->Next = NULL;
    entry->Prev = NULL;
    entry->RGBImage = NULL;
    entry->YUVImage = NULL;
    return entry;
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
    assert(entry);
    if(entry->RGBImage){
        DeleteImage(entry->RGBImage);
    }
    if (entry->YUVImage){
        DeleteYUVImage(entry->YUVImage);
    }
    free(entry);
    entry = NULL;
}


/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *List, IMAGE *RGBimage)
{
    IENTRY *entry = NULL;
    assert(List);
    assert(RGBimage);
    entry = CreateImageEntry();
    entry->RGBImage = RGBimage;
    /*If there are no existing entries*/
    if (List->Last)
    {	entry->List = List;
        entry->Next = NULL;
        entry->Prev = List->Last;
        List->Last->Next = entry;
        List->Last= entry;
    }
        /*If there are no  existing entries*/
    else
    {	entry->List = List;
        entry->Next = NULL;
        entry->Prev = NULL;
        List->First = entry;
        List->Last= entry;
    }

    List->Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *List, YUVIMAGE *YUVimage)
{
    IENTRY *entry = NULL;
    assert(List);
    assert(YUVimage);
    entry = CreateImageEntry();
    entry->YUVImage = YUVimage;
    if (List->Last)
    {       entry->List = List;
        entry->Next = NULL;
        entry->Prev = List->Last;
        List->Last->Next = entry;
        List->Last= entry;
    }
    else
    {       entry->List = List;
        entry->Next = NULL;
        entry->Prev = NULL;
        List->First = entry;
        List->Last= entry;
    }
    List->Length++;
}

/* Reverse an image list */
void ReverseImageList(ILIST *List) /*change later, did not show on the slide of Imgaelist*/
{
    IENTRY *tmp, *tmp_next;
    tmp = List->First;
    tmp_next = tmp->Next;
    tmp->Next = NULL;
    /* tmp will be the last entry, so no more entry behind, tmp->Next become NULL*/

    while (tmp != NULL && tmp_next != NULL) {
        tmp->Prev = tmp_next;
        tmp_next = tmp_next->Next;
        tmp->Prev->Next = tmp;
        tmp = tmp->Prev;
    }

    tmp->Prev = NULL;
    /* Because tmp will be the first one, so no previous entry available*/
    tmp = List->First;
    List->First = List->Last;
    List->Last = tmp;
    tmp = NULL;
}

/* EOF */
