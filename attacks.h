#ifndef ATTACKS_H
#define ATTACKS_H
#include "def.h"

extern U64 pawnAttacks[2][64];
extern U64 knightAttacks[64];
extern U64 kingAttacks[64];

extern U64 bishopAttacks[64][512];
extern U64 rookAttacks[64][4096];

void initAttacks();
U64 getBishopAttacks(int square, U64 occupancy);
U64 getRookAttacks(int square, U64 occupancy);
U64 getQueenAttacks(int square, U64 occupancy);

#endif
