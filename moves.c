#include "moves.h"

int isCheckWK(BOARD board, U64 move){
    int kingSquare = get_lsb(board.piece_bb[WK]);
    U64 kingCheckRays = getQueenAttacks(kingSquare, (board.position_bb[WHITE] ^ move));
        
    if(((kingCheckRays & board.piece_bb[BB]) & ~FILES[get_file(kingSquare)]) | ((kingCheckRays & board.piece_bb[BR]) & FILES[get_file(kingSquare)]))
        return 1;

    return 0;
}

U64 getWhitePawnMoves(BOARD board){
    U64 move = 0ULL;
    U64 pawnBB = board.piece_bb[WP];
    int square;

    move = (pawnBB << 8) | ((pawnBB & RANKS[RANK_2]) << 16);
    move &= ~board.position_bb[BOTH];

    for(int numPawn = 0; numPawn <= count_bits(pawnBB); numPawn++){
        square = get_lsb(pawnBB);
        pop_bit(pawnBB, square);
        move |= pawnAttacks[WHITE][square] & board.position_bb[BLACK];
    }

    return move;
}

U64 getBlackPawnMoves(BOARD board){
    U64 move = 0ULL;
    U64 pawnBB = board.piece_bb[BP];
    int square;

    move = (pawnBB << 8) | ((pawnBB & RANKS[RANK_2]) << 16);
    move &= ~board.position_bb[BOTH];

    for(int numPawn = 0; numPawn <= count_bits(pawnBB); numPawn++){
        square = get_lsb(pawnBB);
        pop_bit(pawnBB, square);
        move |= pawnAttacks[BLACK][square] & board.position_bb[WHITE];
    }

    return move;
}
