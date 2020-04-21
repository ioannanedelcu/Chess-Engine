//
// Created by Ana on 08/03/2020.
//
#pragma once
#ifndef CHESS_PROJECT_HEADER_H
#define CHESS_PROJECT_HEADER_H
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <csignal>
#include <ctime>
#include <vector>
#include <fstream>
#include <iomanip>
#include "move.h"

#define WHITE   1
#define BLACK   -1
#define NONE    0
#define ANALYZE  3
#define INVALID 666

#define DEPTH 3   /* maximum search depth */
#define BESTSCORE 9999

#define SCASTLING 1 //small castling
#define BCASTLING 2 // big castling


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
} piece;



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

#endif //CHESS_PROJECT_HEADER_H
