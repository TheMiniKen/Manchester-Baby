/*
 * Sam Glendenning
 * Dylan Keningale
 * Matthew Daldry
 * Will Lockett
 *
 * COMPUTER SYSTEMS 2A: ASSIGNMENT 3
 * THE MANCHESTER SMALL-SCALE EXPERIMENTAL MACHINE (BABY)
 * Header file for Baby object
 */

#ifndef BABY_H_
#define BABY_H_

/*
 * Should be returned from any of the 7 standard operations.
 * This helps diagnose any faults and safely shut Baby down.
 * Feel free to add more if you think they could be useful.
 */
#define SUCCESS	(0)
#define FAIL (1)

using namespace std;

class Baby
{
private:
	int store[32][32];				//Baby's memory store
	string accumulator;				//Accumulator register
	string currentInstruction;		//Current instruction register
	string presentInstruction;		//Present instruction register

//See baby.cpp for details of each function
public:
	Baby();

	string getAccumulator();
	string getCurrentInstruction();
	string getPresentInstruction();

	string readLineFromStore(int lineNumber);
	void displayStore();
	int getOperand(int lineNumber);
	int getOpcode(int lineNumber);

	int JMP();
	int JRP();
	int LDN();
	int STO(int operand);
	int SUB();
	int CMP();

	int test();

	~Baby();
};

#endif /* BABY_H_ */
