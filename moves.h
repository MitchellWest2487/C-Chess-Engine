#ifndef MOVES_H
#define MOVES_H
#include "attacks.h"

int isCheckWK(BOARD board, U64 move);
U64 getWhitePawnMoves(BOARD board);

typedef struct{
    U64 newBoard;
    int piece;
}MOVE;
#endif
