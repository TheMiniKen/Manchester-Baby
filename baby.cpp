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
#include <bitset>
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
string Baby::readLineFromStore(int lineNumber)
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
int Baby::getOpcode(int lineNumber)
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
int Baby::getOperand(int lineNumber)
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
void Baby::displayStore()
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
 * Jump to the address stored in present instruction
 */
int Baby::JMP()
{
	currentInstruction = "";

	for (int i=0; i<32; i++)
	{
		if (i < 5)
		{
			if (presentInstruction[i] == '1')
			{
				currentInstruction += '1';
			}
			else
			{
				currentInstruction += '0';
			}
		}
		else
		{
			currentInstruction += '0';
		}
	}

	return SUCCESS;
}

/*
 * Jump to the address stored in currentInstruction + the value stored in presentInstruction
 */
int Baby::JRP()
{
	/*
	int presentInstructionDecimal = binaryToDecimal(presentInstruction);
	string valueAsBinary = bitset<32>(presentInstructionDecimal).to_string();
	string lsbBinary = "00000000000000000000000000000000";

	for (unsigned int i=0; i<valueAsBinary.length(); i++)
	{
		if (valueAsBinary[i] == '0')
		{
			lsbBinary[31 - i] = '0';
		}
		else
		{
			lsbBinary[31 - i] = '1';
		}
	}

	for (int i=0; i<32; i++)
	{
		if (currentInstruction[i] == '0' && lsbBinary[i] == '1')
		{
			currentInstruction[i] = '1';
		}
		else if (currentInstruction[i] == '1' && lsbBinary[i] == '1')
		{
			currentInstruction[i] = '0';
		}
	}
	*/

	return SUCCESS;
}

/*
 * Retrieves the decimal value of the present instruction, converts it to binary and then
 * swaps its values round so it reads left to right. This is stored in the accumulator
 */
int Baby::LDN()
{
	/*
	int negativeDecimal = binaryToDecimal(presentInstruction) * -1;
	string negativeBinary = bitset<32>(negativePresentInstruction).to_string();

	for (unsigned int i=0; i<negativeBinary.length(); i++)
	{
		if (negativeBinary[i] == '0')
		{
			accumulator[31 - i] = '0';
		}
		else
		{
			accumulator[31 - i] = '1';
		}
	}
	*/

	return SUCCESS;
}

/*
 * Test STO function. STO is used to store the value of the accumulator register in a
 * specified location in the store. In the test function, this changes the first line of
 * the store (run the program and see).
 */
int Baby::STO(int operand)
{
	//currentInstructionDecimal = binaryToDecimal(currentInstruction);

	for (int i=0; i<32; i++)
	{
		if (accumulator[i] == '0')
		{
			store[operand][i] = 0;
			//store[currentInstructionDecimal][i] = 0;
		}
		else
		{
			store[operand][i] = 1;
			//store[currentInstructionDecimal][i] = 1;
		}
	}

	return SUCCESS;
}

/*
 * Takes the decimal version of the present instruction away from the decimal version of the
 * accumulator. The decimals are obtained through Dylan's binary conversion function.
 * The calculated decimal is then transformed back to binary through a handy to_string function
 * in the biset library
 */
int Baby::SUB()
{
	//int result = binaryToDecimal(accumulator) - binaryToDecimal(presentInstruction);

	//accumulator = bitset<32>(result).to_string();

	return SUCCESS;
}

/*
 * Returns true if the rightmost digit is 1, which usually indicates the number is negative
 */
int Baby::CMP()
{
	if (accumulator[31] == '1')
	{
		if (currentInstruction[0] == '0')
		{
			currentInstruction[0] = '1';
		}
		else
		{
			for (unsigned int i=0; i<currentInstruction.length(); i++)
			{
				if (currentInstruction[i] == '0')
				{
					currentInstruction[i] = '1';

					for (int j=i; j>-0; j--)
					{
						currentInstruction[j-1] = '0';
					}

					break;
				}
			}
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
	cout << "Displaying empty store..." << endl;
	displayStore();

	cout << "Testing STO function..." << endl;

	cout << "Output of first line of store is " << readLineFromStore(0) << endl;
	cout << "Operand = " << getOperand(0) << endl;
	cout << "Opcode = " << getOpcode(0) << endl;

	cout << endl << "Changing first line of store..." << endl;

	accumulator = "00111001011111010010001000010101";	//Random value of the accumulator
	if (STO(0) != SUCCESS)
	{
		cout << "The STO function failed!" << endl;
		return FAIL;
	}

	cout << endl << "STORE AFTER STO OPERATION:" << endl;
	displayStore();

	cout << endl << "Output of first line of store is " << readLineFromStore(0) << endl;
	cout << "Operand = " << getOperand(0) << endl;
	cout << "Opcode = " << getOpcode(0) << endl << endl;



	cout << "Testing CMP function..." << endl;
	currentInstruction = "11100000000000000000000000000000";
	accumulator = "11001100000101000000000010101110";

	cout << "Testing CMP with positive accumulator" << endl;
	cout << "Is accumulator negative?" << endl;
	cout << "Current instruction register before CMP check:" << currentInstruction << endl;
	cout << "Performing CMP operation..." << endl;

	if (CMP() == FAIL)
	{
		cout << "Operation failed!" << endl;
		return FAIL;
	}

	cout << "Current instruction register after CMP check (increments if negative):" << currentInstruction << endl;

	currentInstruction = "10000010000011000000011110000000";
	accumulator = "11001100000101000000000010101111";

	cout << "Testing with negative number in accumulator" << endl;
	cout << "Is accumulator negative?" << endl;
	cout << "Current instruction register before CMP check:" << currentInstruction << endl;
	cout << "Performing CMP operation..." << endl;

	if (CMP() == FAIL)
	{
		cout << "Operation failed!" << endl;
		return FAIL;
	}

	cout << "Current instruction register after CMP check (increments if negative):" << currentInstruction << endl;
	cout << "CMP test complete!" << endl << endl;



	cout << "Testing JMP function..." << endl;
	cout << "Setting present instruction equal to 11010000000000000000000000000000 (13)" << endl;

	presentInstruction = "11010000000000000000000000000000";

	cout << "Current instruction register before JMP: " << currentInstruction << endl;

	if (JMP() == FAIL)
	{
		cout << "JMP failed!" << endl;
		return FAIL;
	}

	cout << "Current instruction register after JMP: " << currentInstruction << endl;
	cout << "JMP test complete!" << endl;



	return SUCCESS;
}
