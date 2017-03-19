#include <iostream>
#include <fstream>
#include <String>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

const int MaxRecords = 50;
enum _Status { PT, FT };

struct Record {
	int unsigned ID=0;
	char lName[19] = {};
	char fName[19] = {};
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
		int _count=0;
		for (string line; getline(File, line); ) { // assume each 'loop' is a start of a new 'record'
			if (line.length() == 8 && stoi(line) >= 1) { //Assume Student ID, terrible way to detect if number
				if (_Record.ID && _Record.ID!=0) { //We assume the ID is filled
					School[_count] = _Record;
					_count++;
					cout << "Stored ID" << endl;
				}
				_Record = Record();
				cout << endl << "Found student ID " << line << endl;
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
						cout << "Found Subject " << _Record.Subjects[i] << " with grade " << _Record.Grade[i] << endl;
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
			_count++;
			cout << _count << "_" << School[i].fName << endl;
		}
	}

	cout << "We found " << _count << " records." << endl;


}

void ShowRecords() {
	for (int i = 0; i <= MaxRecords; i++) {
		cout << "Student No \t" << School[i].ID << endl; 
		cout << "First Name \t" << School[i].fName << endl;
		cout << "Family Name \t" << School[i].lName << endl;
		cout << "Status \t" << School[i].Status << endl;
		string _tmp="";
		string _tmpG="";
		for (int j = 0; j <= 3; j++) { //check all indexs
			if (School[i].Subjects[j]) {
				_tmp += "\t" + string(School[i].Subjects[j]);
				_tmpG += "\t" + to_string(School[i].Grade[j]);
			}
		}
		cout << "Subjects " << _tmp << endl;
		cout << "Results " << _tmpG << endl;
		cout << "Display next record(y / n) :";


		string input;
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), tolower);	//transform input into lowercase

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
void AddRecord() {
	 
}
void SearchData() {
	//create function to display record
}