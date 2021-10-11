#ifndef DEF_H
#define DEF_H
#include<stdio.h>

typedef unsigned long long U64;

//bitboard of all files
extern U64 FILES[8];

//bitboard of all ranks
extern U64 RANKS[8];

//piece encoding
enum {WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK};

enum{A_FILE, B_FILE, C_FILE, D_FILE, E_FILE, F_FILE, G_FILE, H_FILE};
enum{RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};

//squares
enum{
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8
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

#define get_rank(square) (square/8)
#define get_file(square) (square%8)
#define get_square(rank, file) ((rank<<3) + file)

#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define get_bit(bitboard, square) ((bitboard) & (1ULL << (square)))
#define pop_bit(bitboard, square) ((bitboard) &= ~(1ULL << (square)))

#define count_bits(bitboard) __builtin_popcountll(bitboard)
#define get_lsb(bitboard) (__builtin_ffsll(bitboard) - 1)
#define get_msb(bitboard) (63 - __builtin_clzll(bitboard))

#define LINE_NORTH(square) (FILES[get_file(square)] << ((get_rank(square) + 1) << 3))
#define LINE_SOUTH(square) (FILES[get_file(square)] >> ((7 - get_rank(square)) << 3) + 1)
#define LINE_EAST(square) ((RANKS[get_rank(square)] << (get_file(square) + 1)) & RANKS[get_rank(square)])
#define LINE_WEST(square) ((RANKS[get_rank(square)] >> (8 - get_file(square))) & RANKS[get_rank(square)])

#define LINE_NE(square) (RISING_DIAGONAL << square)
#define LINE_NW(square) (RISING_DIAGONAL >> square)
#define LINE_SE(square) (FALLING_DIAGONAL << square)
#define LINE_SW(square) (FALLING_DIAGONAL >> square)
#endif
