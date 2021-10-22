#include "attacks.h"
#include "board.h"
#include "moves.h"

int main (int argc, char *argv[]){
    if(argc > 1){
        initBoardNewFen(argv[1]);
    }
    else{
        initBoard();
    }
    initAttacks();
    printBoard();
    

}
