#ifndef SQUARECONTROL_H_
#define SQUARECONTROL_H_
#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <cmath>

class squarecontrol :
	public Osp::Ui::Controls::Panel,
	public Osp::Ui::ITouchEventListener
{
public:
		int contents;
			bool isvalid;
			int row,col;
			squarecontrol();
	squarecontrol(int r,int c);
	virtual ~squarecontrol();




protected:






// callbacks
public:
virtual result OnInitializing(void);
	virtual result OnDraw(void);
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
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
};


#endif /* SQUARECONTROL_H_ */
