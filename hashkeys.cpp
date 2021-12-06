// hashkeys.cpp

#include "defs.h"

U64 GeneratePosKey(const S_BOARD *pos) {
	int sq = 0;
	U64 finalKey = 0;
	int piece = EMPTY;

	// setting the pieces
	for(sq = 0; sq < BRD_SQ_NUM; ++sq) {
		piece - pos->pieces[sq];
		if(piece!=NO_SQ && piece!=EMPTY) {
			ASSERT(piece>=wP && piece<=bK);
			finalKey ^= PieceKeys[piece][sq];
		}
	}

	// if white to move, hash in the sidekey 
	if(pos->side == WHITE) {
		finalKey ^= SideKey;
	}


	// setting up the pawn glitch
	// https://www.chessprogramming.org/En_passant
	if(pos->enPassant != NO_SQ) {
		ASSERT(pos->enPassant>=0 && pos->enPassant<BRD_SQ_NUM);
		finalKey ^= PieceKeys[EMPTY][pos->enPassant];
	}

	ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15);

	finalKey ^= CastleKeys[pos->castlePerm];

	return finalKey;
}