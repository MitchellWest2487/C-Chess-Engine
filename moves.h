#ifndef MOVES_H
#define MOVES_H
#include "attacks.h"

extern U64 whiteMoves[256];
int isCheckWK(BOARD board, U64 move);

typedef struct{
    U64 newBoard;
    int piece;
}MOVE;
#endif
