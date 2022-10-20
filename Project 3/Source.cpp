#include <Python.h>
#include <iostream>
#include <fstream>
#define NOMINMAX
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void main()
{
	int option = 0;
	int frequency;
	string name;
	string item;
	
	//Creates a while loop to run the program until the user chose to exit by entering 4
	while (option != 4)
	{
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << endl;
		cout << "1: Display a list of all items and quantities purchased" << endl;
		cout << "2: Display number of times a specific item was purchased" << endl;
		cout << "3: Display a histogram of purchased items and quantities" << endl;
		cout << "4: Exit" << endl;
		cout << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Enter your selection as a number: 1, 2, 3, or 4" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << endl;

		//Get user input
		cin >> option;
		cout << endl;

		//Validate user input
		if (cin.fail() == true)
		{
			cout << "Invalid format for input. Please re-enter 1,2,3 or 4" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		else if (option == 1)
		{
			//Calls the funtion determineInventory from python to print items and quantities purchased 
			cout << "*********************************************************" << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~ TOTAL INVENTORY ~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "*********************************************************" << endl;
			cout << endl;
			CallProcedure("determineInventory");
			cout << endl;
		}

		else if (option == 2)
		{
			//Calls the python function for number of times a specific item was purchased and the string parameter based on the user input
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "Enter an item to know how many times it was purchased: " << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << endl;
			cin >> name;
			cout << name << " occur " << callIntFunc("determineFrequency", name) << " times " << endl;
			cout << endl;
		}

		else if (option == 3)
		{
			//Write item and frequency in frequency.dat file
			cout << "*********************************************************" << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~ HISTOGRAM ~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "*********************************************************" << endl;
			CallProcedure("output");
			cout << endl;

			//Read the frequency.dat file, and create the histogram
			ifstream writeFile;
			writeFile.open("frequency.dat");
			if (writeFile.is_open())
			{
				while (writeFile >> item >> frequency)
				{
					cout << item;
					for (int i = 0; i < frequency; i++)
					{
						cout << setw(2) << "*";
					}
					cout << endl;
				}
				writeFile.close();
			}

		}

	}

	//Prints exit and exits the program
	if (option == 4)
	{
		cout << "Exit" << endl;
	}

	return;
}