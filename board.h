#ifndef BOARD_H
#define BOARD_H
#include "def.h"
#define INT_TO_CHAR "PNBRQKpnbrqk"
extern BOARD board;

void initBoard();
void initBoardNewFen(char* fen);

void printBoard();
void printBB(U64 bb);
#endif
