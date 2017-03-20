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
	CurrentRecords = _count;
	cout << "We found " << _count << " records." << endl;


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
	cout << "Display next record(y / n) :";
}

void ShowRecords() {
	for (int i = 0; i <= MaxRecords; i++) {
		PrintRecord(i);

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

void AddRecord() {
	cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "\t  Add Record to Database " << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	//Check for
	//		Std Number = 8 digits		Done
	//		Name = Formatted & 20 Char	Done
	//		Status	FT = 4				Done
	//				PT = 2				Done
	//		Grade = 0-100
	//		Subject name = 7char

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
				strcpy_s(_tmp.fName, _tmpName.c_str());
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
				strcpy_s(_tmp.lName, _tmpName.c_str());
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
	_tmp.Status = FT;
	cout << "Enter 4 Subjects and the Results: " << endl;
	do {	
		string _tmpSubject = "";
		if (cin >> _tmpSubject) {
			istringstream iss(_tmpSubject);
			string temptoken;
			try {
				while (getline(iss, temptoken, ' ')) {	//for each whitespace 				
					if (temptoken.length() == 7) {		//Assume subject code
						strcpy_s(_tmp.Subjects[current], temptoken.c_str());
						continue; //prevent exception of testing subject name to int
					}
					if (atoi(temptoken.c_str()) >= 0 && atoi(temptoken.c_str()) <= 100) {						//Assume grade
						_tmp.Grade[current] = stoi(temptoken);
						current++;
					}
				}
			}
			catch (exception) {
				cout << "Please enter a valid Subject and Grade" << endl;
			}
		}
	} while (current != (_tmp.Status+1)*2);		//PT = 2 , FT = 4
}


void WriteData() {
	ifstream File;
	File.open("example.txt");
	for (int i; i <= CurrentRecords; i++) {
		File << "Student No \t";//(School[i].ID) << endl;
		File << "First Name \t" << School[i].fName << endl;
		File << "Family Name \t" << School[i].lName << endl;
		File << "Status \t\t" << StatusTypes[School[i].Status] << endl;
		string _tmp = "";
		string _tmpG = "";
		for (int j = 0; j <= 3; j++) { //check all indexs
			if (School[index].Subjects[j]) {
				_tmp += "\t" + string(School[index].Subjects[j]);
				if (School[index].Grade[j] != 0) { _tmpG += "\t" + to_string(School[index].Grade[j]); }

			}
		}
		File << "Subjects " << _tmp << endl;
		File << "Results " << _tmpG << endl;
		File << "Display next record(y / n) :";
	}
}
void SearchData() {
	//create function to display record
	//implment into ShowRecord()
}

