/*
 * Board.h
 *
 *  Created on: Aug 25, 2010
 *      Author: Shahid najam
 */

#ifndef BOARD_H_
#define BOARD_H_
#define Black -1
#define White 1
#define Empty 0
class Board {
private:


 bool IsOutflanking(int color, int row, int col, int dr, int dc);
 bool IsOutflankable(int row, int col);
 void UpdateCounts();
public:
	Board();
	Board(Board &b);
	int blackCount;
	int whiteCount;
	 int emptyCount;
	 int blackFrontierCount;
	 int whiteFrontierCount;
	    int blackSafeCount;
	 int whiteSafeCount;
	 int squares[8][8];
	 bool safediscs[8][8];
	void setfornewgame();
	int GetSquareContents(int row, int col);
	void MakeMove(int color, int row, int col);
	bool HasAnyValidMove(int color);
	bool IsValidMove(int color, int row, int col);
	int GetValidMoveCount(int color);

	virtual ~Board();
};

#endif /* BOARD_H_ */
