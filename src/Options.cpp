/*
 * Options.cpp
 *
 *  Created on: Aug 26, 2010
 *      Author: Shahid najam
 */

#include "Options.h"

Options::Options() {
	this->RestoreDefaults();

}
void Options::RestoreDefaults()
{

    this->FirstMove = -1;
       this->ComputerPlaysBlack = false;
       this->ComputerPlaysWhite =true;
       this->Difficulty =3;
}
Options::~Options() {
	// TODO Auto-generated destructor stub
}
