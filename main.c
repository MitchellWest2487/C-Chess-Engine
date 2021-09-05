#include <stdio.h>
#include <string.h>
#include "main.h"

BOARD board;
char* fen = STARTING_FEN;
char* p2c = INT_TO_CHAR;

//sets up the game board from a given FEN
void buildBoard(const char* fen){
    int i = 0, x = 0;

    //builds the bit boards for type, color, and combined based of FEN
    while (fen[i] != ' '){
        switch (fen[i]){
            case 'p': set_bit(board.piece_bb[BP], x); set_bit(board.position_bb[BLACK], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'b': set_bit(board.piece_bb[BB], x); set_bit(board.position_bb[BLACK], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'n': set_bit(board.piece_bb[BN], x); set_bit(board.position_bb[BLACK], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'r': set_bit(board.piece_bb[BR], x); set_bit(board.position_bb[BLACK], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'q': set_bit(board.piece_bb[BQ], x); set_bit(board.position_bb[BLACK], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'k': set_bit(board.piece_bb[BK], x); set_bit(board.position_bb[BLACK], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'P': set_bit(board.piece_bb[WP], x); set_bit(board.position_bb[WHITE], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'B': set_bit(board.piece_bb[WB], x); set_bit(board.position_bb[WHITE], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'N': set_bit(board.piece_bb[WN], x); set_bit(board.position_bb[WHITE], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'R': set_bit(board.piece_bb[WR], x); set_bit(board.position_bb[WHITE], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'Q': set_bit(board.piece_bb[WQ], x); set_bit(board.position_bb[WHITE], x); set_bit(board.position_bb[BOTH], x++);break;
            case 'K': set_bit(board.piece_bb[WK], x); set_bit(board.position_bb[WHITE], x); set_bit(board.position_bb[BOTH], x++);break;
            case '/': break; 
            case '1': x++; break; 
            case '2': x += 2; break; 
            case '3': x += 3; break; 
            case '4': x += 4; break; 
            case '5': x += 5; break; 
            case '6': x += 6; break; 
            case '7': x += 7; break; 
            case '8': x += 8; break;
            default: break;
        }
        i++;    
    }

    //sets side to go from FEN
    board.side = fen[++i];
    i+= 2;
    
    //sets castle permissions from FEN
    while (fen[i] != ' '){
        switch (fen[i]){
        case 'K': set_bit(board.castPerm, WKC); break;
        case 'Q': set_bit(board.castPerm, WQC); break;
        case 'k': set_bit(board.castPerm, BKC); break;
        case 'q': set_bit(board.castPerm, BQC); break;
        default:break;
        }
        i++;
    }

    //sets en passant square from FEN
    if(fen[++i] != '-')
        board.enPas = (fen[i++] - 'a') + (8 * ((short)fen[i++] - 1));

    //sets the amount of half and full moves from FEN
    board.fullMove = (short)fen[++i];
    board.halfMove = (short)fen[++i];

}

//prints out game board to console
void printBoard(){
    int square;
    int piece = -1;
    printf("    A    B    C    D    E    F    G    H\n");
    for (int r = 0; r < 8; r++){
        printf("%d ", r + 1);
        for(int f = 0; f < 8; f++){ 
            square = f + (8 * r);
            for(int p = 0; p < 13; p++){
                if(get_bit(board.piece_bb[p], square)){
                    piece = p;
                    break;
                }
            }
            printf("| %c |", (piece == -1) ? '-' : p2c[piece]);
            piece = -1;
        }
        printf("\n");
    }
    printf("\n");
}

//prints out bit board to console
void printBB(U64 i){
    int square;
    printf("\n");
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
            square = y + (8 * x);
            if(get_bit(i,square)){
                printf("| 1 |");
            }else{
                printf("| 0 |");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void main(){
    buildBoard(fen);
    printBoard();
}
