#include "board.h"
#include "pieceSquareTables.h"

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
    for (int i=0; i<120; ++i) {

        boardArray[i] = initial[i];
    }

    stm = WHITE;
}

vector<MOVE> Board::findLegalMoves() {

    vector<MOVE> legalMoves;

    //for white pieces
    if (stm > 0) {
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

                    //en-passant
                    if (i >= 61 && i <= 68 && moveHistory.size() != 0) {
                        //capture left
                        MOVE previousMove = moveHistory[moveHistory.size() - 1];
                        //if last move was a two square move in my left
                        if (previousMove.from == i + 19 && previousMove.to == i - 1 && previousMove.piece == BP) {
                            j = i + 9;
                            MOVE m(i, j, currentPiece, boardArray[i - 1], EM, i - 1, 0);
                            legalMoves.push_back(m);
                        }

                        //capture right
                        if (previousMove.from == i + 21 && previousMove.to == i + 1 && previousMove.piece == BP) {
                            j = i +11;
                            MOVE m(i, j, currentPiece, boardArray[i + 1], EM, i + 1, 0);
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

        //check for 2 possible castlings for white
        if (bigWhiteCastling == 0 && boardArray[A1] == WR && boardArray[E1] == WK) {
            if (boardArray[B1] == EM && boardArray[C1] == EM && boardArray[D1] == EM) {
                if(!(isThreatened(E1) || isThreatened(D1) || isThreatened(C1))) {
                    MOVE m(E1, C1, WK, EM, EM, 0, BCASTLING);
                    legalMoves.push_back(m);
                }
            }
        }
        if (smallWhiteCastling == 0 && boardArray[H1] == WR && boardArray[E1] == WK) {
            if (boardArray[G1] == EM && boardArray[F1] == EM) {
                if(!(isThreatened(E1) || isThreatened(F1) || isThreatened(G1))) {
                    MOVE m(E1, G1, WK, EM, EM, 0, SCASTLING);
                    legalMoves.push_back(m);
                }
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

                    //en-passant
                    if (i >= 51 && i <= 58 && moveHistory.size() != 0) {

                        MOVE previousMove = moveHistory[moveHistory.size() - 1];
                        //capture left

                        //if last move was a two square move in my left
                        if (previousMove.from == i - 19 && previousMove.to == i + 1 && previousMove.piece == WP) {
                            j = i - 9;
                            MOVE m(i, j, currentPiece, boardArray[i + 1], EM, i + 1, 0);
                            legalMoves.push_back(m);
                        }

                        //capture right

                        //if last move was a two square move in my right
                        if (previousMove.from == i - 21 && previousMove.to == i - 1 && previousMove.piece == WP) {
                            j = i - 11;
                            MOVE m(i, j, currentPiece, boardArray[i - 1], EM, i - 1, 0);
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
        //check for 2 possible castlings for black
        if (bigBlackCastling == 0 && boardArray[A8] == BR && boardArray[E8] == BK) {
            if (boardArray[B8] == EM && boardArray[C8] == EM && boardArray[D8] == EM) {
                if(!(isThreatened(E8) || isThreatened(D8) || isThreatened(C8))) {
                    MOVE m(E8, C8, BK, EM, EM, 0, BCASTLING);
                    legalMoves.push_back(m);
                }
            }
        }
        if (smallBlackCastling == 0 && boardArray[H8] == BR && boardArray[E8] == BK) {
            if (boardArray[G8] == EM && boardArray[F8] == EM) {
                if(!(isThreatened(E8) || isThreatened(F8) || isThreatened(G8))) {
                    MOVE m(E8, G8, BK, EM, EM, 0, SCASTLING);
                    legalMoves.push_back(m);
                }
            }
        }
    }
    if (isMyKingInCheck()) {
    vector<MOVE>::iterator iter = legalMoves.begin();
        while (iter != legalMoves.end()) {
            Board copy((*this));
            copy.makeMove((*iter));
            copy.swapSides();
            if (copy.isMyKingInCheck()) {
                iter = legalMoves.erase(iter);
            } else {
                ++iter;
            }
        }
    }

    return legalMoves;
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

    switch (move.captured)
    {
        case WP : case BP : score += 1; break;
        case WN : case BN : score += 3; break;
        case WB : case BB : score += 3; break;
        case WR : case BR : score += 5; break;
        case WQ : case BQ :score += 9; break;
        default : break;
    }

    switch (move.promoted)
    {
        case WN : case BN :score += 3-1; break;
        case WB : case BB : score += 3-1; break;
        case WR : case BR : score += 5-1; break;
        case WQ : case BQ : score += 9-1; break;
        default : break;
    }

    // if certain moves are made, castling is not possible anymore
    if ((move.from == A1 || move.from == E1) && bigWhiteCastling == 0) {
        bigWhiteCastling = moveHistory.size() + 1;
    }
    if ((move.from == H1 || move.from == E1) && smallWhiteCastling == 0) {
        smallWhiteCastling = moveHistory.size() + 1;
    }
    if ((move.from == A8 || move.from == E8) && bigBlackCastling == 0) {
        bigBlackCastling = moveHistory.size() + 1;
    }
    if ((move.from == H8 || move.from == E8) && smallBlackCastling == 0) {
        smallBlackCastling = moveHistory.size() + 1;
    }

    if (move.castling) {
        //white castlings
        if (stm > 0) {
            if (move.castling == BCASTLING) {
                boardArray[A1] = EM;
                boardArray[E1] = EM;
                boardArray[C1] = WK;
                boardArray[D1] = WR;
            } else if (move.castling == SCASTLING) {
                boardArray[H1] = EM;
                boardArray[E1] = EM;
                boardArray[G1] = WK;
                boardArray[F1] = WR;
            }
            //black castlings
        } else {
            if (move.castling == BCASTLING) {
                boardArray[A8] = EM;
                boardArray[E8] = EM;
                boardArray[C8] = BK;
                boardArray[D8] = BR;
            } else if (move.castling == SCASTLING) {
                boardArray[H8] = EM;
                boardArray[E8] = EM;
                boardArray[G8] = BK;
                boardArray[F8] = BR;
            }
        }
    } else {
        //printf("move.from: %d, move.to: %d\n", move.from, move.to);
        boardArray[move.to] = boardArray[move.from];

        boardArray[move.from] = EM;
        //case en-passant
        if (move.en_pasant != 0) {
            boardArray[move.en_pasant] = EM;
        }
        if (move.promoted != EM) {
            boardArray[move.to] = move.promoted;
        }
    }

    swapSides(); //update the next side to move
    score = (-1) * score;
    moveHistory.push_back(move);
}

void Board::undoMove(MOVE move) {

    score = (-1) * score;

    switch (move.captured)
    {
        case WP : case BP : score -= 1; break;
        case WN : case BN : score -= 3; break;
        case WB : case BB : score -= 3; break;
        case WR : case BR : score -= 5; break;
        case WQ : case BQ :score -= 9; break;
        default : break;
    }

    switch (move.promoted)
    {
        case WN : case BN :score -= 3-1; break;
        case WB : case BB : score -= 3-1; break;
        case WR : case BR : score -= 5-1; break;
        case WQ : case BQ : score -= 9-1; break;
        default : break;
    }

    //remove castling flags if necessary, meaning if the current move
    //generated the flags, they need to be erased
    if (bigBlackCastling == moveHistory.size()) {
        bigBlackCastling = 0;
    }
    if (smallBlackCastling == moveHistory.size()) {
        smallBlackCastling = 0;
    }
    if (smallWhiteCastling == moveHistory.size()) {
        smallWhiteCastling = 0;
    }
    if (bigWhiteCastling == moveHistory.size()) {
        bigWhiteCastling = 0;
    }

    if (move.castling) {
        //white castlings
        if (stm > 0) {
            if (move.castling == BCASTLING) {
                boardArray[A1] = WR;
                boardArray[E1] = WK;
                boardArray[C1] = EM;
                boardArray[D1] = EM;
            } else if (move.castling == SCASTLING) {
                boardArray[H1] = WR;
                boardArray[E1] = WK;
                boardArray[G1] = EM;
                boardArray[F1] = EM;
            }
            //black castlings
        } else {
            if (move.castling == BCASTLING) {
                boardArray[A8] = BR;
                boardArray[E8] = BK;
                boardArray[C8] = EM;
                boardArray[D8] = EM;
            } else if (move.castling == SCASTLING) {
                boardArray[H8] = BR;
                boardArray[E8] = BK;
                boardArray[G8] = EM;
                boardArray[F8] = EM;
            }
        }
    } else {

        boardArray[move.from] = move.piece;
        boardArray[move.to] = move.captured;

        //case en-passant
        if (move.en_pasant != 0) {
            boardArray[move.to] = EM;
            boardArray[move.en_pasant] = move.captured;
        }
    }

    swapSides(); //update the next side to move
    moveHistory.pop_back();
}


//returns true or false if it finds any valid moves
bool Board::isValid(MOVE move) {

    vector<MOVE> legalMoves = findLegalMoves();

    for (int i = 0; i < legalMoves.size(); i++) {
        if (move.from == legalMoves[i].from && move.to == legalMoves[i].to) {
            return true;
        }
    }
    return false;
}

int Board:: whitePosition () {

    int white = 0;
    for (int i = 0; i <  64; i++) {
        switch (boardArray[i + (2 * (i / 8)) + 21]) {
            case WP :
                white += pawntable[i];
                break;
            case WN :
                white += knighttable[i];
                break;
            case WB :
                white += bishoptable[i];
                break;
            case WR :
                white += rooktable[i];
                break;
            case WQ :
                white += queentable[i];
                break;
            case WK :
                white += kingtable[i];
                break;
            default:
                break;
        }
    }
    return white;
}

int Board:: blackPosition () {

    int black = 0;
    for (int i = 0; i <  64; i++) {
        switch (boardArray[i + (2 * (i / 8)) + 21]) {
            case BP :
                black += pawntable[56 + (2* (i%8)) - i];
                break;
            case BN :
                black += knighttable[56 + (2* (i%8)) - i];
                break;
            case BB :
                black += bishoptable[56 + (2* (i%8)) - i];
                break;
            case BR :
                black += rooktable[56 + (2* (i%8)) - i];
                break;
            case BQ :
                black += queentable[56 + (2* (i%8)) - i];
                break;
            case BK :
                black += kingtable[56 + (2* (i%8)) - i];
                break;
            default:
                break;
        }
    }
    return black;
}

int Board::eval()
{
    if (isMyKingInCheck())
        return -BESTSCORE;

    int eval = 0;

    // number of possible moves
    vector<MOVE> legalMoves = findLegalMoves();
    int my_moves = legalMoves.size();
    swapSides();

    legalMoves.clear();
    legalMoves = findLegalMoves();
    int opponent_moves = legalMoves.size();
    swapSides();

    eval = my_moves - opponent_moves;

    // position
    if (stm > 0) {
        eval += whitePosition() - blackPosition();
    }
    else {
        eval += blackPosition() - whitePosition();
    }

    // material
    return eval + 100 * score;
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

vector<int> &Board::getBoardArray()  {
    return boardArray;
}