#pragma once


#include "clsScreen.h"
class clsEditLastName : protected clsScreen
{

public:

	static void EditLastName()
	{
		_DrawScreenHeader("\t  Edit Last Name");
		string LastName = "";
		cout << "\t\t\t\t\t You Last Name is   : " << CurrentUser.LastName;
		cout << "\n\t\t\t\t\t Enter new Last Name: ";
		LastName = clsInputValidate<string>::ReadString();

		CurrentUser.LastName = LastName;
		clsUser::enSaveResults SaveResults;
		SaveResults = CurrentUser.Save();

		if (SaveResults == clsUser::enSaveResults::svSucceeded)
		{
			cout << "\n\t\t\t\t\tYour Last Name Edited Successfully :-)";
		}
		else {
			cout << "\n\t\t\t\t\tAn error has been here, try again please )-:";
		}
	}
};

