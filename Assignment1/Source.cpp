#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include "SourceH.h"
using namespace std;

char MainMenu();

int main() {


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