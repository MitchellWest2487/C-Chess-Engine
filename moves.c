#include "moves.h"
U64 whitePawnMoves[33];
U64 whiteKnightMoves[81];
U64 whiteKingMoves[9];

int isCheckWK(BOARD board, U64 move){
    int kingSquare = get_lsb(board.piece_bb[WK]);
    U64 kingCheckRays = getQueenAttacks(kingSquare, (board.position_bb[WHITE] ^ move));
        
    if(((kingCheckRays & board.piece_bb[BB]) & ~FILES[get_file(kingSquare)]) | ((kingCheckRays & board.piece_bb[BR]) & FILES[get_file(kingSquare)]))
        return 1;

    return 0;
}

void genWPMoves(BOARD board){
    U64 pawnBB = board.piece_bb[WP];
    U64 move, pawnAtk;
    int sq;
    int x = 0;

    for(int pawn = 0; pawn < count_bits(board.piece_bb[WP]); pawn++){
        sq = get_lsb(pawnBB);
        pop_bit(pawnBB, sq);
        
        pawnAtk = pawnAttacks[WHITE][sq] & board.position_bb[BLACK];
        move = (1ULL << sq) | (1ULL << (sq+8));
        
        if(!isCheckWK(board,move)){
            whitePawnMoves[x++] = move;
        }

        if(get_rank(sq) == RANK_2){
            move = (1ULL << sq) | (1ULL << (sq+16));
            if(!isCheckWK(board, move)){
                whitePawnMoves[x++] = move;
            }
        }
        
        if(pawnAtk){
            if(count_bits(pawnAtk) > 1){
                move = (1ULL << sq) | (1ULL << (get_lsb(pawnAtk)));
                pop_bit(pawnAtk, get_lsb(pawnAtk));
                if(!isCheckWK(board, move)){
                    whitePawnMoves[x++] = move;
                }
            }
            move = (1ULL << sq) | (1ULL << (get_lsb(pawnAtk)));
            if(!isCheckWK(board, move)){
                whitePawnMoves[x++] = move;
            }
        }
    }

}

void genWNMoves(BOARD board){
    U64 knightBB = board.piece_bb[WN];
    U64 move, knightAtk;
    int sq, moveSq;
    int numMove = 0;

    for(int k = 0; k < count_bits(board.piece_bb[WN]); k++){
        sq = get_lsb(knightBB);
        pop_bit(knightBB, sq);
        
        knightAtk = knightAttacks[sq];
        for(int x = 0; x < count_bits(knightAttacks[sq]); x++){
            moveSq = get_lsb(knightAtk);
            pop_bit(knightAtk, moveSq);

            move = (1ULL << sq) | (1ULL << moveSq);
            
            if(!isCheckWK(board, move)){
               whiteKnightMoves[numMove++] = move; 
            }
        }    
    }
}

void genWKMoves(BOARD board){
    U64 move, kingMoves;
    int sq, moveSq;
    int numMove = 0;
    
    sq = get_lsb(board.piece_bb[WK]);
    kingMoves = kingAttacks[sq];

    for(int k = 0; k < count_bits(board.piece_bb[WK]); k++){
        moveSq = get_lsb(kingMoves);
        pop_bit(kingMoves, moveSq);

        move = (1ULL << sq) | (1ULL << moveSq);

        if(!isCheckWK(board, move)){
            whiteKingMoves[numMove++] = move;
        }
    }
}
//U64 getWhitePawnMoves(BOARD board){
//    U64 move = 0ULL;
//    U64 pawnBB = board.piece_bb[WP];
//    int square;
//
//    move = (pawnBB << 8) | ((pawnBB & RANKS[RANK_2]) << 16);
//    move &= ~board.position_bb[BOTH];
//
//    for(int numPawn = 0; numPawn <= count_bits(pawnBB); numPawn++){
//        square = get_lsb(pawnBB);
//        pop_bit(pawnBB, square);
//        move |= pawnAttacks[WHITE][square] & board.position_bb[BLACK];
//    }
//
//    return move;
//}

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
