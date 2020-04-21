#include "ai.h"

int minimax(int alpha, int beta, int depth, Board &board) {

    if (depth == 0) {
        return board.eval();
    }
    vector<MOVE> moves = board.findLegalMoves();
    //printf("moves size: %d, side: %d", moves.size(), board.getStm());

    int best_score = -BESTSCORE;

    for (int i = 0; i < moves.size(); i++) {

        // Opponent's king can be captured. That means he is check-mated.
        if (moves[i].captured == BK || moves[i].captured == WK) {
            return 9000 + depth;
        }

        Board copy(board);
        copy.makeMove(moves[i]);
        int score = - minimax(-beta, -alpha, depth - 1, copy);

        if (score > best_score) {
            best_score = score;
        }
        if (best_score > alpha) {
            alpha = best_score;
        }

        if (alpha >= beta) {
            break;
            // cut-off
        }
    }
    return best_score;
}


MOVE searchBestMove(Board &board) {

    vector<MOVE> legalMoves = board.findLegalMoves();
    srand((int)time(0));

    vector<MOVE> bestMoves;
    int best_score = -BESTSCORE;

    for (int i = 0; i < legalMoves.size(); i++) {
        Board copy(board);
        copy.makeMove(legalMoves[i]);
        copy.swapSides();
        if (copy.isMyKingInCheck())
            continue;
        copy.swapSides();
        int score = -minimax(-BESTSCORE, BESTSCORE, DEPTH, copy);

        if (score > best_score) {
            best_score = score;
            bestMoves.clear();
            bestMoves.push_back(legalMoves[i]);
        } else if (score == best_score) {
            bestMoves.push_back(legalMoves[i]);
        }
    }

    int randomIndex = rand() % bestMoves.size();
    return bestMoves[randomIndex];
}