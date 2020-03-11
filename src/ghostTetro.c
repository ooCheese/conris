#include <stdlib.h>
#include "ghostTetro.h"

BlockList * jumpToLastBlock(BlockList * blockList);

extern BlockList * createGhostBlock(int x, int y,BlockList * ghostBlocks){
    BlockList * new = malloc(sizeof(BlockList));

    new->next = NULL;
    new->x = x;
    new->y = y;

    if(ghostBlocks == NULL){
        return new;
    }else{
        jumpToLastBlock(ghostBlocks)->next = new;;
        return ghostBlocks;
    }
}


BlockList * jumpToLastBlock(BlockList * blockList){
    if(blockList == NULL){
        return NULL;
    }

    while(blockList->next != NULL){
        blockList = blockList->next;
    }
    return blockList;
}