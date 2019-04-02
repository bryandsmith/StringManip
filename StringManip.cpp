// Written by Bryan Smith
// 3/19/2019
#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
/*
	Method Signatures
*/
static void inputData(string &);
string trim(string);
string clean(string);
static void outputData(string);
int main()
{
	string myString;
	cout << "Please enter your name: \n";
	// Name is expected to be input as: last, first, middle initial
	getline(cin, myString);
	inputData(myString);
	outputData(myString);
}
/* Gets the reference to the string, if its empty, return.
 If not, call stringstream and pull words out of string, then arrange them in the desired order. */
static void inputData(string &input)
{
	//trim the string
	input = trim(input);
	string first, middle, last, newString;
	//call an istringstream to pull words out of the string, seperated by spaces
	istringstream ss(input);
	//if string is blank, then return
	if (input.compare("") == 0)
	{
		cout << "String is empty. \n";
		return;
	}
	//vulnerable to out of range exceptions. Caught in clean method
	ss >> last;
	last = clean(last);
	ss >> first;
	first = clean(first);
	ss >> middle;
	middle = clean(middle);
	//empty the stringstream
	ss.str("");
	//concatenate the string into a new string
	newString += first + " " + middle + " " + last;
	//empty the referenced string, starting from index 0 to the length of the string.
	input.erase(0, input.length());
	//insert new string into the original string
	input.insert(0, newString);
}
static void outputData(string input)
{
	//print the string
	cout << input << "\n";
}
//this function trims whitespace on either side of a string
string trim(string str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	if (first == string::npos)
	{
		return "";
	}
	return str.substr(first, (last - first + 1));
}
//this function removes any non-alphabetic letters from the end of the string
string clean(string str)
{
	size_t end = str.length() - 1;
	try
	{
		if (!(isalpha(str[end])))
		{
			str.pop_back();
		}
	}
	catch (out_of_range err)
	{
		cout << "Out of range: incorrect information given. Please try again.";
	}
	return str;
}