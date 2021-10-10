#include "def.h"
#include "attacks.c"

BOARD board;
char *fen = STARTING_FEN;

//sets up the game board from a given FEN
void buildBoard(const char *fen){
    int i = 0, f = 0, r = 7;

    //builds the bit boards for type, color, and combined based of FEN
    while (fen[i] != ' '){
        switch (fen[i]){
            case 'p': set_bit(board.piece_bb[BP], ((r<<3) + f)); set_bit(board.position_bb[BLACK], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'b': set_bit(board.piece_bb[BB], ((r<<3) + f)); set_bit(board.position_bb[BLACK], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'n': set_bit(board.piece_bb[BN], ((r<<3) + f)); set_bit(board.position_bb[BLACK], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'r': set_bit(board.piece_bb[BR], ((r<<3) + f)); set_bit(board.position_bb[BLACK], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'q': set_bit(board.piece_bb[BQ], ((r<<3) + f)); set_bit(board.position_bb[BLACK], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'k': set_bit(board.piece_bb[BK], ((r<<3) + f)); set_bit(board.position_bb[BLACK], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'P': set_bit(board.piece_bb[WP], ((r<<3) + f)); set_bit(board.position_bb[WHITE], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'B': set_bit(board.piece_bb[WB], ((r<<3) + f)); set_bit(board.position_bb[WHITE], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'N': set_bit(board.piece_bb[WN], ((r<<3) + f)); set_bit(board.position_bb[WHITE], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'R': set_bit(board.piece_bb[WR], ((r<<3) + f)); set_bit(board.position_bb[WHITE], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'Q': set_bit(board.piece_bb[WQ], ((r<<3) + f)); set_bit(board.position_bb[WHITE], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case 'K': set_bit(board.piece_bb[WK], ((r<<3) + f)); set_bit(board.position_bb[WHITE], ((r<<3) + f)); set_bit(board.position_bb[BOTH], ((r<<3) + f++));break;
            case '/': break;
            case '1': f++; break;
            case '2': f += 2; break;
            case '3': f += 3; break;
            case '4': f += 4; break;
            case '5': f += 5; break;
            case '6': f += 6; break;
            case '7': f += 7; break;
            case '8': f += 8; break;
            default: break;
        }
        i++;
        r = (f == 8)?(r-1):r;
        f %= 8;

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
        board.enPas = (fen[i++] - 'a') + (((short)fen[i++] - 1) << 3);

    //sets the amount of half and full moves from FEN
    board.fullMove = (short)fen[++i];
    board.halfMove = (short)fen[++i];

}

//prints out game board to console
void printBoard(){
    int square;
    int piece = -1;
    printf("    A    B    C    D    E    F    G    H\n");
    for (int r = 7; r > -1; r--){
        printf("%d ", 8 - r);
        for(int f = 0; f < 8; f++){
            square = f + (r << 3);
            for(int p = 0; p < 13; p++){
                if(get_bit(board.piece_bb[p], square)){
                    piece = p;
                    break;
                }
            }
            printf("| %c |", (piece == -1) ? '-' : INT_TO_CHAR[piece]);
            piece = -1;
        }
        printf("\n");
    }
    printf("\n");
}

//prints out bit board to console
void printBB(U64 bb){
    int square;
    printf("\n");
    for (int x = 7; x > -1; x--){
        for (int y = 0; y < 8; y++){
            square = y + (x << 3);
            get_bit(bb,square) ? printf("| 1 |") : printf("| 0 |");
        }
        printf("\n");
    }
    printf("\n");
}

void main(){
    buildBoard(fen);
    initAttacks();

    printBB(getBishopAttacks(f4, 0ULL));
}
