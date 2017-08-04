/*
	Author: Alesha Morovits
	Purpose: create a form that allows a user to view data, editdata, add data, and save their password datain an encoded format.
	*/


#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 30;
const int BUFFER_SIZE = 200;

struct dataRow {
	string site, user, pass, notes;
	string code;
};

string inFileName; //name of inputfile	
string outFileName;
ifstream pathStream;
ofstream outFile;
char inputChar;
int extPosition(1), count = 0, lineNum;

void displayVector(vector<dataRow>& inputData);
void viewLineData(vector<dataRow>& inputData, int lineNum);
void addNewRow(vector<dataRow>& inputData, int& lastRowNum, string site, string user, string pass, string notes);
void editLineData(vector<dataRow>& inputData, int& lineNum, string site, string user, string pass, string notes);
void saveToFile(string outFile, vector<dataRow>& inputData, int codein);

string encodeLev1(string rawData);
string decodeLev1(string rawData);
string encodeLev2(string rawData);
string decodeLev2(string rawData);
string encodeLev3(string rawData);
string decodeLev3(string rawData);
int getEnCode(string encoding);
void warning();
void cleanBuffer();
void displayMenu();
int exit();
vector<dataRow> inputData;
dataRow descripLine;
string rowDescripin, userin, passin, notesin, sitein;
string codein, errorMsg;
int lastRow, code;
const int ALT_ONE = -3;
const int ALT_TWO = 5;
const int ALT_THREE = 3;
const int ALT_FOUR = 4;
char userCode;
string encodedString[MAX_SIZE];
string userInputRow;
int main()
{

	//add a .txt extension to the file if the user didn't provide an extension
	if (inFileName.size() > 4)
		// If there's a valid extension, it will be in the last 4 positions of the string; Adjust by 1 for 0 offset
		extPosition = inFileName.size() - 4;
	//int ext = inFileName.find_last_of(".txt");
	if (!(inFileName.find_last_of(".") == extPosition))
	{
		inFileName += ".txt";
	}
	//opening the input file and checking for failure
	cout << "\nPlease enter the filename of input file: ";
	cin >> inFileName;
	cleanBuffer();
	pathStream.open(inFileName.c_str());

	if (pathStream.fail())
	{
		cerr << inFileName << " failed to open.\n";
		system("pause");
		exit(1);
	}
	else
	{
		cout << "startup success" << endl;
	}
	//putting the txt file into the inputdata vector, as semicolons seperate each thing 
	getline(pathStream, codein, ';');
	code = getEnCode(codein);
	while (!pathStream.eof())
	{
		descripLine.site = "";
		getline(pathStream, sitein, ';');
		if (!(pathStream.eof()))
		{
			for (int lcv = 0; lcv < sitein.length(); lcv++)
			{
				//cout << sitein<<endl;
				if (sitein[lcv] != '\n')
				{
					descripLine.site += sitein[lcv];
				}
				//cout << descripLine.site<<endl;
			}
			descripLine.user = "";
			getline(pathStream, userin, ';');
			for (int lcv = 0; lcv < userin.length(); lcv++)
			{
				if (userin[lcv] != '\n')
				{
					descripLine.user += userin[lcv];
				}
			}
			descripLine.pass = "";
			getline(pathStream, passin, ';');
			for (int lcv = 0; lcv < passin.length(); lcv++)
			{
				if (passin[lcv] != '\n')
				{
					descripLine.pass += passin[lcv];
				}
			}
			descripLine.notes = "";
			getline(pathStream, notesin, ';');
			for (int lcv = 0; lcv < notesin.length(); lcv++)
			{
				if (notesin[lcv] != '\n')
				{
					descripLine.notes += notesin[lcv];
				}
			}

			inputData.push_back(descripLine);
		}
	}
	if (code == 0)
	{
		for (int lcv = 0; lcv < sitein.length(); lcv++)
		{
			//cout << sitein<<endl;
			if (sitein[lcv] != ';')
			{
				descripLine.site += sitein[lcv];
			}
			//cout << descripLine.site<<endl;
		}
		//descripLine.user = "";
		getline(pathStream, userin, ';');
		for (int lcv = 0; lcv < userin.length(); lcv++)
		{
			if (userin[lcv] != ';')
			{
				descripLine.user += userin[lcv];
			}
		}
		descripLine.pass = "";
		getline(pathStream, passin, ';');
		for (int lcv = 0; lcv < passin.length(); lcv++)
		{
			if (passin[lcv] != ';')
			{
				descripLine.pass += passin[lcv];
			}
		}
		descripLine.notes = "";
		getline(pathStream, notesin, ';');
		for (int lcv = 0; lcv < notesin.length(); lcv++)
		{
			if (notesin[lcv] != ';')
			{
				descripLine.notes += notesin[lcv];
			}
		}

		if (code == 1)
		{

			for (int lcv = 0; lcv < inputData.size(); lcv++)
			{
				inputData[lcv].site = decodeLev1(descripLine.site);
				//outFile << decodeLev1(descripLine.site) << ';';

				inputData[lcv].user = decodeLev1(descripLine.user);
				//outFile << decodeLev1(descripLine.user) << ';';

				inputData[lcv].pass = decodeLev1(descripLine.pass);
				//outFile << decodeLev1(descripLine.pass) << ';';

				inputData[lcv].notes = decodeLev1(descripLine.notes);
				//outFile << decodeLev1(descripLine.notes) << ';' << endl;

			}
		}
		else if (code == 2)
		{

			for (int lcv = 0; lcv < inputData.size(); lcv++)
			{
				descripLine.site = decodeLev2(inputData[lcv].site);

				descripLine.user = decodeLev2(inputData[lcv].user);

				descripLine.pass = decodeLev2(inputData[lcv].pass);

				descripLine.notes = decodeLev2(inputData[lcv].notes);
			}
		}
		else if (code == 3)
		{
			for (int lcv = 0; lcv < inputData.size(); lcv++)
			{
				descripLine.site = decodeLev3(inputData[lcv].site);

				descripLine.user = decodeLev3(inputData[lcv].user);

				descripLine.pass = decodeLev3(inputData[lcv].pass);

				descripLine.notes = decodeLev3(inputData[lcv].notes);
			}
		}

		pathStream.close();
		//call the menu and display the first field of the vector for user connvience
		displayVector(inputData);
		displayMenu();
		//do stuff according to user input of input char
		while (cin){
			cin >> inputChar;
			inputChar = toupper(inputChar);
			cleanBuffer();
			//Adjust output based on inputCHar
			if (inputChar == 'D')  // Display line descriptions
			{
				displayVector(inputData);
			}
			else if (inputChar == 'V')  //View line data
			{
				cout << "Enter line number you wish to view: ";
				cin >> lineNum;
				cleanBuffer();
				viewLineData(inputData, lineNum);//THIS WORKS but it doesnt show the newly added rows
			}
			else if (inputChar == 'E')  //Edit line Data
			{
				warning();

				cout << "Enter line number you wish to edit: ";
				cin >> lineNum;
				cleanBuffer();

				cout << "Enter a line description: ";
				(getline(cin, rowDescripin));
				cleanBuffer();

				cout << "Enter a line username: ";
				(getline(cin, userin));
				cleanBuffer();

				cout << "Enter a line password: ";
				(getline(cin, passin));
				cleanBuffer();

				cout << "Enter notes: ";
				(getline(cin, notesin));
				cleanBuffer();

				editLineData(inputData, lineNum, rowDescripin, userin, passin, notesin);
			}
			else if (inputChar == 'A')  //Add line data
			{
				warning();//works
				cout << endl;
				lastRow = inputData.size();
				//user enters info according to fields
				cout << "Enter a line description: ";
				(getline(cin, rowDescripin));
				cleanBuffer();
				cout << "Enter a line username: ";
				(getline(cin, userin));
				cleanBuffer();

				cout << "Enter a line password: ";
				(getline(cin, passin));
				cleanBuffer();

				cout << "Enter notes: ";
				(getline(cin, notesin));
				cleanBuffer();

				inputData.push_back(descripLine);

				addNewRow(inputData, lastRow, rowDescripin, userin, passin, notesin);
			}
			else if (inputChar == 'S')  //Save and encode file
			{
				int encodeNum;

				cout << "Enter encoding level (0, 1, 2, or 3) then the filename:";
				cin >> encodeNum;
				cin >> outFileName;
				cleanBuffer();
				outFile.open(outFileName.c_str());
				if (encodeNum == 0)
				{

					outFile << "E0;" << endl;
					for (int lcv = 0; lcv < inputData.size(); lcv++)
					{
						descripLine.site = inputData[lcv].site;
						inputData[lcv].site = descripLine.site;
						outFile << descripLine.site << ';';

						descripLine.user = inputData[lcv].user;
						outFile << descripLine.user << ';';

						descripLine.pass = inputData[lcv].pass;
						outFile << descripLine.pass << ';';

						descripLine.notes = inputData[lcv].notes;
						outFile << descripLine.notes << ';' << endl;
					}
				}
				else if (encodeNum == 1)
				{
					outFile << "E1;" << endl;


					for (int lcv = 0; lcv < inputData.size(); lcv++)
					{
						descripLine.site = inputData[lcv].site;
						inputData[lcv].site = encodeLev1(descripLine.site);
						outFile << encodeLev1(descripLine.site) << ';';

						descripLine.user = inputData[lcv].user;
						outFile << encodeLev1(descripLine.user) << ';';

						descripLine.pass = inputData[lcv].pass;
						outFile << encodeLev1(descripLine.pass) << ';';

						descripLine.notes = inputData[lcv].notes;
						outFile << encodeLev1(descripLine.notes) << ';' << endl;
					}
					outFile.flush();
				}
				else if (encodeNum == 2)
				{
					outFile << "E2;" << endl;

					for (int lcv = 0; lcv < inputData.size(); lcv++)
					{
						descripLine.site = inputData[lcv].site;
						outFile << encodeLev2(descripLine.site) << ';';

						descripLine.user = inputData[lcv].user;
						outFile << encodeLev2(descripLine.user) << ';';

						descripLine.pass = inputData[lcv].pass;
						outFile << encodeLev2(descripLine.pass) << ';';

						descripLine.notes = inputData[lcv].notes;
						outFile << encodeLev2(descripLine.notes) << ';' << endl;
					}
					outFile.flush();
				}



				else if (encodeNum == 3)
				{
					outFile << "E3;" << endl;
					for (int lcv = 0; lcv < inputData.size(); lcv++)
					{
						descripLine.site = inputData[lcv].site;
						outFile << encodeLev3(descripLine.site) << ';';

						descripLine.user = inputData[lcv].user;
						outFile << encodeLev3(descripLine.user) << ';';

						descripLine.pass = inputData[lcv].pass;
						outFile << encodeLev3(descripLine.pass) << ';';

						descripLine.notes = inputData[lcv].notes;
						outFile << encodeLev3(descripLine.notes) << ';' << endl;
					}
					outFile.flush();
				}


				outFile.close();
				displayMenu();

			}

			else if (inputChar == 'X')  //exit program
			{
				exit(0);
			}
			else if ((inputChar != 'D') || (inputChar != 'V') || (inputChar != 'E')
				|| (inputChar != 'A') || (inputChar != 'X'))
			{
				displayMenu();
			}

		}

		return 0;
	}
}
	void displayMenu()
	{
		cout << endl << "			AVAILABLE OPTIONS			" << endl << endl <<
			"D - DISPLAY LINE DESCRIPTIONS" << endl <<
			"V - VIEW LINE DATA" << endl <<
			"E - EDIT LINE DATA" << endl <<
			"A - ADD LINE DATA" << endl <<
			"S - SAVE AND ENCODE FILE" << endl <<
			"X - EXIT PROGRAM" << endl;

	}
	void viewLineData(vector<dataRow>& inputData, int lineNum)
	{
		cout << setw(2) << fixed;

		cout << "Row Desc: "
			<< inputData[lineNum].site << endl;
		cout << "Row User: ";
		cout << inputData[lineNum].user << endl;
		cout << "Row Pass: ";
		cout << inputData[lineNum].pass << endl;
		cout << "Row Notes: ";
		cout << inputData[lineNum].notes << endl;

	}
	void displayVector(vector<dataRow>& inputData)
	{
		//cout << fixed << setprecision(3);
		string site;

		site.clear();
		for (unsigned int i = 0; i < inputData.size() - 1; i++)
		{
			//cout << inputData[i].site;
			cout << i << setw(20) << fixed << inputData[i].site << endl;

		}

	}
	void addNewRow(vector<dataRow>& inputData, int& lastRowNum, string site, string user, string pass, string notes)
	{
		char ans;
		cout << "You have entered:" << endl << site << endl << user << endl << pass << endl << notes;
		cout << endl << "Is this the data you wish to add (Y/N)? ";
		cin >> ans;
		ans = toupper(ans);
		cleanBuffer();
		cout << endl;
		if (ans == 'Y')
		{
			dataRow tempRow = { site, user, pass, notes };
			inputData.push_back(tempRow);
			cout << inputData.size();
			for (unsigned int i = 0; i < inputData.size(); i++)
			{
				cout << endl << inputData[i].site << endl << inputData[i].user << endl << inputData[i].pass << endl << inputData[i].notes << endl;
			}
		}
		else if (ans == 'N')
		{
			cout << "Line was not changed." << endl;
			displayMenu();
		}
	}
	void editLineData(vector<dataRow>& inputData, int& lineNum, string sitein, string userin, string passin, string notesin)
	{
		char ans;
		lineNum - 1;


		cout << "You have entered:" << endl;
		cout << sitein << endl;
		cout << userin << endl;
		cout << passin << endl;
		cout << notesin << endl;

		cout << endl << "Is this the data you wish to edit (Y/N)? ";
		cin >> ans;
		ans = toupper(ans);
		cleanBuffer();
		if (ans == 'Y')
		{
			cout << "Line was updated." << endl;
			inputData[lineNum].site = sitein;
			inputData[lineNum].user = userin;
			inputData[lineNum].pass = passin;
			inputData[lineNum].notes = notesin;
		}
		else if (ans == 'N')
		{
			cout << "Line was not changed." << endl;
			displayMenu();
		}
	}
	void warning()
	{
		cout << "WARNING: You cannot use semi-colons in these fields. Any semi-colons entered will be removed." << endl;
		return;
	}
	void cleanBuffer()
	{
		cin.clear();
		cin.ignore(BUFFER_SIZE, '\n');
	}
	string encodeLev1(string rawData)
	{
		string encodedDataAltOne;
		string encodedDataAltTwo;
		for (int i = 0; i < rawData.length(); i++)//go through each "raw" string 
		{
			encodedDataAltOne += char(int(rawData[i]) + ALT_ONE);//char by char, cast to the ascii value, then apply first alteration
		}                                                        //this will push back the ascii value by -3 (ALT_ONE)
		//then create a string variable called encodedDataAltOne	
		for (int i = 0; i < encodedDataAltOne.length(); i++)//now go through encodedDataAltOne, then apply the second alteration
		{
			if (i % 2 == 0)//if the position is even, allow the value to stay as the first alteration, but build onto a new variable
			{
				encodedDataAltTwo += char(int(encodedDataAltOne[i])); //+ ALT_ONE);//char by char push back the ascii value by-3
			}
			if (!(i % 2 == 0))//if the position is odd, apply the second alteration. This will take the encodedDataAltOne string and then apply the second alteration
			{                 //the second alteration will take the encodedDataAlt one values in the odd position and push it forward 5 ascii values
				encodedDataAltTwo += char(int(encodedDataAltOne[i]) + ALT_TWO);
			}
		}
		return encodedDataAltTwo;
	}
	string decodeLev1(string rawData)
	{
		string encodedDataAltOne;
		string encodedDataAltTwo;
		for (int i = 0; i < rawData.length(); i++)//go through each "raw" string 
		{
			encodedDataAltOne += char(int(rawData[i]) - ALT_ONE);//char by char, cast to the ascii value, then apply first alteration
		}                                                        //this will push back the ascii value by -3 (ALT_ONE)
		//then create a string variable called encodedDataAltOne	
		for (int i = 0; i < encodedDataAltOne.length(); i++)//now go through encodedDataAltOne, then apply the second alteration
		{
			if (i % 2 == 0)//if the position is even, allow the value to stay as the first alteration, but build onto a new variable
			{
				encodedDataAltTwo += char(int(encodedDataAltOne[i]));// - ALT_ONE);//char by char push back the ascii value by-3
			}
			if (!(i % 2 == 0))//if the position is even, apply the second alteration. This will take the encodedDataAltOne string and then apply the second alteration
			{                 //the second alteration will take the encodedDataAlt one values in the odd position and push it forward 5 ascii values
				encodedDataAltTwo += char(int(encodedDataAltOne[i]) - ALT_TWO);
			}
		}
		//cout << "\ndecoded string-\n" << encodedDataAltTwo;
		return encodedDataAltTwo;
	}
	string encodeLev2(string rawData)
	{
		string encodedDataAltOne;
		string encodedDataAltTwo;
		string encodedDataAltThree;
		string buildstr;
		string tempVar, tempvar;
		for (int i = 0; i < rawData.length(); i++)//go through each "raw" string 
		{
			encodedDataAltOne += char(int(rawData[i]) + ALT_FOUR);//char by char, cast to the ascii value, then apply first alteration
		}                                                        //this will push back the ascii value by -3 (ALT_ONE)
		//then create a string variable called encodedDataAltOne

		for (int i = 0; i < encodedDataAltOne.length(); i++)//now go through encodedDataAltOne, then apply the second alteration
		{
			char altVal;

			if (i % 3 == 0)//if the position is even, allow the value to stay as the first alteration, but build onto a new variable
			{
				altVal = char(int(encodedDataAltOne[i]) + ALT_THREE);

				if (altVal == ';')
					encodedDataAltTwo += '\1';
				else
					encodedDataAltTwo += altVal;
			}
			if (!(i % 3 == 0))
			{
				altVal = char(int(encodedDataAltOne[i]));
				if (altVal == ';')
					encodedDataAltTwo += '\1';
				else
					encodedDataAltTwo += altVal;
			}
		}
		{
			tempVar = encodedDataAltTwo.substr(0, 1);
			tempvar = encodedDataAltTwo.substr(encodedDataAltTwo.length() - 1, encodedDataAltTwo.length());

			encodedDataAltThree = encodedDataAltTwo.substr(1, encodedDataAltTwo.length() - 2);
			buildstr = tempvar + encodedDataAltThree + tempVar;
		}

		return buildstr;
	
}
	
	string decodeLev2(string rawData)
	{
		string encodedDataAltOne;
		string encodedDataAltTwo;
		string encodedDataAltThree;
		string buildstr;
		string tempVar, tempvar;

		for (int i = 0; i < rawData.length(); i++)//go through each "raw" string 
		{
			if (char(int(rawData[i])) == '\1')
				rawData[i] = ';';

			encodedDataAltOne += char(int(rawData[i]) - ALT_FOUR);//char by char, cast to the ascii value, then apply first alteration
		}                                                        //this will push back the ascii value by -3 (ALT_ONE)
		//then create a string variable called encodedDataAltOne	
		for (int i = 0; i < encodedDataAltOne.length(); i++)//now go through encodedDataAltOne, then apply the second alteration
		{
			if (i % 3 == 0)//if the position is even, allow the value to stay as the first alteration, but build onto a new variable
			{
				encodedDataAltTwo += char(int(encodedDataAltOne[i]) - ALT_THREE);//char by char push back the ascii value by-3
			}
			if (!(i % 3 == 0))
			{
				encodedDataAltTwo += char(int(encodedDataAltOne[i]));
			}
		}
		{
			tempVar = encodedDataAltTwo.substr(0, 1);
			tempvar = encodedDataAltTwo.substr(encodedDataAltTwo.length() - 1, encodedDataAltTwo.length());

			encodedDataAltThree = encodedDataAltTwo.substr(1, encodedDataAltTwo.length() - 2);
			buildstr = tempvar + encodedDataAltThree + tempVar;
		}
		
		return buildstr;
	}
	string encodeLev3(string rawData)
	{
		string encodedDataAltFive;
		string var;
		var = encodeLev1(rawData);
		encodedDataAltFive = encodeLev2(var);
		return encodedDataAltFive;
	}
	string decodeLev3(string rawData)
	{

		string encodedDataAltFive;
		string var;
		var = decodeLev1(rawData);
		encodedDataAltFive = decodeLev2(var);
		return encodedDataAltFive;
	}
	int getEnCode(string encode)
	{
		int code = 0;
		if (encode == "E0")
		{
			code = 0;
		}
		else if (encode == "E1")
		{
			code = 1;
		}
		else if (encode == "E2")
		{
			code = 2;
		}
		else if (encode == "E3")
		{
			code = 3;
		}
		return code;
	}













	