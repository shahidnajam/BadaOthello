#ifndef _FORM1_H_
#define _FORM1_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FBaseRtThread.h>
#include <FBaseRtThreadIRunnable.h>
#include <cmath>
#include <FAppAppRegistry.h>
#include "squarecontrol.h"
#include "board.h"
#include "Options.h"
class Form1 :

	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::ITouchEventListener,
	public Osp::Base::Runtime::IRunnable

{

// Construction
public:
	Form1(void);
	virtual ~Form1(void);
	bool Initialize(void);
	 virtual Object* Run(void);


// Implementation
protected:


	static const int ID_BUTTON_OK = 101;
	static const int ID_SOFTKEY_LEFT = 103;
	static const int ID_SOFTKEY_RIGHT = 104;
	Osp::Ui::Controls::Label *pwlabel;
	Osp::Ui::Controls::Label *pblabel;
	Osp::Ui::Controls::Label *statuslabel;
	Osp::Ui::Controls::Panel *mypanel;

public:

 struct ComputerMove
	{

int row;
int col;
int rank;
ComputerMove()
{
	row=-1;
	col=-1;
rank=0;
}
	};
	enum Difficulty
	{
		Beginner,
		Intermediate,
		Advanced,
		Expert
	};
	enum GameState
	        {
	            GameOver,			// The game is over (also used for the initial state).
	            InMoveAnimation,	// A move has been made and the animation is active.
	            InPlayerMove,		// Waiting for the user to make a move.
	            InComputerMove,		// Waiting for the computer to make a move.
	            MoveCompleted		// A move has been completed (including the animation, if active).
	        };

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
void square_click();
	void OnTouchPressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition,const Osp::Ui::TouchEventInfo & touchInfo);
	void OnTouchLongPressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition ,const Osp::Ui::TouchEventInfo & touchInfo);
	void OnTouchReleased(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition ,const Osp::Ui::TouchEventInfo & touchInfo);
	void OnTouchMoved(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);
	void OnTouchDoublePressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition,const Osp::Ui::TouchEventInfo & touchInfo);
	void OnTouchFocusIn(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition,const Osp::Ui::TouchEventInfo & touchInfo);
	void OnTouchFocusOut(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition,const Osp::Ui::TouchEventInfo & touchInfo);

private:
	 Osp::Base::Runtime::Thread * mythread;
bool isComputerPlaySuspended;
	Board *board;
 GameState gameState;
 Options *options;
 int currentColor;
int moveNumber;
  // AI parameters.
int lookAheadDepth;
int forfeitWeight;
  int frontierWeight;
int mobilityWeight;
int stabilityWeight;
int lastMoveColor;
int maxRank;
void UpdateBoardDisplay();
void EndGame();
bool IsComputerPlayer(int color);
void StartTurn();
void SetAIParameters();
void HighlightValidMoves();
void StartGame(bool isRestart);
void UnHighlightSquares();
squarecontrol sqctrl[8][8];
ComputerMove GetBestMove(Board *board);
ComputerMove GetBestMove(Board *board, int color, int depth, int alpha, int beta);
void MakeMove(int row, int col);
void EndMove();
void MakePlayerMove(int row, int col);
void MakeComputerMove(int row, int col);


};



#endif	//_FORM1_H_
