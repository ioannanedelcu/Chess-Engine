//
// Created by Ana on 08/03/2020.
//

#ifndef CHESS_PROJECT_HEADER_H
#define CHESS_PROJECT_HEADER_H


//pieces encoding
typedef enum {
    EM = 0,   // Empty
    WP = 1,   // White Pawn
    WN = 2,   // White Knight
    WB = 3,   // White Bishop
    WR = 4,   // White Rook
    WQ = 5,   // White Queen
    WK = 6,   // White King
    BP = -1,  // Black Pawn
    BN = -2,  // Black Knight
    BB = -3,  // Black Bishop
    BR = -4,  // Black Rook
    BQ = -5,  // Black Queen
    BK = -6,  // Black King
    IV = 99   // INVALID
}piece;

//move structure
typedef struct MOVE {

    int from;
    int to;
    int piece;
    int captured;
    int promoted;

    MOVE() {
        from = EM;
        to = EM;
        piece = EM;
        captured = EM;
        promoted = EM;
    }

    MOVE(const MOVE &a) {
        from = a.from;
        to = a.to;
        piece = a.piece;
        captured = a.captured;
        promoted = a.promoted;
    }

    MOVE(int from_, int to_, int piece_, int captured_, int promoted_) {
        from = from_;
        to = to_;
        piece = piece_;
        captured = captured_;
        promoted = promoted_;
    }

} MOVE;

//squares of the board encoding
enum // squares
{
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
};

enum // Directions
{
    N = 10, S = -10, E = -1, W = 1,
    NW = 11, SW = -9, NE = 9, SE = -11,
    NNW = 21, NNE = 19, NWW = 12, NEE = 8,
    SSW = -19, SSE = -21, SWW = -8, SEE = -12
};

#define WHITE   1
#define BLACK   -1
#define NONE    0
#define ANALYZE  3

// some value that cannot occur as a valid move
#define INVALID 666

// some parameter of your engine
#define MAXMOVES 500  /* maximum game length  */
#define MAXPLY   60   /* maximum search depth */

#define OFF 0
#define ON  1


// Some routines your engine should have to do the various essential things
int  MakeMove(int stm, MOVE move);      // performs move, and returns new side to move
//void UnMake(MOVE move);                 // unmakes the move;
int Setup();                  // sets up the position from the given FEN, and returns the new side to move
//void SetMemorySize(int n);              // if n is different from last time, resize all tables to make memory usage below n MB
//char *MoveToText(MOVE move);            // converts the move from your internal format to text like e2e2, e1g1, a7a8q.
//MOVE ParseMove(char *moveText);         // converts a long-algebraic text move to your internal move format
void searchBestMove(int stm, int timeLeft, int mps, int timeControl, int inc, int timePerMove, MOVE *move, MOVE *ponderMove);
void PonderUntilInput(int stm);         // Search current position for stm, deepening forever until there is input.


#endif //CHESS_PROJECT_HEADER_H
