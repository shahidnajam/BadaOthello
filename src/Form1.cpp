#include "Form1.h"
#include "optionform.h"
using namespace Osp::Base;
using namespace Osp::App;
using namespace Osp::Base::Collection;
using namespace Osp::Base::Utility;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Media;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;
Form1::Form1(void)
{
}

Form1::~Form1(void)
{
}

bool
Form1::Initialize()
{
	// Construct an XML form
	Construct(L"IDF_FORM1");

	return true;
}

result
Form1::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	// Get a button via resource ID

	this->SetSoftkeyActionId(SOFTKEY_0,ID_SOFTKEY_LEFT);
	this->SetSoftkeyActionId(SOFTKEY_1,ID_SOFTKEY_RIGHT);
	this->SetBackgroundColor(Color(0x1E, 0x90, 0xFF));
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
options=new Options();
AppRegistry *registry=Application::GetInstance()->GetAppRegistry();
int complay=-1;
int level;
registry->Get("computerplay",complay);
registry->Get("difficulty",level);

if(complay==0)
	options->ComputerPlaysWhite=false;
else
	options->ComputerPlaysWhite=true;
options->Difficulty=level;
board=new Board();
mypanel=new Panel();


pwlabel=static_cast<Label *>(GetControl(L"IDC_LABEL3"));
pblabel=static_cast<Label *>(GetControl(L"IDC_LABEL4"));
statuslabel=static_cast<Label *>(GetControl(L"IDC_LABEL5"));
mypanel->Construct(Rectangle(2,90,480,480));
mypanel->SetBackgroundColor(Color::COLOR_CYAN);
squarecontrol *wpanel=new squarecontrol();
wpanel->Construct(Rectangle(10,15,60,60));
wpanel->contents=1;



squarecontrol *bpanel=new squarecontrol();

bpanel->Construct(Rectangle(253,15,60,60));
bpanel->contents=-1;


this->AddControl(*wpanel);
this->AddControl(*bpanel);
this->AddControl(*mypanel);

this->maxRank=64000;
for(int i=0;i<8;i++)
{
	for(int j=0;j<8;j++)
	{




	sqctrl[i][j].Construct(Rectangle(j*60,i*60,60,60));
	sqctrl[i][j].row=i;
	sqctrl[i][j].col=j;
	sqctrl[i][j].contents=0;
	sqctrl[i][j].AddTouchEventListener(*this);
	String name;
	name.Append(int(i));
	name.Append(int(j));
sqctrl[i][j].SetName(name);
	mypanel->AddControl(sqctrl[i][j]);
	}
}

this->StartGame(false);
	return r;
}

Object* Form1::Run(void)
        {

	this->SetAIParameters();

	               	            // Find the best available move.
	        ComputerMove move = this->GetBestMove(this->board);
	                    this->MakeComputerMove(move.row,move.col);

         return null;
        }

void Form1::StartTurn()
       {

           // If the current player cannot make a valid move, forfeit the turn.
           if (!this->board->HasAnyValidMove(this->currentColor))
           {
               // Switch back to the other player.

               this->currentColor *= -1;

               // If the original player cannot make a valid move either, the game is over.
               if (!this->board->HasAnyValidMove(this->currentColor))
               {

                   this->EndGame();

                   return;
               }
               else
               {




               }
           }

           // Set the player text for the status display.
      String playerText = (this->currentColor == Black) ? "Black" : "White";
      if ((this->options->ComputerPlaysBlack && !this->options->ComputerPlaysWhite) ||
          (this->options->ComputerPlaysWhite && !this->options->ComputerPlaysBlack))
           playerText = (this->IsComputerPlayer(this->currentColor) ? "Computer" : "Your");

           // Update the turn display.
         /*  if (this->currentColor == Black)
               this->currentColorPanel.BackColor = Color.Black;
           else
               this->currentColorPanel.BackColor = Color.White;
*/
           // If the current color is under computer control, set up for a
           // computer move.
           if (this->IsComputerPlayer(this->currentColor))
           {
               // Set the game state.
               this->gameState = InComputerMove;
               String st;
               st.Append( playerText);
               st.Append(" move, thinking...");
                              // Update the status display.

               this->statuslabel->SetText(st);
                                     this->statuslabel->RequestRedraw(true);
               // Check if computer play is currently suspended.

                                   mythread=new Thread();
 mythread->Construct(*this,Thread::DEFAULT_STACK_SIZE,THREAD_PRIORITY_LOW);

mythread->Start();



           }

           // Otherwise, set up for a user move.
           else
           {
               // Set the game state.
               this->gameState = InPlayerMove;




               // Show valid moves, if that option is active.

                  this->HighlightValidMoves();


String st;
st.Append( playerText);
st.Append(" move...");
               // Update the status display.
           this->statuslabel->SetText(st);
           this->statuslabel->RequestRedraw(true);


           }

           // Update the status display.


       }
 void Form1::MakeComputerMove(int row, int col)
        {

                // Make the move.

                this->MakeMove(row, col);

        }
bool Form1::IsComputerPlayer(int color)
        {
            return ((this->options->ComputerPlaysBlack && color == Black) ||
            (this->options->ComputerPlaysWhite && color == White));
        }

   void Form1::StartGame(bool isRestart)
       {
           // Enable/disable the menu items and tool bar buttons



           // Initialize the information display.
      //     this->currentColorTextLabel.Visible = true;
           //this->currentColorPanel.Visible = true;

           // Initialize a new game.
           if (!isRestart)
           {
               // Initialize the move list.
               this->moveNumber = 1;


               // Initialize the last move color.
               this->lastMoveColor =Empty;

               // Clear the suspend computer play flag.


               // Initialize the board->
              this->board->setfornewgame();
          this->UpdateBoardDisplay();

               // Initialize the status display.


               // Set the first player.
             this->currentColor = this->options->FirstMove;
           }

           // Start the first turn.
  this->StartTurn();
       }
void Form1::SetAIParameters()
        {
            // Set the AI parameter weights.
            switch (this->options->Difficulty)
            {
                case Beginner:
                    this->forfeitWeight =0;
                    this->frontierWeight = 1;
                    this->mobilityWeight = 0;
                    this->stabilityWeight =0;
                    this->lookAheadDepth = 1;
                    break;
                case Intermediate:
                    this->forfeitWeight = 3;
                    this->frontierWeight = 1;
                    this->mobilityWeight = 0;
                    this->stabilityWeight = 5;
                    this->lookAheadDepth = 2;
                    break;
                case Advanced:
                    this->forfeitWeight = 7;
                    this->frontierWeight = 2;
                    this->mobilityWeight = 1;
                    this->stabilityWeight = 10;
                    this->lookAheadDepth = 4;
                    break;
                case Expert:
                    this->forfeitWeight = 35;
                    this->frontierWeight = 10;
                    this->mobilityWeight = 5;
                    this->stabilityWeight = 50;
                    this->lookAheadDepth = 5;
                    break;
                default:
                    this->forfeitWeight = 0;
                    this->frontierWeight = 0;
                    this->mobilityWeight = 0;
                    this->stabilityWeight = 0;
                    this->lookAheadDepth = 0;
                    break;
            }





        }
 void Form1::MakeMove(int row, int col)
        {
            // Add the move to the move list.
            String color = "Black";
            if (this->currentColor == White)
                color = "White";

            // Enable/disable the move-related menu items and tool bar buttons as
            // appropriate.


            // increment the move number.
            this->moveNumber++;

            // Update the status display.



            // Clear any board square highlighting.
            this->UnHighlightSquares();

            // Make a copy of the board (for doing move animation).

            // Make the move on the board.
            this->board->MakeMove(this->currentColor, row, col);

                       this->lastMoveColor = this->currentColor;

            // If the animate moves option is active, start the animation.

                this->EndMove();
          //  sndPlayer.Play();
            this->UpdateBoardDisplay();

        }
 void Form1::UnHighlightSquares()
 {
     squarecontrol *squareControl;
     int i, j;
     for (i = 0; i < 8; i++)
         for (j = 0; j < 8; j++)
         {

        	 squareControl = static_cast<squarecontrol*>(mypanel->GetControl(i*8+j));
             squareControl->isvalid = false;
         }
 }
     void Form1::EndMove()
        {
            // Set the game state.
            this->gameState =MoveCompleted;

            // Switch players and start the next turn.
            this->currentColor *= -1;
            this->StartTurn();
        }

void Form1::HighlightValidMoves()
       {
           // Check each square.
           squarecontrol *squareControl;
           int i, j;
           for (i = 0; i < 8; i++)
               for (j = 0; j < 8; j++)
               {

            	   squareControl = static_cast<squarecontrol*>(mypanel->GetControl(i*8+j));
                            if (this->board->IsValidMove(this->currentColor, i, j))
                       squareControl->isvalid = true;
                   else
                       squareControl->isvalid = false;
               }
           mypanel->RequestRedraw(true);
       }
  void Form1::UpdateBoardDisplay()
        {

	  this->pwlabel->SetText(Integer::ToString(this->board->whiteCount));
	  this->pblabel->SetText(Integer::ToString(this->board->blackCount));
	  this->pwlabel->RequestRedraw(true);
	  this->pblabel->RequestRedraw(true);
	                // Map the current game board to the square controls.
            squarecontrol *squareControl;
            int i, j;
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)
                {
                	  squareControl = static_cast<squarecontrol*>(mypanel->GetControl(i*8+j));

                	  squareControl->contents = this->board->GetSquareContents(i, j);






                                 }

            // Redraw the board.
            mypanel->RequestRedraw(true);
        }

Form1::ComputerMove Form1::GetBestMove(Board *board)
        {
            // Initialize the alpha-beta cutoff values.

            int alpha =	maxRank+ 64;

            int beta = -alpha;

            // Kick off the look ahead.
    return  GetBestMove(board, currentColor, 1, alpha, beta);
        }
Form1::ComputerMove Form1::GetBestMove(Board *board, int color, int depth, int alpha, int beta)
       {

           // Initialize the best move.

           ComputerMove bestMove ;
           bestMove.col=-1;
           bestMove.row=-1;
           bestMove.rank = -color * this->maxRank;

           // Find out how many valid moves we have so we can initialize the
           // mobility score.

           int validMoves = this->board->GetValidMoveCount(color);


           // Check all valid moves.
           int i, j;
           for (i = 0; i < 8; i++)
           {
               for (j = 0; j < 8; j++)

               {

                   // Get the row and column.
                   int row = i;
                   int col = j;



                   if (board->IsValidMove(color, row, col))
                   {


                                          // Update the progress bar for each move when on the
                       // first look ahead depth level.
               //   if (depth == 1)
                     // this->UpdateStatusProgress();

                       // Make the move.

                       ComputerMove testMove ;
                       testMove.row=row;
                       testMove.col=col;
                       Board *testBoard = new Board(*board);

                       testBoard->MakeMove(color, testMove.row, testMove.col);
                       int score = testBoard->whiteCount - testBoard->blackCount;

                       // Check the board->
                       int nextColor = -color;
                       int forfeit = 0;
                       bool isEndGame = false;
                       int opponentValidMoves = testBoard->GetValidMoveCount(nextColor);
                       if (opponentValidMoves == 0)
                       {
                           // The opponent cannot move, count the forfeit.
                           forfeit = color;

                           // Switch back to the original color.
                           nextColor = -nextColor;

                           // If that player cannot make a move
                           // game is over.
                           if (!testBoard->HasAnyValidMove(nextColor))
                               isEndGame = true;
                       }


                       if (isEndGame || depth == this->lookAheadDepth)
                       {
                           //end game,  add on the
                           // final score.
                           if (isEndGame)
                           {
                               // Negative value for black win.
                               if (score < 0)
                                   testMove.rank = -this->maxRank + score;

                               // Positive value for white win.
                               else if (score > 0)
                                   testMove.rank = this->maxRank + score;

                               // Zero for a draw.
                               else
                                   testMove.rank = 0;
                           }

                           // It's not an end game so calculate the move rank.
                           else
                               testMove.rank =
                                   this->forfeitWeight * forfeit +
                                   this->frontierWeight * (testBoard->blackFrontierCount - testBoard->whiteFrontierCount) +
                                   this->mobilityWeight * color * (validMoves - opponentValidMoves) +
                                   this->stabilityWeight * (testBoard->whiteSafeCount - testBoard->blackSafeCount) +
                                                            score;

                       }


                       else
                       {
                           ComputerMove nextMove;
                           nextMove.row=-1;
                           nextMove.col=-1;
                           nextMove.rank=-1;

                           nextMove=GetBestMove(testBoard, nextColor, depth+1, alpha, beta);


                           testMove.rank = nextMove.rank;


                           if (forfeit != 0 && Math::Abs(testMove.rank) < this->maxRank)
                               testMove.rank += forfeitWeight * forfeit;


                           if (color == 1 && testMove.rank >= beta)
                               beta = testMove.rank;
                           if (color == -1 && testMove.rank <= alpha)
                               alpha = testMove.rank;
                       }


                       //Min alpha cuteoff
                       if (color == 1 && testMove.rank > alpha)
                       {
                           testMove.rank = alpha;

                           return testMove;
                       }
                       //Max beta cuteoff
                       if (color == -1 && testMove.rank < beta)
                       {
                           testMove.rank = beta;

                           return testMove;
                       }

                       // If this is the first move tested, assume it is the
                       // best for now.
                       if (bestMove.row < 0)
                           bestMove = testMove;


                       else if (color * testMove.rank > color * bestMove.rank)
                           bestMove = testMove;
                   }

               }

           }

           // Return the best move found.

           return bestMove;

       }
 void Form1::MakePlayerMove(int row, int col)
        {
            // Allow the computer to resume play.
           this->isComputerPlaySuspended = false;

            // Make the move.
            this->MakeMove(row, col);
        }
 void Form1::EndGame()
        {

	 this->gameState = GameOver;

	            // Stop the game timer.



	            // For a computer vs. user game, determine who played what color.
	            int computerColor = Empty;
	            int userColor = Empty;
	            if (this->IsComputerPlayer(Black) && !this->IsComputerPlayer(White))
	            {
	                computerColor = Black;
	                userColor = White;
	            }
	            if (this->IsComputerPlayer(White) && !this->IsComputerPlayer(Black))
	            {
	                computerColor =White;
	                userColor = Black;
	            }



	                // Update the status message.
	                if (this->board->blackCount > this->board->whiteCount)
	                {

String str;
str.Append("Black won by ");
str.Append(this->board->blackCount);
str.Append(":");
str.Append(this->board->whiteCount);
	                    this->statuslabel->SetText(str);

	                }
	                else if (this->board->whiteCount > this->board->blackCount)
	                {
	                	String str;
	                	str.Append("White won by ");
	                	str.Append(this->board->whiteCount);
	                	str.Append(":");
	                	str.Append(this->board->blackCount);
	                	this->statuslabel->SetText(str);
	                }

	                else
	                    this->statuslabel->SetText("Draw");
this->statuslabel->RequestRedraw(true);
	                // Record the result.

	           //     MessageBox.Show(this->statuslabel.Text,"Game Over",MessageBoxButtons.OK,MessageBoxIcon.Information);

	 //    MessageBox messageBox;
	  //    messageBox.Construct(L"Game Over",L"hello", MSGBOX_STYLE_OK, 6000);


	          //  int modalResult = 0;
	          // messageBox.ShowAndWait(modalResult);

	            // Update the status display.

        }

result
Form1::OnTerminating(void)
{

	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}
void Form1::square_click()
{

	  MessageBox messageBox;
	    messageBox.Construct(L"My MessageBox", L"This is MessageBox Sample Code.", MSGBOX_STYLE_OK, 3000);

	    // Call ShowAndWait - draw, show itself and process events
	    int modalResult = 0;
	    messageBox.ShowAndWait(modalResult);

//


}

void
Form1::OnTouchPressed(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo){






}

void
Form1::OnTouchLongPressed(const Control& source,
	const Point& currentPosition ,const TouchEventInfo & touchInfo)
{

}

void
Form1::OnTouchReleased(const Control& source,
	const Point& currentPosition ,const TouchEventInfo & touchInfo){


	 if (this->gameState ==InPlayerMove)
	 {

squarecontrol *sq= (squarecontrol*)&source;



if (this->board->IsValidMove(this->currentColor, sq->row, sq->col))
        {


                // Make the move.
         this->MakePlayerMove(sq->row,sq->col);


        }

           }



}

void
Form1::OnTouchMoved(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo){

}

void
Form1::OnTouchDoublePressed(const Control& source,
	const Point& currentPosition,const TouchEventInfo & touchInfo){}

void
Form1::OnTouchFocusIn(const Control& source,
	const Point& currentPosition,const TouchEventInfo & touchInfo){}

void
Form1::OnTouchFocusOut(const Control& source,
	const Point& currentPosition,const TouchEventInfo & touchInfo){}



void
Form1::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_BUTTON_OK:
		{

		}
		break;
	case ID_SOFTKEY_LEFT:
	{
		  MessageBox messageBox;
			    messageBox.Construct(L"Start New Game", L"Are you sure to resign?", MSGBOX_STYLE_YESNO,9000);

			    // Call ShowAndWait - draw, show itself and process events
			    int modalResult = 0;
			    messageBox.ShowAndWait(modalResult);
				Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
			    switch(modalResult)
			    {
			    case MSGBOX_RESULT_YES:
			    {
					optionform *oForm = new optionform();
										oForm->Initialize();

										pFrame->AddControl(*oForm);
										pFrame->SetCurrentForm(*oForm);
										oForm->Draw();
										oForm->Show();
										pFrame->RemoveControl(*this);
			    }
			        break;

			    default:
			        break;
			    }




	}
	break;
	case ID_SOFTKEY_RIGHT:
	{
	    MessageBox messageBox;
	    messageBox.Construct(L"Quit", L"Are you sure to quit?", MSGBOX_STYLE_YESNO, 6000);

	    // Call ShowAndWait - draw, show itself and process events
	    int modalResult = 0;
	    messageBox.ShowAndWait(modalResult);

	    switch(modalResult)
	    {
	    case MSGBOX_RESULT_YES:
	    	Application::GetInstance()->Terminate();
	        break;

	    default:
	        break;
	    }


	}
	break;
	default:
		break;
	}
}


