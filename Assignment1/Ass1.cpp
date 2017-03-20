/****************************************************
*		main.cpp - CSCI251 Ass1 - Atm2017				
*		Function definitions for student database
*		Christopher Aldous, 5096054, 21/3/17		    
****************************************************/

#include <iostream>
#include <fstream>
#include <String>
#include <sstream>
#include <algorithm>

using namespace std;

const int MaxRecords = 100;
int CurrentRecords = 0;
enum _Status { PT, FT };
char *StatusTypes[] = { "PT","FT" };

struct Record {
	int unsigned ID=0;
	char lName[19] = {};
	char fName[19] = {};
	_Status Status;
	int Grade[4] = {};	
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
		int _count=0;
		for (string line; getline(File, line); ) { // assume each 'loop' is a start of a new 'record'
			if (line.length() == 8 && stoi(line) >= 1) { //Assume Student ID, terrible way to detect if number
				if (_Record.ID && _Record.ID!=0) { //We assume the ID is filled
					School[_count] = _Record;
					_count++;
				}
				_Record = Record();
				_Record.ID = stoi(line);
			}
			else if (!_Record.lName[0]) { //Assume second and third output from string is fname & lname
				strcpy_s(_Record.lName, line.c_str());
			}
			else if (!_Record.fName[0]) { //Assume second and third output from string is fname & lname
				strcpy_s(_Record.fName, line.c_str());
			}
			else if (line == "PT" || line == "FT") { //Asume fourth output is Status
				if (line == "PT") {
					_Record.Status = PT;
				}
				else {
					_Record.Status = FT;
				}
			}
			else if (line.find(" ") && _Record.fName[0] != '\0') { //Assume 5th - 8th subject(s)
				istringstream iss(line);
				string temptoken;
				for (int i = 0; i <= 4; i++) {
					if (_Record.Subjects[i][0] != '\0') {	//check if spot is available
						continue;
					}
					else {
						while (getline(iss, temptoken, ' ')) { //for each whitespace 
							if (_Record.Subjects[i][0] == '\0') {	//do subject name first
								strcpy_s(_Record.Subjects[i], temptoken.c_str()); //Split result into tokens
							}
							else {	//subject mark second
								_Record.Grade[i] = stoi(temptoken);
							}
						}
						break;
					}
				}
			}
		}
		File.close();
		School[_count++] = _Record; //needed to add last element to array (bad coder).
	}

	int _count = 0;
	for (int i = 0; i <= MaxRecords; i++) {
		
		if (School[i].ID != 0) {
			_count++;		}
	}
	CurrentRecords = _count;
	cout << "There are "<< CurrentRecords <<" records in the student records databas" << endl;
}

void PrintRecord(int index) {
	cout << "Student No \t" << School[index].ID << endl;
	cout << "First Name \t" << School[index].fName << endl;
	cout << "Family Name \t" << School[index].lName << endl;
	cout <<"Status \t\t" << StatusTypes[School[index].Status] << endl;
	string _tmp = "";
	string _tmpG = "";
	for (int j = 0; j <= 3; j++) { //check all indexs
		if (School[index].Subjects[j]) {
			_tmp += "\t" + string(School[index].Subjects[j]);
			if (School[index].Grade[j] != 0){_tmpG += "\t" + to_string(School[index].Grade[j]); }
			
		}
	}
	cout << "Subjects " << _tmp << endl;
	cout << "Results " << _tmpG << endl;
}
void ShowRecords() {
	for (int i = 0; i <= MaxRecords; i++) {
		PrintRecord(i);
		cout << "Display next record(y / n) :";

		string input;
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), tolower);	//transform input into lowercase
		cout << endl;
		do {
			if (input == "y" && input.length() == 1) {
				break;
			}
			else if (input == "n" && input.length() == 1) {
				goto exit_loop; //break both loops
			}
			else {
				cin >> input;
				transform(input.begin(), input.end(), input.begin(), tolower);
			}

		} while (input != "y" || input != "n");

	}
	exit_loop: ;

}
void WriteData() {
	ofstream  File;
	File.open("Students.txt");
	for (int i = 0; i < CurrentRecords; i++) {
		File << School[i].ID << endl;
		File << School[i].fName << endl;
		File << School[i].lName << endl;
		File << StatusTypes[School[i].Status] << endl;
		string _tmp = "";
		string _tmpG = "";
		int count = (School[i].Status + 1) * 2;
		for (int j = 0; j < count; j++) { //check all indexs
			if (School[i].Subjects[j]) {
				File << School[i].Subjects[j] << " " << School[i].Grade[j] << endl;
			}
		}
	}
	
	cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "	"<<CurrentRecords<<" records are in the database" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}
void AddRecord() {
cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
cout << "\t  Add Record to Database " << endl;
cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;

Record _tmp;
for (;;) { //Student Number Input and validation
	cout << "Student Number: ";
	if (cin >> _tmp.ID && to_string(_tmp.ID).length() == 8) {
		break;
	}
	else {
		cout << "Please enter a valid 8 digit integer" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
};
for (;;) {// Student First name 
	cout << "Student First Name: ";
	string _tmpName = "";
	if (cin >> _tmpName) {
		if (_tmpName.npos == _tmpName.find_first_of("0123456789") && _tmpName.length() <= 20) { //fits into char [19] and doesn't contain a number
			char _tmpUpper = toupper(_tmpName.at(0));	//Should've just got input as char array not string
			char _combined[19] = {};
			strcpy_s(_combined, _tmpName.c_str());
			_combined[0] = _tmpUpper;
			strcpy_s(_tmp.fName, _combined);
			break;
		}
		goto falseflag;
	}
	else {
	falseflag:;
		cout << "Please enter a valid 20 Character name" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
};
for (;;) {// Student  Last name 
	cout << "Student Last Name: ";
	string _tmpName = "";
	if (cin >> _tmpName) {
		if (_tmpName.npos == _tmpName.find_first_of("0123456789") && _tmpName.length() <= 20) { //fits into char [19] and doesn't contain a number

			char _tmpUpper = toupper(_tmpName.at(0));	//Should've just got input as char array not string
			char _combined[19] = {};
			strcpy_s(_combined, _tmpName.c_str());
			_combined[0] = _tmpUpper;
			strcpy_s(_tmp.lName, _combined);

			break;
		}
		goto falseflag2;
	}
	else {
	falseflag2:;
		cout << "Please enter a valid 20 Character name" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
};

for (;;) {	//Student status
	cout << "Student's Status (FT/PT): ";
	string _tmpName = "";
	if (cin >> _tmpName) {
		transform(_tmpName.begin(), _tmpName.end(), _tmpName.begin(), ::toupper);		//Makes input Uppercase
		if (_tmpName == "PT") {
			_tmp.Status = PT;
			break;
		}
		else if (_tmpName == "FT") {
			_tmp.Status = FT;
			break;
		}
		cout << "Please enter a correct Status (PT / FT)" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

}


int current = 0;
cout << "Enter " << (_tmp.Status + 1) * 2 << " Subjects and the Results: " << endl;
do {
	string _tmpSubject = "";
	if (cin >> _tmpSubject) {
		istringstream iss(_tmpSubject);
		string temptoken;
		try {
			while (getline(iss, temptoken, ' ')) {											//for each whitespace 				
				if (temptoken.length() == 7) {												//Assume subject code
					transform(temptoken.begin(), temptoken.end(), temptoken.begin(), toupper);
					strcpy_s(_tmp.Subjects[current], temptoken.c_str());
					continue;																//prevent exception of testing subject name to int
				}
				if (atoi(temptoken.c_str()) >= 0 && atoi(temptoken.c_str()) <= 100) {		//Assume grade
					_tmp.Grade[current] = stoi(temptoken);
						current++;
				}
				}
			} catch (exception) {
				cout << "Please enter a valid Subject and Grade" << endl;
			}
		}
	} while (current != (_tmp.Status+1)*2);		//PT = 2 , FT = 4
	
	School[CurrentRecords] = _tmp;
	CurrentRecords += 1;

	WriteData();
}
void SearchData() {

	string input;
	cout << "Enter Student Number:";
	cin >> input;
	bool check = false;
	for (int i = 0; i <= CurrentRecords; i++) {
		if (stoi(input) == School[i].ID){			//Lets just go with the whole 'assume everything is correct' style. :)
			PrintRecord(i);
			check = true;
		}
	}
	if (check == false) {
		cout << "Unable to find record requested" << endl;
	}
}

