/****************************************************
*    main.cpp - CSCI251 Ass1 - Atm2017				*
*    Contains main + UI for student DB program		*
*    Christopher Aldous, 5096054, 21/3/17		    *
****************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "SourceH.h"

using namespace std;

char MainMenu();

int main() {

	// Option for redirecting input from input.txt 
	// Use this when you demo your program to your 
	// tutor as explained on page 4 of the Ass1 specs.
	char RedirectInput[20];
	cout << "Redirect input? (y/n): ";
	cin.getline(RedirectInput, 20);
	if (RedirectInput[0] == 'y') { // then get input from input.txt...
		FILE *fp = freopen("input.txt", "r", stdin);
		if (fp == NULL) { cerr << "\"input.txt\" not found!\n"; exit(1); }
	}

	bool Exit = false;
	do {
		char Input = MainMenu();
		switch (Input) {
			case 'r':
				Readfile();
				break;
			case 'd':
				ShowRecords();
				break;
			case 'a':
				AddRecord();
				break;
			case 's':
				SearchData();
				break;
			case 'q':
				Exit = true;
				break;
			default :
				cerr << "Invalid request\n";
		}

	} while (!Exit);

	cout << "Thank you for using the student records database" << endl;
	if (RedirectInput[0] == 'y') fclose(stdin);    // close redirected input from input.txt
	return 0;

}


char MainMenu()
{
	cout << "*********************************" << endl;
	cout << "*    Student Records Database   *" << endl;
	cout << "*     (r)ead data file          *" << endl;
	cout << "*     (d)isplay records         *" << endl;
	cout << "*     (a)dd record to DB        *" << endl;
	cout << "*     (s)earch records          *" << endl;
	cout << "*     (q)uit                    *" << endl;
	cout << "*********************************" << endl;
	cout << "Command: ";
	
	char Cmd;
	cin >> Cmd;
	cin.ignore();
	Cmd = tolower(Cmd);
	return Cmd;
}
