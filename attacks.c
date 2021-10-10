#include "attacks.h"
U64 pawnAttacks[2][64];
U64 knightAttacks[64];
U64 kingAttacks[64];

U64 bishopMasks[64];
U64 rookMasks[64];

U64 bishopAttacks[64][512];
U64 rookAttacks[64][4096];

//generates possible pawn attacks from a square
U64 genPawnAttack(int color, int square){
    U64 board = 1ULL << square;

    if(color){
        return (((board << 7) & ~FILES[H_FILE]) | ((board << 9) & ~FILES[A_FILE]));
    }
    return (((board >> 7) & ~FILES[H_FILE]) | ((board >> 9) & ~FILES[A_FILE]));
}

//generates possible knight attacks from a square
U64 genKnightAttack(int square){
    U64 board = 1ULL << square;

    return (((board << 17)  | (board >> 15)) & ~FILES[A_FILE]) |
        (((board << 15) | (board >> 17)) & ~FILES[H_FILE]) |
        (((board << 10) | (board >> 6)) & ~(FILES[A_FILE] | FILES[B_FILE])) |
        (((board << 6) | (board >> 10)) & ~(FILES[H_FILE] | FILES[G_FILE]));
}

//generates possible king attacks from a square
U64 genKingAttacks(int square){
    U64 board = 1ULL << square;
    return (((board << 7) | (board >> 9) | (board >> 1)) & (~FILES[H_FILE])) |
        (((board << 9) | (board >> 7) | (board << 1)) & (~FILES[A_FILE])) |
        ((board >> 8) | (board << 8));
}

//generates the blocker mask for bishops at a given square to be used in generating magic bitboards
U64 genBishopMask(int square){
    U64 mask = 0ULL;
    int rank, file;
    int tr = get_rank(square);
    int tf = get_file(square);

    for (rank = tr + 1, file = tf + 1; rank <= 6 && file <= 6; rank++, file++){
        set_bit(mask, ((rank << 3) + file));
    }

    for (rank = tr - 1, file = tf + 1; rank >= 1 && file <= 6; rank--, file++){
        set_bit(mask, ((rank << 3) + file));
    }

    for (rank = tr + 1, file = tf - 1; rank <= 6 && file >= 1; rank++, file--){
        set_bit(mask, ((rank << 3) + file));
    }

    for (rank = tr - 1, file = tf - 1; rank >=1 && file >= 1; rank--, file--){
        set_bit(mask, ((rank << 3) + file));
    }

    return mask; 
}

//generates the blocker mask for rooks at a given square to be used in generating magic bitboards
U64 genRookMask(int square){
    return ((LINE_NORTH(square) & ~RANKS[RANK_8]) | 
            (LINE_SOUTH(square) & ~RANKS[RANK_1]) | 
            (LINE_EAST(square) & ~FILES[H_FILE]) | 
            (LINE_WEST(square) & ~FILES[A_FILE]));
}

// generate bishop attacks on the fly
U64 bishopAttactOTF(int square, U64 block){
    U64 attack = 0ULL;
    
    int rank, file;
    int tr = get_rank(square);
    int tf = get_file(square);

    for (rank = tr + 1, file = tf + 1; rank <= 6 && file <= 6; rank++, file++){
        attack |= (1ULL << ((rank << 3) + file));
        if ((1ULL << ((rank << 3) + file)) & block) 
            break;
    }

    for (rank = tr - 1, file = tf + 1; rank >= 1 && file <= 6; rank--, file++){
        attack |= (1ULL << ((rank << 3) + file));
        if ((1ULL << ((rank << 3) + file)) & block) 
            break;        
    }

    for (rank = tr + 1, file = tf - 1; rank <= 6 && file >= 1; rank++, file--){
        attack |= (1ULL << ((rank << 3) + file));
        if ((1ULL << ((rank << 3) + file)) & block) 
            break;       
    }

    for (rank = tr - 1, file = tf - 1; rank >=1 && file >= 1; rank--, file--){
        attack |= (1ULL << ((rank << 3) + file));
        if ((1ULL << ((rank << 3) + file)) & block) 
            break;
    }
    
    return attack;
}

// generate rook attacks on the fly
U64 rookAttactOTF(int square, U64 block){
    U64 attack = 0ULL;
    int rank, file;
    int tr = get_rank(square);
    int tf = get_file(square);

    for (rank = tr + 1; rank <= 7; rank++){
        set_bit(attack, ((rank << 3) + tf));
        if ((1ULL << ((rank << 3) + tf)) & block) 
            break;
    }

    for (rank = tr - 1; rank >= 0; rank--){
        set_bit(attack, ((rank << 3) + tf));
        if ((1ULL << ((rank << 3) + tf)) & block) 
            break;        
    }

    for (file = tf + 1; file <= 7; file++){
        set_bit(attack, ((tr << 3) + file));
        if ((1ULL << ((tr << 3) + file)) & block) 
            break;       
    }

    for (file = tf - 1; file >= 0; file--){
        set_bit(attack, ((tr << 3) + file));
        if ((1ULL << ((tr << 3) + file)) & block) 
            break;       
    }
    
    return attack;
}

//
U64 setOccupancy(int index, int num_bits, U64 mask){
    U64 occupancy = 0ULL;
    int square;
    
    for (int count = 0; count < num_bits; count++){
        square = get_lsb(mask);
        pop_bit(mask, square);
        
        if (index & (1 << count)){
            set_bit(occupancy, square);
        }
    }

    return occupancy;
}

//initializes pawn, king and knight attacks
void initNonsliderAttacks(){
    for (int square = 0; square < 64; square++){
        pawnAttacks[WHITE][square] = genPawnAttack(WHITE, square);
        pawnAttacks[BLACK][square] = genPawnAttack(BLACK, square);

        knightAttacks[square] = genKnightAttack(square);
        kingAttacks[square] = genKingAttacks(square);
    }
}

//initializes bishop, and rook attacks
void initSlidersAttacks(){
    U64 attackMask;
    U64 occupancy;
    int relBitCout;
    int occupancyIndex;
    int magicIndex;

    for (int square = 0; square < 64; square++){
        bishopMasks[square] = genBishopMask(square);
        attackMask = bishopMasks[square];
        relBitCout = count_bits(attackMask);
        occupancyIndex = (1 << relBitCout);

        for (int index = 0; index < occupancyIndex; index++){
            occupancy = setOccupancy(index, relBitCout, attackMask);
            magicIndex = (occupancy * bishopMagics[square]) >> (64 - bishopRelevantBits[square]);
            bishopAttacks[square][magicIndex] = bishopAttactOTF(square, occupancy);
        }

        rookMasks[square] = genRookMask(square);
        attackMask = rookMasks[square];
        relBitCout = count_bits(attackMask);
        occupancyIndex = (1 << relBitCout);

        for (int index = 0; index < occupancyIndex; index++){
            occupancy = setOccupancy(index, relBitCout, attackMask);
            magicIndex = (occupancy * rookMagics[square]) >> (64 - rookRelevantBits[square]);
            rookAttacks[square][magicIndex] = rookAttactOTF(square, occupancy);
        }
    }
}

//returns bishop attacks from magic board
static inline U64 getBishopAttacks(int square, U64 occupancy){
    occupancy &= bishopMasks[square];
    occupancy *= bishopMagics[square];
    occupancy >>= 64 - bishopRelevantBits[square];

    return bishopAttacks[square][occupancy];
}

//returns rook attacks from magic board
static inline U64 getRookAttacks(int square, U64 occupancy){
    occupancy &= rookMasks[square];
    occupancy *= rookMagics[square];
    occupancy >>= 64 - rookRelevantBits[square];

    return rookAttacks[square][occupancy];
}

//returns queen attacks from combining bishop and rook attacks
static inline U64 getQueenAttacks(int square, U64 occupancy){
    return getBishopAttacks(square, occupancy) | getRookAttacks(square, occupancy);
}

//initializes all
void initAttacks(){
    initNonsliderAttacks();
    initSlidersAttacks();
}
