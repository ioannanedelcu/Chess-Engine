#pragma once
#ifndef CHESS_PROJECT_BOARD_H
#define CHESS_PROJECT_BOARD_H

#include "header.h"

using namespace std;


class Board {

 public:

    Board() {
        stm = WHITE;
        newGame();
    }

    //copy constructor
    Board (const Board& copy) {
        boardArray.reserve(120);
        for (int i = 0; i < 120; ++i) {

            boardArray[i] = copy.boardArray[i];
        }
        stm = copy.stm;
        score = copy.score;
        for (int i = 0; i < copy.moveHistory.size(); i++) {
            moveHistory.push_back(copy.moveHistory[i]);
        }
        smallBlackCastling = copy.smallBlackCastling;
        bigBlackCastling = copy.bigBlackCastling;
        smallWhiteCastling = copy.smallWhiteCastling;
        bigWhiteCastling = copy.bigWhiteCastling;
    }

    // methods
    void newGame();
    vector<int> &getBoardArray();
    vector<MOVE> findLegalMoves();
    void makeMove (MOVE move);
    void undoMove (MOVE move);
    bool isValid(MOVE move);
    int getStm();
    void setStm(int s);
    void changeSides();
    bool isThreatened(int position);
    bool isMyKingInCheck();       
    int whitePosition();
    int blackPosition();
    int eval(); 

    void printBoard (ofstream &out);

    vector<MOVE>  moveHistory;
    void swapSides() {
        stm = -stm;
    }

 private:

    vector<int> boardArray;
    int stm; //side to move
    int score = 0; //material balance

    // flags for castling
    int smallBlackCastling = 0;
    int bigBlackCastling = 0;
    int smallWhiteCastling = 0;
    int bigWhiteCastling = 0;

};

#endif