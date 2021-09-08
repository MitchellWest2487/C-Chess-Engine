#ifndef DEF_H
#define DEF_H

#include<stdio.h>

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define INT_TO_CHAR "PNBRQKpnbrqk"

typedef unsigned long long U64;

//bitboard of all files
const U64 H_FILE = 0x8080808080808080ULL;
const U64 G_FILE = 0x4040404040404040ULL;
const U64 F_FILE = 0x2020202020202020ULL;
const U64 E_FILE = 0x1010101010101010ULL;
const U64 D_FILE = 0x808080808080808ULL;
const U64 C_FILE = 0x404040404040404ULL;
const U64 B_FILE = 0x202020202020202ULL;
const U64 A_FILE = 0x101010101010101ULL;

//bitboard of all ranks
const U64 RANK_1 = 0xffULL;
const U64 RANK_2 = 0xff00ULL;
const U64 RANK_3 = 0xff0000ULL;
const U64 RANK_4 = 0xff000000ULL;
const U64 RANK_5 = 0xff00000000ULL;
const U64 RANK_6 = 0xff0000000000ULL;
const U64 RANK_7 = 0xff000000000000ULL;
const U64 RANK_8 = 0xff00000000000000ULL;

//piece encoding
enum { WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK};

//squares
enum{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, no_sq
};

//castling rights
enum{WKC = 1, WQC = 2, BKC = 4, BQC = 8};

//color encoding
enum{WHITE, BLACK, BOTH};

//information about the board
typedef struct{
    
    U64 piece_bb[12];
    U64 position_bb[3];

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

#define count_bits(bitboard) __builtin_popcountll(bitboard)
#define get_lsb(bitboard) (__builtin_ffsll(bitboard) - 1)
#define get_msb(bitboard) (63 - __builtin_clzll(bitboard))
#endif