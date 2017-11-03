/*
 * Sam Glendenning
 * Dylan Keningale
 * Matthew Daldry
 * Will Lockett
 *
 * COMPUTER SYSTEMS 2A: ASSIGNMENT 3
 * THE MANCHESTER SMALL-SCALE EXPERIMENTAL MACHINE (BABY)
 *
 * Baby source file
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "baby.h"

using namespace std;

/*
 * Constructor for Baby. Assigns all values in the store to 0 and sets accumulator to 0.
 * Accumulator will increase to 1 before any instructions are performed.
 * Currently, accumulator value of 1 indicates first line should be read (which has index 0).
 * This can, and probably should, be changed.
 */
Baby::Baby()
{
	for (int i=0; i<32; i++)
	{
		for (int j=0; j<32; j++)
		{
			store[i][j] = 0;
		}
	}

	accumulator = "00000000000000000000000000000000";
	currentInstruction = "";
	presentInstruction = "";
}

/*
 * Destructor for Baby. Sets all values in the store to 0 and sets all registers' values
 * to empty strings.
 */
Baby::~Baby()
{
	for (int i=0; i<32; i++)
	{
		for (int j=0; j<32; j++)
		{
			store[i][j] = 0;
		}
	}

	accumulator = "";
	currentInstruction = "";
	presentInstruction = "";

	cout << "Shutting Baby down..." << endl;
}

/*
 * Returns the current value of the accumulator register.
 */
string Baby::getAccumulator()
{
	return accumulator;
}

/*
 * Returns the current value of the current instruction register.
 */
string Baby::getCurrentInstruction()
{
	return currentInstruction;
}

/*
 * Returns the current value of the present instruction register.
 */
string Baby::getPresentInstruction()
{
	return presentInstruction;
}

/*
 * Reads a 32-bit number from the store. Requires the entire store to be passed in and the
 * appropriate line number (first line = 0).
 * In future, this line will not need an integer representing the line number to be passed in.
 * What will actually happen is it will just read the accumulator (since accumulator will hold
 * the appropriate operand from the last instruction? Is that right?)
 */
string Baby::readLineFromStore(int store[][32], int lineNumber)
{
	string instruction = "";

	for (int i=0; i<32; i++)
	{
		instruction += to_string(store[lineNumber][i]);
	}

	return instruction;
}

/*
 * Retrieves the decimal value of the opcode of a specific line in the store.
 * This function may be better off just reading a string instruction passed in from the
 * current instruction register, so subject to change.
 */
int Baby::getOpcode(int store[][32], int lineNumber)
{
	string opcode = "";

	for (int i=13; i<16; i++)
	{
		opcode += to_string(store[lineNumber][i]);		//Obtains the entire store line as string
	}

	if (opcode == "000")
		return 0;
	else if (opcode == "100")
		return 1;
	else if (opcode == "010")
		return 2;
	else if (opcode == "110")
		return 3;
	else if (opcode == "001")
		return 4;
	else if (opcode == "101")
		return 5;
	else if (opcode == "011")
		return 6;
	else
		return 7;
}

/*
 * Retrieves the decimal value of the operand of a specific line in the store.
 * This function may be better off just reading a string instruction passed in from the
 * current instruction register, so subject to change.
 */
int Baby::getOperand(int store[][32], int lineNumber)
{
	string operand = "";

	for (int i=0; i<5; i++)
	{
		operand += to_string(store[lineNumber][i]);
	}

	//return binaryToDecimal(operand);		//Retrieves the value 0-31 for the operand

	//TO BE DELETED. THIS SHOULD BE COVERED BY DYLAN'S BINARY TO DECIMAL FUNCTION (SEE ABOVE)
	//ONLY HERE FOR TEMPORARY USE
	if (operand == "00000")
		return 0;
	else if (operand == "10000")
		return 1;
	else if (operand == "01000")
		return 2;
	else if (operand == "11000")
		return 3;
	else if (operand == "00100")
		return 4;
	else if (operand == "10100")
		return 5;
	else if (operand == "01100")
		return 6;
	else if (operand == "11100")
		return 7;
	else if (operand == "00010")
		return 8;
	else if (operand == "10010")
		return 9;
	else if (operand == "01010")
		return 10;
	else if (operand == "11010")
		return 11;
	else if (operand == "00110")
		return 12;
	else if (operand == "10110")
		return 13;
	else if (operand == "01110")
		return 14;
	else if (operand == "11110")
		return 15;
	else if (operand == "00001")
		return 16;
	else if (operand == "10001")
		return 17;
	else if (operand == "01001")
		return 18;
	else if (operand == "11001")
		return 19;
	else if (operand == "00101")
		return 20;
	else if (operand == "10101")
		return 21;
	else if (operand == "01101")
		return 22;
	else if (operand == "11101")
		return 23;
	else if (operand == "00011")
		return 24;
	else if (operand == "10011")
		return 25;
	else if (operand == "01011")
		return 26;
	else if (operand == "11011")
		return 27;
	else if (operand == "00111")
		return 28;
	else if (operand == "10111")
		return 29;
	else if (operand == "01111")
		return 30;
	else
		return 31;
}

/*
 * Displays the entire store. Called after every instruction is executed.
 * In the program, this could be every second, maybe?
 */
void Baby::displayStore(int store[][32])
{
	for (int i=0; i<32; i++)
	{
		for (int j=0; j<32; j++)
		{
			cout << store[i][j];
		}

		cout << endl;
	}
}

/*
 * Test STO function. STO is used to store the value of the accumulator register in a
 * specified location in the store. In the test function, this changes the first line of
 * the store (run the program and see).
 */
int Baby::STO(int store[][32], string accumulator, int operand)
{
	for (int i=0; i<32; i++)
	{
		if (accumulator[i] == '0')
		{
			store[operand][i] = 0;
		}
		else
		{
			store[operand][i] = 1;
		}
	}

	return SUCCESS;
}

/*
 * Simple demo of Baby's functionality.
 * NOTE: The variables instruction, accumulator, operand and opcode are NOT affiliated with
 * Baby's own variables of similar names. This was purely a demo to test Baby's functionality
 * with such variables.
 */
int Baby::test()
{
	string instruction;
	int operand;
	int opcode;

	instruction = readLineFromStore(store, 0);
	operand = getOperand(store, 0);
	opcode = getOpcode(store, 0);

	cout << "Output of first line of store is " << instruction << endl;
	cout << "Operand = " << operand << endl;
	cout << "Opcode = " << opcode << endl << endl;
	cout << "STORE BEFORE STO OPERATION:" << endl;

	displayStore(store);

	cout << endl << "Changing first line of store..." << endl;

	string accumulator = "00111001011111010010001000010101";	//Random value of the accumulator
	if (STO(store, accumulator, 0) != SUCCESS)
	{
		cout << "The STO function failed!" << endl;
		return FAIL;
	}

	cout << endl << "STORE AFTER STO OPERATION:" << endl;
	displayStore(store);

	instruction = readLineFromStore(store, 0);
	operand = getOperand(store, 0);
	opcode = getOpcode(store, 0);

	cout << endl << "Output of first line of store is " << instruction << endl;
	cout << "Operand = " << operand << endl;
	cout << "Opcode = " << opcode << endl << endl;

	return SUCCESS;
}
