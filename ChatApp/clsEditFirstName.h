#pragma once

#include "clsScreen.h"
class clsEditFirstName : protected clsScreen
{

public:

	static void EditFirstName()
	{
		_DrawScreenHeader("\t  Edit First Name");
		string FirstName = "";
		cout << "\t\t\t\t\t You First Name is   : " << CurrentUser.FirstName;
		cout << "\n\t\t\t\t\t Enter new Last Name: ";
		FirstName = clsInputValidate<string>::ReadString();

		CurrentUser.FirstName = FirstName;
		clsUser::enSaveResults SaveResults;
		SaveResults = CurrentUser.Save();

		if (SaveResults == clsUser::enSaveResults::svSucceeded)
		{
			cout << "\n\t\t\t\t\tYour First Name Edited Successfully :-)";
		}
		else {
			cout << "\n\t\t\t\t\tAn error has been here, try again please )-:";
		}
	}
};

