#pragma once

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsShowSendMessageScreen : protected clsScreen
{
private:
	static clsUser _FindUser()
	{
		cout << "\n\t\t\t\t\tPlease enter username ";
		string Username = clsInputValidate<string>::ReadString();
		
		while ((!clsUser::IsUserExist(Username)) || CurrentUser.Username == Username)
		{
			cout << "\t\t\t\t\tUsername is not exist, enter another Username: ";
			Username = clsInputValidate<string>::ReadString();
		}
		clsUser User = clsUser::Find(Username);
		return User;
	}

	static void _PrintMessage(clsUser::stMessage Message, clsUser UserDestination)
	{

		if (Message.ID == CurrentUser.ID)
		{
			cout << "\t\t\t\t\t" << "'You'" << " :";
			cout << "\n\t\t\t\t\t" << Message.Message;
		}
		else
		{
			cout << "\t\t\t\t";
			cout << "\t\t\t\t" << ": " << UserDestination.Username;
			cout << "\n\t\t\t\t\t\t\t\t" << Message.Message;

		}
	}

	static void _StartChatting(clsUser UserDestination)
	{
		while(true)
		{
			system("cls");
			enum enChatOptions { eSendMessage = 1, EndChatting = 2 };
			string ChatTitle = "\t  /( " + UserDestination.FirstName + " " + UserDestination.LastName + " )\\";
			_DrawScreenHeader("\t\tChat Box");
			cout << "\t\t\t\t\t______________________________________\n";
			cout << "\n\t\t\t\t\t" << ChatTitle << endl;
			
			vector <clsUser::stMessage> vMessages = clsUser::GetChatMessages(CurrentUser, UserDestination);

			if (vMessages.size() == 0)
			{
				cout << "\t\t\t\t\tNo Messages. . .";
			}
			else
			{
				for (clsUser::stMessage Message : vMessages)
				{
					_PrintMessage(Message, UserDestination);
					cout << endl;
					cout << endl;
				}
			}
			cout << "\n\t\t\t\t\t______________________________________\n";
			cout << "\t\t\t\t\tWrite your message\n\t\t\t\t\tif you want to left send -1: \n\t\t\t\t\t";
			string NewMessage = clsInputValidate<string>::ReadString();

			if (NewMessage == "-1")
				break;

			CurrentUser.SendMessage(NewMessage, UserDestination);
		}


	}
public:
	static void ShowSendMessageScreen()
	{
		_DrawScreenHeader("\t  Send Message Screen", "Find Chat");

		clsUser UserDestination = _FindUser();
		_StartChatting(UserDestination);
	}
};

