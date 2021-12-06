#include "iostream"
#include "stdio.h"
#include "defs.h"
#include "init.cpp"
#include "bitboards.cpp"

// 50 move rule, threefold repetetion, en passant
// Side to move
// ply (individual moves)

int main() {

	AllInit();

	int PieceOne = rand();
	int PieceTwo = rand();
	int PieceThree = rand();
	int PieceFour = rand();

	printf("PieceOne:%X\n", PieceOne);
	printf("PieceTwo:%X\n", PieceTwo);
	printf("PieceThree:%X\n", PieceThree);
	printf("PieceFour:%X\n", PieceFour);

	int Key = PieceOne ^ PieceTwo ^ PieceThree ^ PieceFour;
	int TempKey = PieceTwo;
	TempKey ^= PieceThree;
	TempKey ^= PieceFour;
	TempKey ^= PieceOne;

	printf("Key:%X\n", Key);
	printf("TempKey:%X\n", TempKey);

	TempKey ^= PieceThree;
	printf(" (Three out) TempKey: %X\n", TempKey);

	TempKey ^= PieceThree;
	printf(" (Three in again) TempKey: %X\n", TempKey);


	return 0;
}