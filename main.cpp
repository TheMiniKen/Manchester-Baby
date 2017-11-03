/*
 * Sam Glendenning
 * Dylan Keningale
 * Matthew Daldry
 * Will Lockett
 *
 * COMPUTER SYSTEMS 2A: ASSIGNMENT 3
 * THE MANCHESTER SMALL-SCALE EXPERIMENTAL MACHINE (BABY)
 *
 * Main source file
 */

#include <iostream>
#include "baby.h"

using namespace std;

int main()
{
	Baby *baby = new Baby();		//A pointer to a new baby object. Refer to it as baby, not *baby

	if (baby->test() != SUCCESS)	//If baby's test function did not return success
	{
		cout << "Critical program failure. Baby is dead :(" << endl;
	}
	else
	{
		cout << "Test was successful!" << endl;
	}

	delete baby;			//Safely delete the baby object (has a programmed destructor)

	return 0;
}
