/*
 * Options.h
 *
 *  Created on: Aug 26, 2010
 *      Author: Shahid najam
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

class Options {
public:
	Options();


	      int FirstMove;
	       bool ComputerPlaysBlack;
	       bool ComputerPlaysWhite;
	int Difficulty;
	       void RestoreDefaults();
	virtual ~Options();
};

#endif /* OPTIONS_H_ */
