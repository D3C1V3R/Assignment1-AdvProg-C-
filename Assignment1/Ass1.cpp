#include <iostream>
#include <fstream>
#include <String>
#include <sstream>

using namespace std;

const int MaxRecords = 200;
enum _Status { PT, FT };

struct Record {
	int unsigned ID;
	char lName[19] = { };
	char fName[19] = { };
	_Status Status;
	int Grade[4];
	char Subjects[4][11] = {}; //Change size to fit Subject length before submit
	int Result = 0;
};

Record School[MaxRecords] = {};

void Readfile() {
	cout << "Opening File" << endl;
	ifstream File("Students.txt");
	if (!File.is_open()) {
		cout << "Can't find data file!\n";
		exit;
	}
	else {

		//I should of done this differently and ASSUMED everything was in the correct position/order
		ifstream File("Students.txt");
		Record _Record;

		for (string line; getline(File, line); ) { // assume each 'loop' is a start of a new 'record'
			if (line.length() == 8 && stoi(line) >= 1) { //Assume Student ID
				_Record = Record();
				cout << endl << "Found student ID" << line << endl;
				_Record.ID = stoi(line);
			}
			else if (!_Record.lName[0]) { //Assume second and third output from string is fname & lname
				strcpy_s(_Record.lName, line.c_str());
				cout << "Found student lname " << _Record.lName << endl;
			}
			else if (!_Record.fName[0]) { //Assume second and third output from string is fname & lname
				strcpy_s(_Record.fName, line.c_str());
				cout << "Found student fname " << _Record.fName << endl;
			}
			else if (line == "PT" || line == "FT") { //Asume fourth output is Status
				if (line == "PT") {
					_Record.Status = PT;
				}
				else {
					_Record.Status = FT;
				}
				cout << "Found student Status " << _Record.Status << endl;
			}
			else if (line.find(" ") && _Record.fName[0] != '\0') { //Assume 5th - 8th subject(s)
				istringstream iss(line);
				string temptoken;
				for (int i = 0; i <= 4; i++) {
					if (_Record.Subjects[i][0] != '\0') {	//check if spot is available
						continue;
					} else {
						while (getline(iss, temptoken, ' ')) { //for each whitespace 
							if (_Record.Subjects[i][0] == '\0') {	//do subject name first
								strcpy_s(_Record.Subjects[i], temptoken.c_str()); //Split result and StoreMark(_Record,value)
								}
							else {	//subject mark second
								_Record.Grade[i] = stoi(temptoken);							}
						}
						cout << "Found Subject " << _Record.Subjects[i] << " with grade " << _Record.Grade[i] << endl;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i <= MaxRecords; i++) {
		//if (School[i] == new Recor) {
		cout << School[i].fName << endl;
		//}
	}


}
void StoreMark(Record _Record, int _Value) {

}
	
	//File.close();
void ShowRecords() {

}
void AddRecord() {

}
void SearchData() {

}