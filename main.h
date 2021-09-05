#ifndef main_h
#define main_h

typedef unsigned long long U64;

#define BRD_NUM 120
#define MAX_HM 4096
#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define INT_TO_CHAR "PNBRQKpnbrqk"

//piece encoding
enum { WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK};

//file encoding
enum{FA, FB, FC, FD, FE, FF, FG, FH};

//rank encoding
enum{R1,R2,R3,R4,R5,R6,R7,R8};

//squares
enum{
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8, no_sq
};

//castling rights
enum{WKC = 1, WQC = 2, BKC = 4, BQC = 8};

enum{WHITE, BLACK, BOTH};

typedef struct{
    
    short enPas;
    short fiftyMove;
    short castPerm;
    unsigned int halfMove;

}MOVE;


typedef struct{
    
    U64 piece_bb[12];
    U64 combine_bb[3];

    char side;
    short enPas;
    short fiftyMove;
    short castPerm;
    unsigned int halfMove;
    unsigned int fullMove;
    
}BOARD;

// MACROS

#define max(a,b) (a > b ? a : b)
#define min(a,b) (a > b ? a : b)

#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define get_bit(bitboard, square) ((bitboard) & (1ULL << (square)))
#define pop_bit(bitboard, square) ((bitboard) &= ~(1ULL << (square)))

#endif