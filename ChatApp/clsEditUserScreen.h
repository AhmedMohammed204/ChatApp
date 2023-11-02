#pragma once

#include <iomanip>
#include "clsScreen.h"
#include "clsEditUsernameScreen.h"
#include "clsEditPasswordScreen.h"
#include "clsEditFirstName.h"
#include "clsEditLastName.h"
class clsEditUserScreen : protected clsScreen
{

private:
	enum enEditUserOptions {
		eFirstName = 1, eLastName = 2, eUsername = 3, ePassword = 4, eMainMenu = 5
	};
	static void _GoBackToEditUserScreen()
	{
		cout << "\n\nPress any key to go back to edit user menu. . .";
		system("pause>0");
		EditScreen();
	}
	static void _Print(clsUser User)
	{
		cout << "\n\t\t\t\t\tUser Info: ";
		cout << "\n\t\t\t\t\t_________________________\n";

		cout << "\t\t\t\t\tID         : " << User.ID << endl;
		cout << "\t\t\t\t\tFirst Name : " << User.FirstName << endl;
		cout << "\t\t\t\t\tLast Name  : " << User.LastName << endl;
		cout << "\t\t\t\t\tUsername   : " << User.Username << endl;
		cout << "\t\t\t\t\tPassword   : " << User.Password << endl;


		cout << "\n\t\t\t\t\t_________________________\n";
	}

	static void _EditFirstName()
	{
		//cout << "Edit first name will be here";
		clsEditFirstName::EditFirstName();
	}
	static void _EditLastName()
	{
		//cout << "Edit Last Name will be here";
		clsEditLastName::EditLastName();
	}
	static void _EditUsername()
	{
		//cout << "Edit Username will be here";
		clsEditUsernameScreen::EditUsername();
	}
	static void _EditPassword()
	{
		//cout << "Edit password will be here";
		clsEditPasswordScreen::EditPassword();
	}

	static void _PerformEditUserScreen(enEditUserOptions Option)
	{
		switch (Option)
		{
		case clsEditUserScreen::eFirstName:
			system("cls");
			_EditFirstName();
			_GoBackToEditUserScreen();
			break;
		case clsEditUserScreen::eLastName:
			system("cls");
			_EditLastName();
			_GoBackToEditUserScreen();
			break;
		case clsEditUserScreen::ePassword:
			system("cls");
			_EditPassword();
			_GoBackToEditUserScreen();
			break;
		case clsEditUserScreen::eUsername:
			system("cls");
			_EditUsername();
			_GoBackToEditUserScreen();
			break;
		case clsEditUserScreen::eMainMenu:
			break;
		default:
			break;
		}
	}

public:

	static void EditScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Edit Data Screen");

		_Print(CurrentUser);
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tEdit User Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Change First Name.\n";
		cout << setw(37) << left << "" << "\t[2] Change Last Name.\n";
		cout << setw(37) << left << "" << "\t[3] Change Username.\n";
		cout << setw(37) << left << "" << "\t[4] Change Password.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		_PerformEditUserScreen((enEditUserOptions)clsInputValidate<short>::ReadNumberBetween(1, 5));
	}

};


