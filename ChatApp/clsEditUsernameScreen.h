#pragma once

#include "clsScreen.h"
class clsEditUsernameScreen : protected clsScreen
{


public:

	static void EditUsername()
	{
		_DrawScreenHeader("\t  Edit First Name");
		cout << "\t\t\t\t\t You username is: " << CurrentUser.Username;
		cout << "\n\t\t\t\t\t Enter new user name: ";
		
		string Username = clsInputValidate<string>::ReadString();
		while (clsUser::IsUserExist(Username))
		{
			cout << "\n\t\t\t\t\tSorry, username is exist, enter another one: ";
			Username = clsInputValidate<string>::ReadString();
		}


		CurrentUser.Username = Username;
		clsUser::enSaveResults SaveResults;
		SaveResults = CurrentUser.Save();

		if (SaveResults == clsUser::enSaveResults::svSucceeded)
		{
			cout << "\n\t\t\t\t\tYour Username Edited Successfully :-)";
		}
		else {
			cout << "\n\t\t\t\t\tAn error has been here, try again please )-:";
		}
	}
};

