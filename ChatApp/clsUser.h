

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsUtil.h"
#include "clsString.h"
#include "clsInputValidate.h"

class clsUser : public clsPerson
{
private:
	
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	struct stMessage;
	enMode _Mode;
	string _ID;
	string _Username;
	string _Password;
	bool _MarkedForDeleted = false;

	static clsUser _ConvertRecordToUser(string Line)
	{
		vector <string> vUserDate = clsString::Split(Line, "#//#");

		return clsUser(enMode::UpdateMode, vUserDate[0],
			vUserDate[1], vUserDate[2], vUserDate[3], clsUtil::DecryptText(vUserDate[4]));
	}
	static string _ConvertUserToRecord(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Username + Seperator;
		UserRecord += User.ID + Seperator;
		UserRecord += clsUtil::EncryptText(User.Password);

		return UserRecord;
	}
	
	string _PrepareMessage(string Message, string Seperator = "#//#")
	{
		string RecordMessage = "";

		RecordMessage += clsDate::GetSystemDateTimeString() + Seperator;
		RecordMessage += this->ID + Seperator;
		RecordMessage += Message;

		return RecordMessage;
	}
	static stMessage _ConvertRecordToMessage(string Line)
	{
		stMessage Message;
		vector <string> vMessageData = clsString::Split(Line, "#//#");

		Message.Date = vMessageData[0];
		Message.ID = vMessageData[1];
		Message.Message = vMessageData[2];

		return Message;
	}

	static clsUser _GetEmptyUser()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "0", "0");
	}

	static  vector <clsUser> _LoadUsersDataFromFile()
	{

		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsUser User = _ConvertRecordToUser(Line);

				vUsers.push_back(User);
			}

			MyFile.close();

		}

		return vUsers;

	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConvertUserToRecord(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}


	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsUser U : vUsers)
			{
				if (U.MarkedForDeleted() == false)
				{
					//we only write records that are not marked for delete.  
					DataLine = _ConvertUserToRecord(U);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}

	}


	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.ID == ID)
			{
				U = *this;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

	}


public:
	struct stMessage {
		string Date;
		string ID;
		string Message;
	};
	clsUser(enMode Mode, string FirstName, string LastName, string Username, string ID, string Password)
		: clsPerson(FirstName, LastName)
	{
		_Mode = Mode;
		_ID = ID;
		_Username = Username;
		_Password = Password;
	}

	
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDeleted;
	}

	string GetUserName()
	{
		return _Username;
	}

	void SetUserName(string UserName)
	{
		_Username = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string Username;


	void SetID(string ID)
	{
		_ID = ID;
	}
	string GetID()
	{
		return _ID;
	}
	__declspec(property(get = GetID, put = SetID)) string ID;

	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	static clsUser Find(string Username)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertRecordToUser(Line);
				if (User.Username == Username)
				{
					return User;
				}

			}

			MyFile.close();
		}

		return _GetEmptyUser();

	}
		
	static clsUser Find(string Username, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertRecordToUser(Line);
				if (User.Username == Username && User.Password == Password)
				{
					return User;
				}

			}

			MyFile.close();
		}

		return _GetEmptyUser();

	}
	
	static bool IsUserExist(string Username)
	{

		clsUser User = clsUser::Find(Username);
		return (!User.IsEmpty());
	}

	void SendMessage(string Message, clsUser UserDestination)
	{
		string RecordMessage = _PrepareMessage(Message);

		fstream MyFile;
		int ChatNumber = stoi(ID) + stoi(UserDestination.ID);
		string FileName = "Chat" + to_string(ChatNumber) + ".txt";
		MyFile.open(FileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
		
			MyFile << RecordMessage << endl;
			
			MyFile.close();

		}
	}
	static clsUser GetAddNewUserObject(string Username)
	{
		return clsUser(enMode::AddNewMode, "", "", Username, "", "");
	}
	static vector < stMessage> GetChatMessages(clsUser SourceUser, clsUser UserDestination)
	{
		vector <stMessage> vMessages;


		fstream MyFile;
		int ChatNumber = stoi(SourceUser.ID) + stoi(UserDestination.ID);
		string FileName = "Chat" + to_string(ChatNumber) + ".txt";
		MyFile.open(FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				stMessage Message = _ConvertRecordToMessage(Line);
				vMessages.push_back(Message);
			}

			MyFile.close();
		}

		return vMessages;
	}
	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsUser::IsUserExist(_Username))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}

	}
};

