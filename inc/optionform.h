/*
 * optionform.h
 *
 *  Created on: Aug 27, 2010
 *      Author: Shahid najam
 */

#ifndef OPTIONFORM_H_
#define OPTIONFORM_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FApp.h>
#include <FUi.h>
#include <FSystem.h>
#include <FAppAppRegistry.h>
class optionform:
		public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener{
public:
	optionform();
	virtual ~optionform();
	bool Initialize(void);
public:
	static const int ID_BUTTON_OK = 101;
	static const int ID_SOFTKEY_LEFT = 103;
	static const int ID_SOFTKEY_RIGHT = 104;
	Osp::Ui::Controls::CheckButton *checkcomputer;
	Osp::Ui::Controls::CheckButton *cbeginner;
	Osp::Ui::Controls::CheckButton *cinter;
	Osp::Ui::Controls::CheckButton *cadvanced;
	Osp::Ui::Controls::CheckButton *cexpert;
	Osp::Ui::Controls::Button *pButtonOk;
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
};

#endif /* OPTIONFORM_H_ */
