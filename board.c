#include "board.h"
#include "def.h"
//bitboard of all files
U64 FILES[8] = {0x101010101010101ULL, 0x202020202020202ULL, 0x404040404040404ULL, 0x808080808080808ULL, 0x1010101010101010ULL, 0x2020202020202020ULL, 0x4040404040404040ULL, 0x8080808080808080ULL};

//bitboard of all ranks
U64 RANKS[8] = {0xffULL,0xff00ULL,0xff0000ULL,0xff000000ULL,0xff00000000ULL,0xff0000000000ULL,0xff000000000000ULL,0xff00000000000000ULL};

BOARD board;

//sets up the game board from a given FEN
void buildBoard(char* fen){
    int i = 0, f = 0, r = 7;

    //builds the bit boards for type, color, and combined based of FEN
    while (fen[i] != ' '){
        switch (fen[i]){
            case 'p': 
                set_bit(board.piece_bb[BP], get_square(r,f)); 
                set_bit(board.position_bb[BLACK], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'b': 
                set_bit(board.piece_bb[BB], get_square(r,f)); 
                set_bit(board.position_bb[BLACK], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'n': 
                set_bit(board.piece_bb[BN], get_square(r,f)); 
                set_bit(board.position_bb[BLACK], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'r': 
                set_bit(board.piece_bb[BR], get_square(r,f)); 
                set_bit(board.position_bb[BLACK], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'q': 
                set_bit(board.piece_bb[BQ], get_square(r,f)); 
                set_bit(board.position_bb[BLACK], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'k': 
                set_bit(board.piece_bb[BK], get_square(r,f)); 
                set_bit(board.position_bb[BLACK], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'P': 
                set_bit(board.piece_bb[WP], get_square(r,f)); 
                set_bit(board.position_bb[WHITE], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'B': 
                set_bit(board.piece_bb[WB], get_square(r,f)); 
                set_bit(board.position_bb[WHITE], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'N': 
                set_bit(board.piece_bb[WN], get_square(r,f)); 
                set_bit(board.position_bb[WHITE], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'R': 
                set_bit(board.piece_bb[WR], get_square(r,f)); 
                set_bit(board.position_bb[WHITE], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'Q': 
                set_bit(board.piece_bb[WQ], get_square(r,f)); 
                set_bit(board.position_bb[WHITE], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
            case 'K': 
                set_bit(board.piece_bb[WK], get_square(r,f)); 
                set_bit(board.position_bb[WHITE], get_square(r,f)); 
                set_bit(board.position_bb[BOTH], get_square(r,f++));
                break;
                
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
        printf("%d ", r + 1);
        for(int f = 0; f < 8; f++){
            square = get_square(r,f);
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
    printf("\n");
    for (int r = 7; r > -1; r--){
        for (int f = 0; f < 8; f++){
            get_bit(bb,get_square(r,f)) ? printf("| 1 |") : printf("| 0 |");
        }
        printf("\n");
    }
    printf("\n");
}

void initBoard() {
    buildBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void initBoardNewFen(char* fen) {
    buildBoard(fen);
}
