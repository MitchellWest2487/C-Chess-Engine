#include "attacks.h"
U64 pawnAttacks[2][64];
U64 knightAttacks[64];

U64 queenAttacks[64];
U64 kingAttacks[64];

U64 bishopMask[64];
U64 rookMask[64];

U64 bishopTable[64][4096];
U64 rookTable[64][1024];


//generates all possible attack moves for pawns not including enPas
void genPawnAttacks(){
    U64 board = 1ULL;

    for(int square = 0; square < 64; square++){
        pawnAttacks[WHITE][square] = (((board >> 7) & ~A_FILE) | ((board >> 9) & ~H_FILE));
        pawnAttacks[BLACK][square] = (((board << 7) & ~A_FILE) | ((board << 9) & ~H_FILE));
        board = board << 1ULL;       
    }
}

//generates all possible attack moves for knights
void genKnightAttacks(){
    U64 board;
    for(int square = 0; square < 64; square++){
        board = KNIGHT_MOVES << (max(square - f3, f3 - square));
        knightAttacks[square] = board & ~(((square % 8) < 3) ? H_FILE|G_FILE : A_FILE|B_FILE);
    }
}

//generates all possible attack moves for kings
void genKingAttack(){
    U64 board = 1ULL;
    for(int square = 0; square < 64; square++){
        kingAttacks[square] = (((board << 7) | (board >> 9) | (board >> 1)) & (~H_FILE)) |
        (((board << 9) | (board >> 7) | (board << 1)) & (~A_FILE)) |
        ((board >> 8) | (board << 8));
    }
}

//generates the mask for bishops to be used in generating magic bitboards
U64 genBishopMask(int square){
    U64 mask = 0ULL;
    int r, f;
    int tr = square/8;
    int tf = square%8;

    for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++){
        mask |= (1ULL << (r * 8 + f));
    }

    for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++){
        mask |= (1ULL << (r * 8 + f));
    }

    for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--){
        mask |= (1ULL << (r * 8 + f));
    }
    
    for (r = tr - 1, f = tf - 1; r >=1 && f >= 1; r--, f--){
        mask |= (1ULL << (r * 8 + f));
    }

    return mask;
}

//generates the mask for rooks to be used in generating magic bitboards
U64 genRookMask(int square){
    U64 mask = 0ULL;
    int r, f;
    int tr = square/8;
    int tf = square%8;

    for (r = tr + 1; r <= 6 ; r++){
        mask |= (1ULL << (r * 8 + tf));
    }

    for (f = tf + 1; f <= 6; f++){
        mask |= (1ULL << (tr * 8 + f));
    }

    for (r = tr - 1; r >= 1; r--){
        mask |= (1ULL << (r * 8 + tf));
    }
    
    for (f = tf - 1;f >= 1; f--){
        mask |= (1ULL << (tr * 8 + f));
    }

    return mask;
}

U64 calcBishopMagic(int square, int blocker){
    return 0;
}

U64 calcQueenAttack(int square, int blocker){
    return 0;
}

//initializes all pregen attack moves
void initAttacks(){
    precalcPawnAttacks();
    precalcKnightAttacks();
    precalcKnightAttacks();
}

