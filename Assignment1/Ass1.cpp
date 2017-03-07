#include <iostream>
#include <fstream>
#include <String>

using namespace std;

const int MaxRecords = 200;

struct Record {
	int unsigned ID;
	char lName[19];
	char fName[19];
	bool Status; //not sure what type to use  PT/FT
	char Subjects[3][6];
	enum Result{low=0,max=100};
};

Record School[MaxRecords];

void Readfile() {
	cout << "Opening File" << endl;
	ifstream File("Students.txt");
	if (!File.is_open()) {
		cout << "Can't find data file!\n";
		exit;
	} else if (!File){
		cout << "File not found" << endl;
	}
	else {
		ifstream File("Students.txt");

		for (string line; getline(File, line); )
		{
			cout << line << endl;
		}
	}
}
	
	//File.close();
void ShowRecords() {

}
void AddRecord() {

}
void SearchData() {

}