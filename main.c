#include "attacks.h"
#include "board.h"
#include "moves.h"

void main (int argc, char *argv[]){
    if(argc > 1){
        initBoardNewFen(argv[1]);
    }
    else{
        initBoard();
    }
    initAttacks();
    printBoard();
    U64 move = 0ULL;

    set_bit(move,f2);
    set_bit(move,f3);
    
    printBB(move);
    printBB(board.position_bb[WHITE] ^ move);
    
    printBB(getQueenAttacks(e1, (board.position_bb[WHITE] ^ move)));
    
    printf("%d\n", isCheckWK(board, move));

}
