#pragma once

#include <iostream>

using namespace std;
class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	
	
public:
	clsPerson(string FirstName, string LastName)
	{
		_FirstName = FirstName;
		_LastName = LastName;
	}

	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	//Property Get
	string GetFirstName()
	{
		return _FirstName;
	}
	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	//Property Set
	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}
	//Property Get
	string GetLastName()
	{
		return _LastName;
	}
	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;


};

