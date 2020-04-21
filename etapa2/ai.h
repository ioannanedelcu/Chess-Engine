#pragma once
#ifndef CHESS_PROJECT_AI_H
#define CHESS_PROJECT_AI_H

#include "board.h"

using namespace std;

int minimax(int alpha, int beta, int depth, Board &board);
MOVE searchBestMove(Board &board);

#endif