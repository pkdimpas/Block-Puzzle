/**
 * File        : block-philo.c
 * Usage       : block-philo (filename.txt)
 * Description : BLOCK PUZZlE
 *               Mid-year programming contest 2019
 * Date:       : May 27, 2019
 * Author      : Philogene Kyle Dimpas
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DISPLAY   1
#define VISITED   1
#define SUCCESS   1
#define FAILURE  -1


/** readability purpose */
#define MATRIX(matrix, i, j)    *(matrix + (j) + (i) * blk->width)
#define DISPLAY_ERROR(...){ printf("ERROR: "__VA_ARGS__);       \
                            return FAILURE;                     \
}

typedef unsigned char uchar;

typedef struct{
    int      height;    /* height of the block  */
    int      width;     /* width of the block   */
    int      size;      /* height * width       */
    int      min;       /* minimum block number */
    uchar   *matrix;    /* holder of the data   */
}BlockData;

typedef struct{
    int      cnt;        /* counter           */
    uchar   *ptr[900];   /* pointer to blocks */
}DelHolder;

const int vector[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };



/****************************************************************************************************
 *                                      Functions                                                   *
 ****************************************************************************************************/


/**
 * Description: process the parameters of a block and store
 *              the information in BlockData blk.
 * Parameters : FILE *fp, BlockData *blk
 * Return     : SUCCESS 
 *              FAILURE
 */
int performParseHeader(FILE *fp, BlockData *blk)
{
    fscanf(fp, "%d %d %d\n", &blk->width, &blk->height, &blk->min);
    blk->size = blk->width * blk->height;
    return (blk->width <= 0 || blk->height <= 0 || blk->min <= 0) ? FAILURE: SUCCESS;
}

/**
 * Description: Display the blk->matrix (block)
 * Parameters : BlockData *blk
 * Return     : void
 */
void displayBlock(BlockData *blk)
{
    int i;
    int j;

    for (i = 0; i < blk->height; i++){
        for (j = 0; j < blk->width; j++)
            printf("%c ", MATRIX(blk->matrix,i,j));
        printf("\n");
    }
}


/**
 * Description: This will search each block using recursive DFS algorithm.
 *              Once it meets the minimum connected block numbers, the suceeding blocks
 *              will be marked deleted ( '.' )
 * Parameters : blk    - data
 *              col    - current y index
 *              row    - current x index
 *              label  - current label (number) of the block
 *              marker - used to check if it's already a VISITED node
 *              min    - current number of connected blocks
 * Return     : current total number of connected blocks
 */
int performSearchBlock(BlockData *blk, int col, int row, int label, uchar *marker, DelHolder *minCnt, int *min)
{
    int idx;
    
    /** 
     * check neighbors
     * col == height
     * row == width 
     */

    /* check bounderies */
    if (row < 0 || col < 0 || row >= blk->width || col >= blk->height) return 0;

    if (*(marker + row + col * blk->width) == VISITED || MATRIX(blk->matrix,col, row) != label) return 0;
    
    /* mark current block visited */
    *(marker + row + col * blk->width) = VISITED;
    (*min)++;

    for (idx = 0; idx < 4; idx++)
        performSearchBlock(blk, col + vector[idx][1], row + vector[idx][0], label, marker, minCnt, min);/* use user-defined stack for DFS pls */
    
    /* minCnt->ptr will point to a block that was popped in the call stack */
    if(*min < blk->min)
        minCnt->ptr[minCnt->cnt++] = &MATRIX(blk->matrix,col, row);
    else
        MATRIX(blk->matrix,col, row) = '.';

    return 0;
}

/**
 * Description: This will perform gravity by finding a number
 *              above '.' and perform swap.
 *              +-----------------------------------+
 *              |                   .               |
 *              |                   2               |
 *              |   found number--> 1 <---+         |
 *              |                   .     | swap    |
 *              |   current top---> . <---+         |
 *              |                   2               |
 *              +-----------------------------------+
 * Parameters : blk - data 
 * Return     : SUCCESS
 */
int performGravity(BlockData *blk)
{
    int     i;
    int     j;
    int     top;    /*holder of the current top index*/

    for (j = 0; j < blk->width; j++){

        /*initialize current top*/
        for (top = blk->height - 1; top > 0 && MATRIX(blk->matrix,top, j) != '.'; top--);
    
        for (i = top; i >= 0; i--){

            if (MATRIX(blk->matrix,i, j) == '.') continue;
            /*swap '.' and number */
            MATRIX(blk->matrix,top, j) =  MATRIX(blk->matrix,i, j);
            MATRIX(blk->matrix,i, j) = '.';
            /*move the current top*/
            top--;
            
        }
    }

    return SUCCESS;
}

/**
 * Description: the main function performBlockPuzzle
 * Parameters : blk    - where parsed data will be stored
 *              data   - raw data read on file
 * Return     : total answer
 *              FAILURE
 */
int performBlockPuzzle(BlockData *blk, uchar *data)
{
    int          i;
    int          j;
    int          k;
    int          min;
    int          tmpWidth;
    int          holder;
    int          total = 0;
    uchar       *marker;
    DelHolder    minCnt;
    
    /* initialization of matrix; parse the data by skipping space then store to blk->matrix */
    tmpWidth = blk->width * 2;
    for (i = 0; i < blk->height; i++){
        for (j = k = 0; k < tmpWidth; k+=2)
            MATRIX(blk->matrix,i, j++) = *(data + k + i * tmpWidth);
    }

#if DISPLAY
    printf("Block size: %d x %d, Minimum blocks: %d\n", blk->width, blk->height, blk->min);
    printf("Original Blocks\n");    
    displayBlock(blk);
#endif  
    /* total block size is less than required minimum number of connected blocks */
    if ( blk->size < blk->min)
        return total;

    /* marker will serve as the flag for visited block parallel to blk->matrix (data) */
    marker = (uchar*)malloc(sizeof(uchar) * blk->size);

    if (marker == NULL)
        return FAILURE;


    /* minimum block is 1 */
    if (blk->min == 1){
        /* add all blocks and mark all deleted */
        for (i = 0; i < blk->height; i++){
            for (j = 0; j < blk->width; j++){
                total += MATRIX(blk->matrix,i, j) - '0';
                MATRIX(blk->matrix,i, j) = '.';
            }
        }
    /* perform searching connected block */
    }else{
        
        do{
            /* flag variable k to 1 if there is a deleted block */
            k = 0;
            memset(marker, 0, blk->size);
            
            /* start searching for connected blocks */
            for (i = 0; i < blk->height; i++){
                for (j = 0; j < blk->width; j++){
                    
                    /* check if visited or marked deleted */
                    if ( *(marker + j + i * blk->width) == VISITED || MATRIX(blk->matrix,i,j) == '.') continue; /* continue or nested if(){}? */
                    
                    minCnt.cnt = 0;
                    min = 0;
                    holder = (MATRIX(blk->matrix,i, j) - '0');
                    /* visit connected blocks */
                    performSearchBlock(blk, i , j, MATRIX(blk->matrix,i, j), marker, &minCnt, &min);
                    /**
                     * check if it meets the minimum connected block number then
                     * add the total answer and perform deletion on the remaining blocks
                     */
                    if (min < blk->min) continue;
                    
                    total += min * holder;
                    k = 1;
                    /* delete remaining blocks */
                    while (--minCnt.cnt >= 0)
                        *(minCnt.ptr[minCnt.cnt]) = '.';
                        
                }
            }
            performGravity(blk);
            
        } while (k != 0);

    }

    free(marker);

    return  total;
}

/**
 * Description: the main function 
 * Parameters : argc
 *              *argv[]
 * Return     : SUCCESS
 */
int main(int argc, char *argv[])
{
    int          total;
    FILE        *fp       = NULL;
    uchar       *rawdata  = NULL;
    BlockData    blk;
    
    if (argc < 2)
      DISPLAY_ERROR("USAGE: block-philo (filename.txt)");

    fp = fopen(argv[1], "r");

    if (fp == NULL)
        DISPLAY_ERROR("File cannot be opened!");
    
    while (performParseHeader(fp, &blk) != FAILURE){
        total = blk.size * 2;
        rawdata  = (uchar* )malloc(sizeof(uchar) * total);

        if (rawdata == NULL)
            DISPLAY_ERROR("'rawdata' failed to allocate a memory");
        
        if (fread(rawdata, sizeof(uchar), total, fp) < total){
            free(rawdata);
            DISPLAY_ERROR("Data read is less than the expected data size");
        }

        /* allocate memory for matrix */
        blk.matrix = (uchar* )malloc(sizeof(uchar) * blk.size);
        
        if (blk.matrix == NULL){
            free(rawdata);
            DISPLAY_ERROR("'blk.matrix' failed to allocate a memory\n");
        }

        /* reuse variable total */
        total = performBlockPuzzle(&blk, rawdata);
        if(total == FAILURE)
            DISPLAY_ERROR("failed to allocate a memory for 'marker'\n");

#if DISPLAY     
        printf("Final Blocks\n");
        displayBlock(&blk);
        printf("Total Points: %d\n\n", total);
#endif
        free(rawdata);
        free(blk.matrix);

    }

    return SUCCESS;
}
