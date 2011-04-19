/*
 * optionform.cpp
 *
 *  Created on: Aug 27, 2010
 *      Author: Shahid najam
 */

#include "optionform.h"
#include "Form1.h"
using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Collection;

optionform::optionform() {
	// TODO Auto-generated constructor stub

}

optionform::~optionform() {
	// TODO Auto-generated destructor stub
}
bool optionform::Initialize() {
	// Construct an XML form
	Construct(L"IDF_FORM2");

	return true;
}

result optionform::OnInitializing(void) {
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	// Get a button via resource ID
	pButtonOk = static_cast<Button *> (GetControl(L"IDC_BUTTON1"));
	checkcomputer=static_cast<CheckButton *>(GetControl(L"IDC_CHECKBUTTON1"));
	cbeginner=static_cast<CheckButton *>(GetControl(L"IDC_CHECKBUTTON2"));
	cinter=static_cast<CheckButton *>(GetControl(L"IDC_CHECKBUTTON3"));
	cadvanced=static_cast<CheckButton *>(GetControl(L"IDC_CHECKBUTTON4"));
	cexpert=static_cast<CheckButton *>(GetControl(L"IDC_CHECKBUTTON5"));
	if (pButtonOk != null)
	{
		pButtonOk->SetActionId(ID_BUTTON_OK);
		pButtonOk->AddActionEventListener(*this);
	}

	AppRegistry *registry=Application::GetInstance()->GetAppRegistry();
	int complay=-1;
	int level;
	registry->Get("computerplay",complay);
	registry->Get("difficulty",level);
	if(complay==1)
	checkcomputer->SetSelected(true);
	else
	checkcomputer->SetSelected(false);

	if(level==0)
	cbeginner->SetSelected(true);
	else if(level==1)
	cinter->SetSelected(true);
	else if(level==2)
	cadvanced->SetSelected(true);
	else if(level==3)
	cexpert->SetSelected(true);

	this->SetSoftkeyActionId(SOFTKEY_0,ID_SOFTKEY_LEFT);
	this->SetSoftkeyActionId(SOFTKEY_1,ID_SOFTKEY_RIGHT);
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	// Create a Panel

			return r;
		}

result optionform::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void optionform::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	switch (actionId) {
	case ID_BUTTON_OK: {

		// Set the current form


	}
		break;
	case ID_SOFTKEY_LEFT: {
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

		AppRegistry *registry = Application::GetInstance()->GetAppRegistry();
		if (checkcomputer->IsSelected() == true)
			registry->Set("computerplay", 1);
		else
			registry->Set("computerplay", 0);
		//difficulty level
		if (cbeginner->IsSelected() == true)
			registry->Set("difficulty", 0);
		else if (cinter->IsSelected() == true)
			registry->Set("difficulty", 1);
		else if (cadvanced->IsSelected() == true)
			registry->Set("difficulty", 2);
		else if (cexpert->IsSelected() == true)
			registry->Set("difficulty", 3);
		registry->Save();

		Form1 *pForm1 = new Form1();
		pForm1->Initialize();

		pFrame->AddControl(*pForm1);
		pFrame->SetCurrentForm(*pForm1);
		pForm1->Draw();
		pForm1->Show();
		pFrame->RemoveControl(*this);

	}
		break;
	case ID_SOFTKEY_RIGHT: {
		MessageBox messageBox;
		messageBox.Construct(L"Quit", L"Are you sure to quit?", MSGBOX_STYLE_YESNO,6000);

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
