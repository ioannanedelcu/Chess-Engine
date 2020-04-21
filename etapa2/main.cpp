#include "ai.h"
using namespace std;
Board BOARD; //global variable of the board


void printMove(MOVE move) {

    char str[5];
    str[0] = (move.from) % 10 + 'a' - 1;
    str[1] = (move.from) / 10 + '0' - 1;
    str[2] = (move.to) % 10 + 'a' - 1;
    str[3] = (move.to) / 10 + '0' - 1;
    printf("move %s\n", str);
}


MOVE parseMove(char *str) {

    if (!strcmp(str, "e1c1")) {
        if (BOARD.getBoardArray()[E1] == WK) {
            MOVE move(E1, C1, WK, 0, 0, 0, BCASTLING);
            return move;
        }
    }
    if (!strcmp(str, "e1g1")) {
        if (BOARD.getBoardArray()[E1] == WK) {
            MOVE move(E1, G1, WK, 0, 0, 0, SCASTLING);
            return move;
        }
    }
    if (!strcmp(str, "e8c8")) {
        if (BOARD.getBoardArray()[E8] == BK) {
            MOVE move(E8, C8, BK, 0, 0, 0, BCASTLING);
            return move;
        }
    }
    if (!strcmp(str, "e8g8")) {
        if (BOARD.getBoardArray()[E8] == BK) {
            MOVE move(E8, G8, BK, 0, 0, 0, SCASTLING);
            return move;
        }
    }

    MOVE move;
    int col = str[0] - 'a';
    int row = str[1] - '0';
    move.from = (row + 1) * 10 + col + 1;
    col = str[2] - 'a';
    row = str[3] - '0';
    move.to = (row + 1) * 10 + col + 1;
    move.piece = BOARD.getBoardArray()[move.from];
    move.captured = BOARD.getBoardArray()[move.to];
    if (strlen(str) > 4) {
        if (BOARD.getStm() > 0) {
            if (str[4] == 'q')
                move.promoted = WQ;
            if (str[4] == 'r')
                move.promoted = WR;
            if (str[4] == 'n')
                move.promoted = WN;
            if (str[4] == 'b')
                move.promoted = WB;
        } else {
            if (str[4] == 'q')
                move.promoted = BQ;
            if (str[4] == 'r')
                move.promoted = BR;
            if (str[4] == 'n')
                move.promoted = BN;
            if (str[4] == 'b')
                move.promoted = BB;
        }
    } else {
        //en-passant - white
        int i = move.from, j = move.to;
        if (move.piece == WP && i >= 61 && i <= 68) {
            MOVE previousMove = BOARD.moveHistory[BOARD.moveHistory.size() - 1];
            //capture left
            if (previousMove.from == i + 19 && previousMove.to == i - 1 &&
             previousMove.piece == BP && j == i + 9) {
                move.captured = BOARD.getBoardArray()[i - 1];
                move.en_pasant = i - 1;
                return move;
            }
            //capture right
            if (previousMove.from == i + 21 && previousMove.to == i + 1 &&
             previousMove.piece == BP && j == i + 11) {
                move.captured = BOARD.getBoardArray()[i + 1];
                move.en_pasant = i + 1;
                return move;
            }
        }
        //en-passant - black
        if (move.piece == BP && i >= 51 && i <= 58) {
            MOVE previousMove = BOARD.moveHistory[BOARD.moveHistory.size() - 1];
            //capture left
            if (previousMove.from == i - 19 && previousMove.to == i + 1 &&
             previousMove.piece == WP && j == i - 9) {
                move.captured = BOARD.getBoardArray()[i + 1];
                move.en_pasant = i + 1;
                return move;
            }
            //capture right
            if (previousMove.from == i - 21 && previousMove.to == i - 1 &&
             previousMove.piece == WP && j == i - 11) {
                move.captured = BOARD.getBoardArray()[i - 1];
                move.en_pasant = i - 1;
                return move;
            }
        }
    }
    return move;
}



int main(int argc, char **argv) {

	// side played by engine
    int engineSide = NONE;
    int i;
    char inBuf[80], command[80];
    signal (SIGINT, SIG_IGN);

    while (1) {

        fflush(stdout);
        if (BOARD.getStm() == engineSide ) {

            MOVE move  = searchBestMove(BOARD);
            BOARD.makeMove(move);
            printMove(move);
        }

        fflush (stdout);
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

        if(!strcmp(command, "protover")){
            printf("feature san=0");
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

        //if it receives a valid move format
        if(command[1] >= '1' && command[1] <='9') {
            MOVE move = parseMove(command);
            if(!BOARD.isValid(move)) {
                printf("Illegal move\n");
            }
            else {
                BOARD.makeMove(move);
            }
            continue;
        }

        if(!strcmp(command, "resign")) {
            //resign = giving up
            break;
        }

        printf("Error: unknown command\n");
    }

    return 0;
}