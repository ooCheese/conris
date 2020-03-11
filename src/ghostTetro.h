typedef struct blockList
{
    int x;
    int y;
    struct blockList * next;

}BlockList;

BlockList * createGhostBlock(int x, int y,BlockList * ghostBlocks);