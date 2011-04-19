/*
 * Board.cpp
 *
 *  Created on: Aug 25, 2010
 *      Author: Shahid najam
 */

#include "Board.h"

Board::Board() {



	            int i, j;
	            for (i = 0; i < 8; i++)
	                for (j = 0; j < 8; j++)
	                {
	                    this->squares[i][j] = 0;
	                    this->safediscs[i][j] = false;
	                }

	            // Update the counts.
	            this->UpdateCounts();

}
Board::Board(Board &board)
{



	            // Copy the given board.
	            int i, j;
	            for (i = 0; i < 8; i++)
	                for (j = 0; j < 8; j++)
	                {
	                    this->squares[i][j] = board.squares[i][j];
	                    this->safediscs[i][j] = board.safediscs[i][j];
	                }

	            // Copy the counts.
	            this->blackCount = board.blackCount;
	            this->whiteCount = board.whiteCount;
	            this->emptyCount = board.emptyCount;
	            this->blackSafeCount = board.blackSafeCount;
	            this->whiteSafeCount = board.whiteSafeCount;
}
void Board::setfornewgame()
{

	 int i, j;
	            for (i = 0; i < 8; i++)
	                for (j = 0; j < 8; j++)
	                {
	                    this->squares[i][j] = 0;
	                    this->safediscs[i][j] = false;
	                }

	            // Set two black and two white discs in the center.
	            this->squares[3][3] = 1;
	            this->squares[3][4] = -1;
	            this->squares[4][3] = -1;
	            this->squares[4][4] =1;

	            // Update the counts.
	            this->UpdateCounts();
}
int Board::GetSquareContents(int row, int col)
        {
            return this->squares[row][col];
        }

 bool Board::HasAnyValidMove(int color)
        {
            // Check all board positions for a valid move.
            int r, c;
            for (r = 0; r < 8; r++)
                for (c = 0; c < 8; c++)
                    if (this->IsValidMove(color, r, c))
                        return true;


            return false;
        }


      bool Board::IsValidMove(int color, int row, int col)
        {

            if (this->squares[row][col]!=Empty)
                return false;


            int dr, dc;
            for (dr = -1; dr <= 1; dr++)
                for (dc = -1; dc <= 1; dc++)
                    if (!(dr == 0 && dc == 0) && this->IsOutflanking(color, row, col, dr, dc))
                        return true;


            return false;
        }

 int Board::GetValidMoveCount(int color)
        {
            int n = 0;


            int i, j;
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)

                    if (this->IsValidMove(color, i, j))
                        n++;
            return n;
        }


       bool Board::IsOutflanking(int color, int row, int col, int dr, int dc)
        {
                  int r = row + dr;
            int c = col + dc;
            while (r >= 0 && r < 8 && c >= 0 && c < 8 && this->squares[r][c] == -color)
            {
                r += dr;
                c += dc;
            }


            if (r < 0 || r > 7 || c < 0 || c > 7 || (r - dr == row && c - dc == col) || this->squares[r][c] != color)
                return false;

            // Otherwise, return true;
            return true;
        }

void Board::MakeMove(int color, int row, int col)
        {
            // Set the disc on the square.
            this->squares[row][col] = color;

            // Flip any flanked opponents.
            int dr, dc;
            int r, c;
            for (dr = -1; dr <= 1; dr++)
                for (dc = -1; dc <= 1; dc++)
                    // Are there any outflanked opponents?
                    if (!(dr == 0 && dc == 0) && IsOutflanking(color, row, col, dr, dc))
                    {
                        r = row + dr;
                        c = col + dc;

                        while (this->squares[r][c] == -color)
                        {
                            this->squares[r][c] = color;
                            r += dr;
                            c += dc;
                        }
                    }

            // Update the counts.
            this->UpdateCounts();
        }
 void Board::UpdateCounts()
        {
            // Reset all counts.
            this->blackCount = 0;
            this->whiteCount = 0;
            this->emptyCount = 0;
            this->blackFrontierCount = 0;
            this->whiteFrontierCount = 0;
            this->whiteSafeCount = 0;
            this->blackSafeCount = 0;

            int i, j;


            bool statusChanged = true;
            while (statusChanged)
            {
                statusChanged = false;
                for (i = 0; i < 8; i++)
                    for (j = 0; j < 8; j++)
                        if (this->squares[i][j] != Empty && !this->safediscs[i][j] && !this->IsOutflankable(i, j))
                        {
                            this->safediscs[i][j] = true;
                            statusChanged = true;
                        }
            }


            int dr, dc;
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)
                {
                    //  if it is on the frontier
                    bool isFrontier = false;
                    if (this->squares[i][j] !=Empty)
                    {
                        for (dr = -1; dr <= 1; dr++)
                            for (dc = -1; dc <= 1; dc++)
                                if (!(dr == 0 && dc == 0) && i + dr >= 0 && i + dr < 8 && j + dc >= 0 && j + dc < 8 && this->squares[i + dr][j + dc] == Empty)
                                    isFrontier = true;
                    }

                    // Update the counts.
                    if (this->squares[i][j] ==Black)
                    {
                        this->blackCount++;
                        if (isFrontier)
                            this->blackFrontierCount++;
                        if (this->safediscs[i][j])
                            this->blackSafeCount++;
                    }
                    else if (this->squares[i][j] == White)
                    {
                        this->whiteCount++;
                        if (isFrontier)
                            this->whiteFrontierCount++;
                        if (this->safediscs[i][j])
                            this->whiteSafeCount++;
                    }
                    else
                        this->emptyCount++;
                }
        }
 bool Board::IsOutflankable(int row, int col)
        {
            // Get the disc color.
            int color = this->squares[row][col];


            int i, j;
            bool hasSpaceSide1, hasSpaceSide2;
            bool hasUnsafeSide1, hasUnsafeSide2;

            // Check the horizontal line
            hasSpaceSide1 = false;
            hasUnsafeSide1 = false;
            hasSpaceSide2 = false;
            hasUnsafeSide2 = false;
            // West side.
            for (j = 0; j < col && !hasSpaceSide1; j++)
                if (this->squares[row][j] == Empty)
                    hasSpaceSide1 = true;
                else if (this->squares[row][j] != color || !this->safediscs[row][j])
                    hasUnsafeSide1 = true;
            // East side.
            for (j = col + 1; j < 8 && !hasSpaceSide2; j++)
                if (this->squares[row][j] == Empty)
                    hasSpaceSide2 = true;
                else if (this->squares[row][j] != color || !this->safediscs[row][j])
                    hasUnsafeSide2 = true;
            if ((hasSpaceSide1 && hasSpaceSide2) ||
                (hasSpaceSide1 && hasUnsafeSide2) ||
                (hasUnsafeSide1 && hasSpaceSide2))
                return true;

            // Check the vertical line through the disc.
            hasSpaceSide1 = false;
            hasSpaceSide2 = false;
            hasUnsafeSide1 = false;
            hasUnsafeSide2 = false;
            // North side.
            for (i = 0; i < row && !hasSpaceSide1; i++)
                if (this->squares[i][col] ==Empty)
                    hasSpaceSide1 = true;
                else if (this->squares[i][col] != color || !this->safediscs[i][col])
                    hasUnsafeSide1 = true;
            // South side.
            for (i = row + 1; i < 8 && !hasSpaceSide2; i++)
                if (this->squares[i][col] == Empty)
                    hasSpaceSide2 = true;
                else if (this->squares[i][col] != color || !this->safediscs[i][col])
                    hasUnsafeSide2 = true;
            if ((hasSpaceSide1 && hasSpaceSide2) ||
                (hasSpaceSide1 && hasUnsafeSide2) ||
                (hasUnsafeSide1 && hasSpaceSide2))
                return true;

            // Check the Northwest-Southeast
            hasSpaceSide1 = false;
            hasSpaceSide2 = false;
            hasUnsafeSide1 = false;
            hasUnsafeSide2 = false;
            // Northwest side.
            i = row - 1;
            j = col - 1;
            while (i >= 0 && j >= 0 && !hasSpaceSide1)
            {
                if (this->squares[i][j] == Empty)
                    hasSpaceSide1 = true;
                else if (this->squares[i][j] != color || !this->safediscs[i][j])
                    hasUnsafeSide1 = true;
                i--;
                j--;
            }
            // Southeast side.
            i = row + 1;
            j = col + 1;
            while (i < 8 && j < 8 && !hasSpaceSide2)
            {
                if (this->squares[i][j] ==Empty)
                    hasSpaceSide2 = true;
                else if (this->squares[i][j] != color || !this->safediscs[i][j])
                    hasUnsafeSide2 = true;
                i++;
                j++;
            }
            if ((hasSpaceSide1 && hasSpaceSide2) ||
                (hasSpaceSide1 && hasUnsafeSide2) ||
                (hasUnsafeSide1 && hasSpaceSide2))
                return true;

            // Check the Northeast-Southwest
            hasSpaceSide1 = false;
            hasSpaceSide2 = false;
            hasUnsafeSide1 = false;
            hasUnsafeSide2 = false;
            // Northeast side.
            i = row - 1;
            j = col + 1;
            while (i >= 0 && j < 8 && !hasSpaceSide1)
            {
                if (this->squares[i][j] == Empty)
                    hasSpaceSide1 = true;
                else if (this->squares[i][j] != color || !this->safediscs[i][j])
                    hasUnsafeSide1 = true;
                i--;
                j++;
            }
            // Southwest side.
            i = row + 1;
            j = col - 1;
            while (i < 8 && j >= 0 && !hasSpaceSide2)
            {
                if (this->squares[i][j] ==Empty)
                    hasSpaceSide2 = true;
                else if (this->squares[i][j] != color || !this->safediscs[i][j])
                    hasUnsafeSide2 = true;
                i++;
                j--;
            }
            if ((hasSpaceSide1 && hasSpaceSide2) ||
                (hasSpaceSide1 && hasUnsafeSide2) ||
                (hasUnsafeSide1 && hasSpaceSide2))
                return true;

            // All lines are safe so the disc cannot be outflanked.
            return false;
        }

Board::~Board() {
	// TODO Auto-generated destructor stub
}
