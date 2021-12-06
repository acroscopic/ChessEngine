#ifndef DEFS_H
#define DEFS_H

#include "stdlib.h"

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

typedef unsigned long long U64;

#define NAME "Theos 1.0"
#define BRD_SQ_NUM 120
#define MAX_MOVES 2048

enum {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK}; //piece names
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};
enum {WHITE, BLACK, BOTH};
enum {FALSE, TRUE};
enum {WSCA = 1, WLCA = 2, BSCA = 4, BLCA = 8}; // WSCA = White Short Castle, BLCA = Black Long Castle

enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1, 
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3, 
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};

typedef struct {

	U64 posKey;
	int move;
	int castlePerm;
	int enPassant;
	int fiftyMove;
	
} S_UNDO ;

typedef struct {

	U64 pawns[3];
	U64 posKey; // unique hash key for the game position 
	int pieces[BRD_SQ_NUM];
	int KingSq[2];
	int side;
	int enPassant;
	int fiftyMove;
	int ply;
	int hisPly;
	int pieceNum[13];
	int bigPiece[3];
	int majorPiece[3];
	int minorPiece[3];
	int castlePerm;

	S_UNDO history[MAX_MOVES];

	// piece list
	int pList[13][10];



} S_BOARD;

/* MACROS */

#define FR2SQ(f,r) ( (21 + (f) ) + ( (r) * 10 ) ) 
#define SQ64(sq120) Sq120ToSq64[sq120]
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLRBIT(bb,sq) ((bb) &= ClearMask[(sq)])
#define SETBIT(bb,sq) ((bb) |= SetMask[(sq)])

/* GLOBALS */

extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];

/* FUNCTIONS */

// init.cpp
extern void AllInit();

// bitboards.cpp
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64* bb);
extern int CountBits(U64 b);

// hashkeys.cpp
extern U64 GeneratePosKey(const S_BOARD *pos);

// board.cpp
extern void ResetBoard(S_BOARD *pos);

#endif