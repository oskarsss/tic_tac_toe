#ifndef AI
#define AI
#include "Board.h"

int getAImove(int* start, int compare);
int findBestMove(int depth,int value,int &move, Board* b, int compare, bool player);
void checkForPoints(Board* b, bool player);

#endif
