/*
 * squarecontrol.cpp
 *
 *  Created on: Aug 24, 2010
 *      Author: Shahid najam
 */

#include "squarecontrol.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Media;
using namespace Osp::Graphics;

squarecontrol::squarecontrol() {
	// TODO Auto-generated constructor stub

}
squarecontrol::squarecontrol(int r,int c) {
	// TODO Auto-generated constructor stub
this->contents=0;
this->row=r;
this->col=c;

}
result squarecontrol::OnInitializing()
{
	   //AddTouchEventListener(*this);
	 //   Touch touch;
	   // touch.SetMultipointEnabled(*this, true);

	this->SetBackgroundColor(Color(0x32,0xcd,0x32));

		return E_SUCCESS;
}
result squarecontrol::OnDraw()
{

	if(!isvalid)
	this->SetBackgroundColor(Color(0x32,0xcd,0x32));
	else
		this->SetBackgroundColor(Color(0x24,0x74,0x1B));

	Canvas * canvas = this->GetCanvasN();
	int h,w;
	this->GetSize(w,h);
	Point * topLeft = new Point(0, 0);
			            Point * topRight = new Point(w-1, 0);
			            Point * bottomLeft = new Point(0, w-1);
			            Point * bottomRight = new Point(h-1, w-1);
		if(canvas)
		{

canvas->SetLineWidth(1);
canvas->SetForegroundColor(Color::COLOR_GREY);


				canvas->DrawLine(*bottomLeft,*topLeft);
				canvas->DrawLine(*topLeft,*topRight);
				canvas->SetForegroundColor(Color::COLOR_BLUE);
				canvas->DrawLine(*bottomLeft,*bottomRight);
				canvas->DrawLine(*bottomRight,*topRight);
				if(this->contents==-1)
				canvas->FillEllipse(Color::COLOR_BLACK,Rectangle(6,6,52,52));
				else if(this->contents==1)
					canvas->FillEllipse(Color::COLOR_WHITE,Rectangle(6,6,52,52));
			}
			delete canvas;

		return E_SUCCESS;


}
void
squarecontrol::OnActionPerformed(const Control& source, int actionId)
{

}

void
squarecontrol::OnTouchPressed(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo){






}

void
squarecontrol::OnTouchLongPressed(const Control& source,
	const Point& currentPosition ,const TouchEventInfo & touchInfo)
{

}

void
squarecontrol::OnTouchReleased(const Control& source,
	const Point& currentPosition ,const TouchEventInfo & touchInfo){



}

void
squarecontrol::OnTouchMoved(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo){

}

void
squarecontrol::OnTouchDoublePressed(const Control& source,
	const Point& currentPosition,const TouchEventInfo & touchInfo){}

void
squarecontrol::OnTouchFocusIn(const Control& source,
	const Point& currentPosition,const TouchEventInfo & touchInfo){}

void
squarecontrol::OnTouchFocusOut(const Control& source,
	const Point& currentPosition,const TouchEventInfo & touchInfo){}

squarecontrol::~squarecontrol() {
	// TODO Auto-generated destructor stub
}
