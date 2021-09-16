#include "attacks.h"
U64 pawnAttacks[2][64];
U64 knightAttacks[64];

U64 queenAttacks[64];
U64 kingAttacks[64];

U64 bishopBlockerMask[64];
U64 rookBlockerMask[64];

U64 bishopTable[64][1024];
U64 rookTable[64][4096];


//generates all possible attack moves for pawns not including enPas
void genPawnAttacks(){
    U64 board = 1ULL;
    for(int square = 0; square < 64; square++){
        pawnAttacks[WHITE][square] = (((board << 7) & ~FILES[H_FILE]) | ((board << 9) & ~FILES[A_FILE]));
        pawnAttacks[BLACK][square] = (((board >> 7) & ~FILES[H_FILE]) | ((board >> 9) & ~FILES[A_FILE]));
        board = board << 1ULL;
    }
}

//generates all possible attack moves for knights
void genKnightAttacks(){
    U64 board = 1ULL;
    for(int square = 0; square < 64; square++){
        knightAttacks[square] = (((board << 17)  | (board >> 15)) & ~FILES[A_FILE]) |
            (((board << 15) | (board >> 17)) & ~FILES[H_FILE]) |
            (((board << 10) | (board >> 6)) & ~(FILES[A_FILE] | FILES[B_FILE])) |
            (((board << 6) | (board >> 10)) & ~(FILES[H_FILE] | FILES[G_FILE]));
        board = board << 1;
    }
}

//generates all possible attack moves for kings
void genKingAttacks(){
    U64 board = 1ULL;
    for(int square = 0; square < 64; square++){
        kingAttacks[square] = (((board << 7) | (board >> 9) | (board >> 1)) & (~FILES[H_FILE])) |
        (((board << 9) | (board >> 7) | (board << 1)) & (~FILES[A_FILE])) |
        ((board >> 8) | (board << 8));
        board = board << 1ULL;
    }
}
//#### Basic implemetaion needs to be redone####
//generates the mask for bishops to be used in generating magic bitboards
void genBishopBlockerMask(){
    int rank, file;
    int tr;
    int tf;

    for(int square = 0; square < 64; square++){
        tr = get_rank(square);
        tf = get_file(square);
        for (rank = tr + 1, file = tf + 1; rank <= 6 && file <= 6; rank++, file++){
            bishopBlockerMask[square] |= (1ULL << (rank << 3 + file));
        }

        for (rank = tr - 1, file = tf + 1; rank >= 1 && file <= 6; rank--, file++){
            bishopBlockerMask[square] |= (1ULL << (rank << 3 + file));
        }

        for (rank = tr + 1, file = tf - 1; rank <= 6 && file >= 1; rank++, file--){
            bishopBlockerMask[square] |= (1ULL << (rank << 3 + file));
        }

        for (rank = tr - 1, file = tf - 1; rank >=1 && file >= 1; rank--, file--){
            bishopBlockerMask[square] |= (1ULL << (rank << 3 + file));
        }
    }
}

//generates the mask for rooks to be used in generating magic bitboards
void genRookBlockerMask(){
    for(int square = 0; square < 64; square++){
        rookBlockerMask[square] = ~(FILES[A_FILE] | FILES[H_FILE] | RANKS[RANK_1] | RANKS[RANK_8]) &
            (LINE_NORTH(square) | LINE_SOUTH(square) | LINE_EAST(square) | LINE_WEST(square));
    }
}

void nextBishopBlocker(){

}

void nextRookBlocker(){

}

void calcBishopMagic(){

}

void calcRookMagic(){
}



//initializes all pregen attack moves
void initAttacks(){
    genPawnAttacks();
    genKnightAttacks();
    genKingAttacks();
    genBishopBlockerMask();
    genRookBlockerMask();
}
