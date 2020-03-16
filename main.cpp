#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <csignal>
#include <ctime>
#include <vector>
#include "header.h"

using namespace std;

/*
// Some global variables that control your engine's behavior
int ponder;
int randomize;
int postThinking;
int resign;         // engine-defined option
int contemptFactor; // likewise
 */

class Board {

public:
    Board() {
        newGame();
    }

    //copy constructor
    Board (const Board& copy);

    void newGame();
    void findLegalMoves ();
    void makeMove (MOVE move);
    bool isValid (MOVE move);
    MOVE searchBestMove();
    int getStm();
    void setStm(int s);
    void changeSides();
    bool isThreatened (int position);
    bool isMyKingInCheck ();

    vector<int> &getBoardArray();

private:
    void swapSides() {
        stm = -stm;
    }

    vector<MOVE> legalMoves;
    vector<int> boardArray;
    int stm; //side to move

};

Board BOARD; //global variable of the board

void Board::newGame()
{
    piece initial[120] = {
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, WR, WN, WB, WQ, WK, WB, WN, WR, IV,
            IV, WP, WP, WP, WP, WP, WP, WP, WP, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, BP, BP, BP, BP, BP, BP, BP, BP, IV,
            IV, BR, BN, BB, BQ, BK, BB, BN, BR, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV} ;

    boardArray.reserve(120);
    for (int i=0; i<120; ++i)
    {
        boardArray[i] = initial[i];
    }

    stm = WHITE;
}

void Board::findLegalMoves() {


    legalMoves.clear();


    if (stm > 0) { //for white pieces
        for (int i = A1; i <= H8; i++) {

            int j;

            int currentPiece = boardArray[i];
            switch (currentPiece) {
                //white pawn
                case WP: {
                    //no captures
                    j = i + 10;
                    if (boardArray[j] == EM) {
                        //promoted
                        if (i > 80) {
                            {
                                MOVE m(i, j, currentPiece, EM, WQ);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, EM, WR);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, EM, WB);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, EM, WN);
                                legalMoves.push_back(m);
                            }
                        }
                            //normal move
                        else {
                            MOVE m(i, j, currentPiece, EM, EM);
                            legalMoves.push_back(m);
                        }
                    }
                    //two squares move
                    if (i < 40) {
                        j = i + 20;
                        if (boardArray[j] == EM && boardArray[j-10] == EM) {
                            MOVE m(i, j, currentPiece, EM, EM);
                            legalMoves.push_back(m);
                        }
                    }
                    //diagonal capture left
                    j = i + 9;
                    if (boardArray[j] < 0 & boardArray[j] != IV) {
                        //promoted
                        if (i > 80) {
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WQ);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WR);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WB);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WN);
                                legalMoves.push_back(m);
                            }
                        }
                            //normal move
                        else {
                            MOVE m(i, j, currentPiece, boardArray[j], EM);
                            legalMoves.push_back(m);
                        }
                    }
                    //diagonal capture right
                    j = i + 11;
                    if (boardArray[j] < 0 & boardArray[j] != IV) {
                        //promoted
                        if (i > 80) {
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WQ);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WR);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WB);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WN);
                                legalMoves.push_back(m);
                            }
                        }
                            //normal move
                        else {
                            MOVE m(i, j, currentPiece, boardArray[j], EM);
                            legalMoves.push_back(m);
                        }
                    }

                } break;
                //white bishop
                case WB: {
                    int directions[4] = {NW, NE, SW, SE};

                    for (int k = 0; k < 4; k++) {
                        int dirChoice = directions[k];
                        j = i;
                        for(;;) {
                            j += dirChoice;
                            if (boardArray[j] == IV) break;
                            if (boardArray[j] <= 0) {
                                MOVE m (i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);

                                if (boardArray[j] < 0)
                                    break;
                            } else
                                break;
                        }
                    }
                } break;
                //white knight
                case WN: {

                    int directions[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};
                    for (int k = 0; k < 8; k++) {
                        int dirChoice = directions[k];
                        j = i + dirChoice;
                        if (boardArray[j] != IV) {
                            if (boardArray[j] <= 0) {
                                MOVE m (i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);
                            }
                        }
                    }
                } break;
                //white rook
                case WR: {
                    int directions[4] = {N, S, W, E};

                    for (int k = 0; k < 4; k++) {
                        int dirChoice = directions[k];
                        j = i;
                        for(;;) {
                            j += dirChoice;
                            if (boardArray[j] == IV) break;
                            if (boardArray[j] <= 0) {
                                MOVE m (i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);

                                if (boardArray[j] < 0)
                                    break;
                            } else
                                break;
                        }
                    }
                } break;
                //white queen
                case WQ: {
                    int directions[8] = {N, S, W, E, NW, NE, SE, SW};

                    for (int k = 0; k < 8; k++) {
                        int dirChoice = directions[k];
                        j = i;
                        for(;;) {
                            j += dirChoice;
                            if (boardArray[j] == IV) break;
                            if (boardArray[j] <= 0) {
                                MOVE m (i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);

                                if (boardArray[j] < 0)
                                    break;
                            } else
                                break;
                        }
                    }
                } break;

                case WK: {
                //white king
                    int directions[8] = {N, S, W, E, NW, NE, SE, SW};
                    for (int k = 0; k < 8; k++) {
                        j = i;
                        int dirChoice = directions[k];

                        j += dirChoice;
                        if (boardArray[j] != IV) {
                            if (boardArray[j] <= 0) {
                                MOVE m(i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);
                            }
                        }
                    }
                } break;

                default:
                    continue;
            }
        }
    }
        //black pieces
    else {
        for (int i = A1; i <= H8; i++) {

            int j;
            int currentPiece = boardArray[i];

            switch (currentPiece) {
                //black pawn
                case BP: {
                    //no captures
                    j = i - 10;
                    if (boardArray[j] == EM) {
                        //promoted
                        if (i < 40) {
                            {
                                MOVE m(i, j, currentPiece, EM, WQ);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, EM, WR);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, EM, WB);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, EM, WN);
                                legalMoves.push_back(m);
                            }
                        }
                            //normal move
                        else {
                            MOVE m(i, j, currentPiece, EM, EM);
                            legalMoves.push_back(m);
                        }
                    }
                    //two squares move
                    if (i > 80) {
                        j = i - 20;
                        if (boardArray[j] == EM && boardArray[j+10] == EM) {
                            MOVE m(i, j, currentPiece, EM, EM);
                            legalMoves.push_back(m);
                        }
                    }
                    //diagonal capture left
                    j = i - 9;
                    if (boardArray[j] > 0 & boardArray[j] != IV) {
                        //promoted
                        if (i < 40) {
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WQ);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WR);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WB);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WN);
                                legalMoves.push_back(m);
                            }
                        }
                            //normal move
                        else {
                            MOVE m(i, j, currentPiece, boardArray[j], EM);
                            legalMoves.push_back(m);
                        }
                    }
                    //diagonal capture right
                    j = i - 11;
                    if (boardArray[j] > 0 & boardArray[j] != IV) {
                        //promoted
                        if (i < 40) {
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WQ);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WR);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WB);
                                legalMoves.push_back(m);
                            }
                            {
                                MOVE m(i, j, currentPiece, boardArray[j], WN);
                                legalMoves.push_back(m);
                            }
                        }
                            //normal move
                        else {
                            MOVE m(i, j, currentPiece, boardArray[j], EM);
                            legalMoves.push_back(m);
                        }
                    }

                } break;
                //black bishop
                case BB: {
                    int directions[4] = {NW, NE, SW, SE};

                    for (int k = 0; k < 4; k++) {
                        int dirChoice = directions[k];
                        j = i;
                        for(;;) {
                            j += dirChoice;
                            if (boardArray[j] == IV) break;
                            if (boardArray[j] >= 0) {
                                MOVE m (i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);

                                if (boardArray[j] > 0)
                                    break;
                            } else
                                break;
                        }
                    }
                } break;
                //black knight
                case BN: {

                    int directions[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};
                    for (int k = 0; k < 8; k++) {
                        j = i;
                        int dirChoice = directions[k];
                        j += dirChoice;
                        if (boardArray[j] != IV) {
                            if (boardArray[j] >= 0) {
                                MOVE m (i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);
                            }
                        }
                    }
                } break;
                //black rook
                case BR: {
                    int directions[4] = {N, S, W, E};

                    for (int k = 0; k < 4; k++) {
                        int dirChoice = directions[k];
                        j = i;
                        for(;;) {
                            j += dirChoice;
                            if (boardArray[j] == IV) break;
                            if (boardArray[j] >= 0) {
                                MOVE m (i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);

                                if (boardArray[j] > 0)
                                    break;
                            } else
                                break;
                        }
                    }
                } break;
                //black queen
                case BQ: {
                    int directions[8] = {N, S, W, E, NW, NE, SE, SW};

                    for (int k = 0; k < 8; k++) {
                        int dirChoice = directions[k];
                        j = i;
                        for(;;) {
                            j += dirChoice;
                            if (boardArray[j] == IV) break;
                            if (boardArray[j] >= 0) {
                                MOVE m (i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);

                                if (boardArray[j] > 0)
                                    break;
                            } else
                                break;
                        }
                    }
                } break;
                //black knight
                case BK: {

                    int directions[8] = {N, S, W, E, NW, NE, SE, SW};
                    for (int k = 0; k < 8; k++) {
                        j = i;
                        int dirChoice = directions[k];

                        j += dirChoice;
                        if (boardArray[j] != IV) {
                            if (boardArray[j] >= 0) {
                                MOVE m(i, j, currentPiece, boardArray[j], EM);
                                legalMoves.push_back(m);
                            }
                        }
                    }
                } break;

                default:
                    continue;
            }
        }
    }
   /* for (int i = 0; i < legalMoves.size(); i++)
        printf ("%d %d,", legalMoves[i].from, legalMoves[i].to );
    printf("\n");*/
}

bool Board::isThreatened (int position) {

    if (stm > 0) { //checking for white pieces
        //check for 2 possible black pawns
        if (boardArray[position + NW] == BP || boardArray[position + NE] == BP) {
            return true;
        }
        //check for the 8 possible squares in which a knight could be
        {
            int directions[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};

            for (int k = 0; k < 8; k++)
            {
                int direction = directions[k];
                if (boardArray[position + direction] == BN)
                    return true;
            }
        }
        //search diagonally for queens or bishops
        {
            int directions[4] = {NW, NE, SW, SE};

            for (int k = 0; k < 4; k++)
            {
                int direction = directions[k];
                int  diag = position;
                while (1)
                {
                    diag += direction;
                    if (boardArray[diag] == BB || boardArray[diag] == BQ)
                        return true;
                    //if it finds another piece along the way, stop searching
                    if (boardArray[diag] != EM)
                        break;
                }

            }
        }
        // search horizontally and vertically for queens or bishops
        {
            int directions[4] = {N, S, W, E};

            for (int k = 0; k < 4; k++)
            {
                int direction = directions[k];
                int liniar = position;
                while (1)
                {
                    liniar += direction;
                    if (boardArray[liniar] == BR || boardArray[liniar] == BQ)
                        return true;
                    //if it finds another piece along the way, stop searching
                    if (boardArray[liniar] != EM)
                        break;
                }

            }
        }

    } else {
        //check for 2 possible white pawns
        if (boardArray[position + SW] == WP || boardArray[position + SE] == WP) {
            return true;
        }
        //check for the 8 possible squares in which a knight could be
        {
            int directions[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};

            for (int k = 0; k < 8; k++)
            {
                int direction = directions[k];
                if (boardArray[position + direction] == WN)
                    return true;
            }
        }
        //search diagonally for queens or bishops
        {
            int directions[4] = {NW, NE, SW, SE};

            for (int k = 0; k < 4; k++)
            {
                int direction = directions[k];
                int diag = position;
                while (1)
                {
                    diag += direction;
                    if (boardArray[diag] == WB || boardArray[diag] == WQ)
                        return true;
                    //if it finds another piece along the way, stop searching
                    if (boardArray[diag] != EM)
                        break;
                }

            }
        }
        // search horizontally and vertically for queens or bishops
        {
            int directions[4] = {N, S, W, E};

            for (int k = 0; k < 4; k++)
            {
                int direction = directions[k];
                int liniar = position;
                while (1)
                {
                    liniar += direction;
                    if (boardArray[liniar] == WR || boardArray[liniar] == WQ)
                        return true;
                    //if it finds another piece along the way, stop searching
                    if (boardArray[liniar] != EM)
                        break;
                }

            }
        }
    }

    return false;
}

bool Board::isMyKingInCheck() {

    int king, kingPosition = 0;

    if (stm > 0) {
        king = WK;
    } else {
        king = BK;
    }
    for (int i = A1; i <= H8; i++) {
        if (boardArray[i] == king) {
            kingPosition = i;
            break;
        }
    }

    return isThreatened(kingPosition);
}

void Board::makeMove(MOVE move) {

    boardArray[move.to] = boardArray[move.from];
    boardArray[move.from] = EM;
    if (move.promoted != EM) {
        boardArray[move.to] = move.promoted;
    }

    swapSides(); //update the next side to move
}

//returns true or false if it finds any valid moves
bool Board::isValid(MOVE move) {

    findLegalMoves();

    for (int i = 0; i < legalMoves.size(); i++) {
        if (move.from == legalMoves[i].from && move.to == legalMoves[i].to) {

            return true;
        }
    }
    return false;
}

MOVE Board::searchBestMove() {

    findLegalMoves();
    srand((int)time(0));
    int randomIndex = rand() % legalMoves.size();
    return legalMoves[randomIndex];
}

void Board::changeSides() {

    for (int i = 0; i < 120; i++) {
        if (boardArray[i] != IV) {
            boardArray[i] = boardArray[i] * (-1);
        }
    }
    stm = -stm;
}

int Board::getStm() {
    return stm;
}

void Board::setStm(int s) {
    stm = s;
}

MOVE parseMove(char *str) {
    MOVE move;
    int col = str[0] - 'a';
    int row = str[1] - '0';
    move.from = (row + 1) * 10 + col + 1;
    col = str[2] - 'a';
    row = str[3] - '0';
    move.to = (row + 1) * 10 + col + 1;
    move.piece = BOARD.getBoardArray()[move.from];
    move.captured = BOARD.getBoardArray()[move.to];
    return move;
}

void printMove(MOVE move) {

    char str[5];
    str[0] = (move.from) % 10 + 'a' - 1;
    str[1] = (move.from) / 10 + '0' - 1;
    str[2] = (move.to) % 10 + 'a' - 1;
    str[3] = (move.to) / 10 + '0' - 1;
    printf("move %s\n", str);

}

vector<int> &Board::getBoardArray()  {
    return boardArray;
}

void PrintResult(int stm, int score)
{
    /*if(score == 0) printf("1/2-1/2\n");
    if(score > 0 && stm == WHITE || score < 0 && stm == BLACK) printf("1-0\n");
    else printf("0-1\n");
    */
    printf("Not yet available\n");
}


int main(int argc, char **argv) {

    int engineSide = NONE;                    // side played by engine
    //vector<MOVE> movesList;                 //lista de mutari
    int moveNr = 0;              // part of game state; incremented by makeMove
    MOVE moveHistory[MAXMOVES]; // holds the game history


    int timeLeft;                            // timeleft on engine's clock
    //int mps, timeControl, inc, timePerMove;  // time-control parameters, to be used by Search
    //int maxDepth;                            // used by search
    // MOVE move, ponderMove;
    int i, score;


    char inBuf[80], command[80];

    signal (SIGINT, SIG_IGN);

    while (1) {

        fflush(stdout);
        if (BOARD.getStm() == engineSide ) {
            //if the engine is in check, it resigns
            if (BOARD.isMyKingInCheck()) {
                printf("resign\n");
                break;
            }
            MOVE move  = BOARD.searchBestMove();
            //if there aren't any moves left, set from to INVALID
            if(move.from == INVALID) {         // game apparently ended
                engineSide = NONE;          // so stop playing
                //PrintResult(BOARD.getStm(), score);
                break;
            } else {
                BOARD.makeMove(move);  // assumes MakeMove returns new side to move
                moveHistory[moveNr++] = move;  // remember game

                //for this part of the project, if the engine gets itself in check,
                //it will just resign
                if (BOARD.isMyKingInCheck()) {
                    printf("resign\n");
                    break;
                }
                printMove(move);
            }
        }

        fflush (stdout);

        // now it is not our turn (anymore)
        /*if(engineSide == ANALYZE) {       // in analysis, we always ponder the position
            PonderUntilInput(stm);
        } else
        if(engineSide != NONE && ponder == ON && moveNr != 0) { // ponder while waiting for input
            if(ponderMove == INVALID) {     // if we have no move to ponder on, ponder the position
                PonderUntilInput(stm);
            } else {
                int newStm = MakeMove(stm, ponderMove);
                PonderUntilInput(newStm);
                UnMake(ponderMove);
            }
        }*/

        // wait for input, and read it until we have collected a complete line
        for(i = 0; (inBuf[i] = getchar()) != '\n'; i++);
        inBuf[i+1] = '\0';

        // extract the first word
        sscanf(inBuf, "%s", command);

        //quit
        if(!strcmp(command, "quit")) {
            break;
        } // breaks out of infinite loop
        if(!strcmp(command, "force")) {
            engineSide = NONE;
            continue;
        }
        if(!strcmp(command, "new")) {
            engineSide = BLACK;
            BOARD.newGame();
            continue;
        }

        if(!strcmp(command, "go")) {
            //set computer to play current move
            engineSide = BOARD.getStm();
            continue;
        }

        if(!strcmp(command, "xboard")) {
            continue;
        }

        if (!strcmp(command, "white")) {
            /* set white to move in current position */
            if(BOARD.getStm() == BLACK) {
                BOARD.changeSides();
            }
            engineSide = BLACK;
            continue;
        }
        if (!strcmp(command, "black")) {
            /* set black to move in current position */
            if(BOARD.getStm() == WHITE) {
                BOARD.changeSides();
            }
            engineSide = WHITE;
            continue;
        }

        if(command[1] >= '1' && command[1] <='9') {
            MOVE move = parseMove(command);
            if(!BOARD.isValid(move)) {
                printf("Illegal move\n");
            }
            else {
                BOARD.makeMove(move);
                //ponderMove = INVALID;
                moveHistory[moveNr++] = move;  // remember game
            }
            continue;
        }

        if(!strcmp(command, "resign")) {
            //to add scoring, resign = giving up
            break;
        }
        if(!strcmp(command, "Illegal")) {
            printf("resign\n");
            break;
        }

        //white, black, resign, move
        printf("Error: unknown command\n");

    }

    return 0;
}