// MOVE structure
#pragma once
#ifndef CHESS_PROJECT_MOVE_H
#define CHESS_PROJECT_MOVE_H

typedef struct MOVE {

    int from;
    int to;
    int piece;
    int captured;
    int promoted;
    int en_pasant;
    int castling;

    MOVE() {
        from = 0;
        to = 0;
        piece = 0;
        captured = 0;
        promoted = 0;
        en_pasant = 0;
        castling = 0;
    }

    MOVE(const MOVE &a) {
        from = a.from;
        to = a.to;
        piece = a.piece;
        captured = a.captured;
        promoted = a.promoted;
        en_pasant = a.en_pasant;
        castling = a.castling;
    }

    MOVE(int from_, int to_, int piece_, int captured_, int promoted_) {
        from = from_;
        to = to_;
        piece = piece_;
        captured = captured_;
        promoted = promoted_;
        en_pasant = 0;
        castling = 0;
    }

    MOVE(int from_, int to_, int piece_, int captured_, int promoted_, int en_passant_, int castling_) {
        from = from_;
        to = to_;
        piece = piece_;
        captured = captured_;
        promoted = promoted_;
        en_pasant = en_passant_;
        castling = castling_;
    }

} MOVE;

#endif