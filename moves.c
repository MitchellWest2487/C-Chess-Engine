include "def.h"

int isLegalMove(int square, int piece, int color, BOARD board){
  switch (piece) {
    case WP:
    case BP:
      return checkPawnMove(color); break;
    case WN:
    case BN:
      return checkKnightMove(color); break;
    case WK:
    case BK:
      return checkKingMove(); break;
    case WB:
    case BB:
      return checkBishopMove(); break;
    case WR:
    case BR:
      return checkRookMove(); break;
    case WQ:
    case BQ:
      return checkBishopMove() | checkRookMove(); break;

    default: return -1; break;
  }
}

int checkPawnMove(int color, int square){
  return 0;
}

int checkKnightMove(int color){
  return 0;
}

int checkKingMove(){
  return 0;
}

int checkBishopMove(){
  return 0;
}

int checkRookMove(){
  return 0;
}

int checkQueenMove(){
  return 0;
}
