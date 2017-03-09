#include <iostream>
#include <fstream>
#include <String>

using namespace std;

const int MaxRecords = 200;

struct Record {
	int unsigned ID;
	char lName[19] = { };
	char fName[19] = { };
	bool Status; //not sure what type to use  PT/FT //PT fase, FT true
	char Subjects[4][11] = {}; //Change size to fit Subject length
	enum Result{low=0,max=100};
};

Record School[MaxRecords];

void Readfile() {
	cout << "Opening File" << endl;
	ifstream File("Students.txt");
	if (!File.is_open()) {
		cout << "Can't find data file!\n";
		exit;
	}
	else {
		ifstream File("Students.txt");
		Record _Record;
		//memset(_Record.lName, 0, 19); //need to clear char array to check if empty// should probably find an alt method
		//memset(_Record.fName, 0, 19); //need to clear char array to check if empty// should probably find an alt method
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
					_Record.Status = false;
				}
				else {
					_Record.Status = true;
				}
				cout << "Found student Status " << _Record.Status << endl;
			}
			else if (line.find(" ") && _Record.fName[0] != '\0') { //Assume 5th - 8th subject(s)
				for (int i=0; i <= 4; i++) {
					if (_Record.Subjects[i][0]=='\0') {
						strcpy_s(_Record.Subjects[i], line.c_str()); //Split result and StoreMark(_Record,value);
						cout << "Found Subject[" << i << "] " << line << endl;
						break;
					}
				}
			}		
		}
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