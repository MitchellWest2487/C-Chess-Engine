#include "attacks.h"

//magic number bs
const U64 rookMagics[64] = {
    0x0080001020400080ull, 0x0040001000200040ull, 0x0080081000200080ull,
    0x0080040800100080ull, 0x0080020400080080ull, 0x0080010200040080ull,
    0x0080008001000200ull, 0x0080002040800100ull, 0x0000800020400080ull,
    0x0000400020005000ull, 0x0000801000200080ull, 0x0000800800100080ull,
    0x0000800400080080ull, 0x0000800200040080ull, 0x0000800100020080ull,
    0x0000800040800100ull, 0x0000208000400080ull, 0x0000404000201000ull,
    0x0000808010002000ull, 0x0000808008001000ull, 0x0000808004000800ull,
    0x0000808002000400ull, 0x0000010100020004ull, 0x0000020000408104ull,
    0x0000208080004000ull, 0x0000200040005000ull, 0x0000100080200080ull,
    0x0000080080100080ull, 0x0000040080080080ull, 0x0000020080040080ull,
    0x0000010080800200ull, 0x0000800080004100ull, 0x0000204000800080ull,
    0x0000200040401000ull, 0x0000100080802000ull, 0x0000080080801000ull,
    0x0000040080800800ull, 0x0000020080800400ull, 0x0000020001010004ull,
    0x0000800040800100ull, 0x0000204000808000ull, 0x0000200040008080ull,
    0x0000100020008080ull, 0x0000080010008080ull, 0x0000040008008080ull,
    0x0000020004008080ull, 0x0000010002008080ull, 0x0000004081020004ull,
    0x0000204000800080ull, 0x0000200040008080ull, 0x0000100020008080ull,
    0x0000080010008080ull, 0x0000040008008080ull, 0x0000020004008080ull,
    0x0000800100020080ull, 0x0000800041000080ull, 0x00FFFCDDFCED714Aull,
    0x007FFCDDFCED714Aull, 0x003FFFCDFFD88096ull, 0x0000040810002101ull,
    0x0001000204080011ull, 0x0001000204000801ull, 0x0001000082000401ull,
    0x0001FFFAABFAD1A2ull
};
const U64 bishopMagics[64] = {
    0x0002020202020200ull, 0x0002020202020000ull, 0x0004010202000000ull,
    0x0004040080000000ull, 0x0001104000000000ull, 0x0000821040000000ull,
    0x0000410410400000ull, 0x0000104104104000ull, 0x0000040404040400ull,
    0x0000020202020200ull, 0x0000040102020000ull, 0x0000040400800000ull,
    0x0000011040000000ull, 0x0000008210400000ull, 0x0000004104104000ull,
    0x0000002082082000ull, 0x0004000808080800ull, 0x0002000404040400ull,
    0x0001000202020200ull, 0x0000800802004000ull, 0x0000800400A00000ull,
    0x0000200100884000ull, 0x0000400082082000ull, 0x0000200041041000ull,
    0x0002080010101000ull, 0x0001040008080800ull, 0x0000208004010400ull,
    0x0000404004010200ull, 0x0000840000802000ull, 0x0000404002011000ull,
    0x0000808001041000ull, 0x0000404000820800ull, 0x0001041000202000ull,
    0x0000820800101000ull, 0x0000104400080800ull, 0x0000020080080080ull,
    0x0000404040040100ull, 0x0000808100020100ull, 0x0001010100020800ull,
    0x0000808080010400ull, 0x0000820820004000ull, 0x0000410410002000ull,
    0x0000082088001000ull, 0x0000002011000800ull, 0x0000080100400400ull,
    0x0001010101000200ull, 0x0002020202000400ull, 0x0001010101000200ull,
    0x0000410410400000ull, 0x0000208208200000ull, 0x0000002084100000ull,
    0x0000000020880000ull, 0x0000001002020000ull, 0x0000040408020000ull,
    0x0004040404040000ull, 0x0002020202020000ull, 0x0000104104104000ull,
    0x0000002082082000ull, 0x0000000020841000ull, 0x0000000000208800ull,
    0x0000000010020200ull, 0x0000000404080200ull, 0x0000040404040400ull,
    0x0002020202020200ull
};

const int rookRelevantBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

const int bishopRelevantBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

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
    return ~color ? (((board << 7) & ~FILES[H_FILE]) | ((board << 9) & ~FILES[A_FILE])) : 
        (((board >> 7) & ~FILES[H_FILE]) | ((board >> 9) & ~FILES[A_FILE]));
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
        set_bit(mask, get_square(rank,file));
    }

    for (rank = tr - 1, file = tf + 1; rank >= 1 && file <= 6; rank--, file++){
        set_bit(mask, get_square(rank,file));
    }

    for (rank = tr + 1, file = tf - 1; rank <= 6 && file >= 1; rank++, file--){
        set_bit(mask, get_square(rank,file));
    }

    for (rank = tr - 1, file = tf - 1; rank >=1 && file >= 1; rank--, file--){
        set_bit(mask, get_square(rank,file));
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

//generate bishop attacks on the fly
U64 bishopAttactOTF(int square, U64 block){
    U64 attack = 0ULL;
    
    int rank, file;
    int tr = get_rank(square);
    int tf = get_file(square);

    for (rank = tr + 1, file = tf + 1; rank <= 7 && file <= 7; rank++, file++){
        set_bit(attack, get_square(rank,file));
        if ((1ULL << get_square(rank,file)) & block) 
            break;
    }

    for (rank = tr - 1, file = tf + 1; rank >= 0 && file <= 7; rank--, file++){
        set_bit(attack, get_square(rank,file));
        if ((1ULL << get_square(rank,file)) & block) 
            break;        
    }

    for (rank = tr + 1, file = tf - 1; rank <= 7 && file >= 0; rank++, file--){
        set_bit(attack, get_square(rank,file));
        if ((1ULL << get_square(rank,file)) & block) 
            break;       
    }

    for (rank = tr - 1, file = tf - 1; rank >= 0 && file >= 0; rank--, file--){
        set_bit(attack, get_square(rank,file));
        if ((1ULL << get_square(rank,file)) & block) 
            break;
    }
    
    return attack;
}

//generate rook attacks on the fly
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

//generates occupancy
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

//initializes bishop and rook attacks
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
U64 getBishopAttacks(int square, U64 occupancy){
    occupancy &= bishopMasks[square];
    occupancy *= bishopMagics[square];
    occupancy >>= 64 - bishopRelevantBits[square];

    return bishopAttacks[square][occupancy];
}

//returns rook attacks from magic board
U64 getRookAttacks(int square, U64 occupancy){
    occupancy &= rookMasks[square];
    occupancy *= rookMagics[square];
    occupancy >>= 64 - rookRelevantBits[square];

    return rookAttacks[square][occupancy];
}

//returns queen attacks from combining bishop and rook attacks
U64 getQueenAttacks(int square, U64 occupancy){
    return getBishopAttacks(square, occupancy) | getRookAttacks(square, occupancy);
}

//initializes all
void initAttacks(){
    initNonsliderAttacks();
    initSlidersAttacks();
}
