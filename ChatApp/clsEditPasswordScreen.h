#pragma once

#include "clsScreen.h"
class clsEditPasswordScreen : protected clsScreen
{

public:

	static void EditPassword()
	{
		_DrawScreenHeader("\t  Edit Password");
		string Password = "";
		cout << "\t\t\t\t\t You Password is   : " << CurrentUser.Password;
		cout << "\n\t\t\t\t\t Enter new password: ";
		Password = clsInputValidate<string>::ReadString();

		CurrentUser.Password = Password;
		clsUser::enSaveResults SaveResults;
		SaveResults = CurrentUser.Save();

		if (SaveResults == clsUser::enSaveResults::svSucceeded)
		{
			cout << "\n\t\t\t\t\tYour Password Edited Successfully :-)";
		}
		else {
			cout << "\n\t\t\t\t\tAn error has been here, try again please )-:";
		}
	}

};

