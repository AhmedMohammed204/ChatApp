#pragma once

#include "clsUser.h"
class clsRegisterNewUser
{
	static clsUser _ReadUser(clsUser & User)
	{


		cout << "\n\t\t\t\t\tEnter Your First Name: ";
		User.FirstName = clsInputValidate<string>::ReadString();
		
		cout << "\t\t\t\t\tEnter Your Last Name: ";
		User.LastName = clsInputValidate<string>::ReadString();
		
		cout << "\t\t\t\t\tEnter Your Password: ";
		User.Password = clsInputValidate<string>::ReadString();

		User.ID = to_string(clsUser::GetUsersList().size() + 1);
		return User;
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

public:

	static void Register()
	{
		cout << "\n\t\t\t\t\tEnter Username: ";
		string Username = clsInputValidate<string>::ReadString();
		while (clsUser::IsUserExist(Username))
		{
			cout << "\n\t\t\t\t\tSorry, username is exist, enter another one: ";
			Username = clsInputValidate<string>::ReadString();
		}
		clsUser NewUser = clsUser::GetAddNewUserObject(Username);
		_ReadUser(NewUser);




		clsUser::enSaveResults SaveResult;
		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsUser::svFaildEmptyObject:
			cout << "\t\t\t\t\t Faild to add because it's empty eser\n";
			break;
		case clsUser::svSucceeded:
			cout << "\t\t\t\t\t User Added Successfully!\n";
			_Print(NewUser);
			break;
		case clsUser::svFaildUserExists:
			cout << "\t\t\t\t\t Faild to add because user is already exist\n";
			break;
		default:
			break;
		}

		cout << "\n\n\t\t\t\t\tPrees any key to go back to Login Screen . . . ";
		system("pause>0");
	}
};

