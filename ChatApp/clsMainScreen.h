#pragma once

#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsShowSendMessageScreen.h"
#include "clsEditUserScreen.h"
#include "Global.h"
class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenueOptions { eSendMessage = 1, eEditData = 2, eLogout = 3 };;
    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowSendMessageScreen()
    {
        //cout << "Send Message Screen will be here";
        clsShowSendMessageScreen::ShowSendMessageScreen();
    }

    static void _ShowEditDataScreen()
    {
        //cout << "Edit data will be here . . .";
        clsEditUserScreen::EditScreen();
    }


    static void _PerfromMainMenueOption(enMainMenueOptions Option)
    {
        switch (Option)
        {
        case enMainMenueOptions::eSendMessage:
            system("cls");
            _ShowSendMessageScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueOptions::eEditData:
            system("cls");
            _ShowEditDataScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueOptions::eLogout:
            //Don't Do Anything 
        default:
            break;
        }
    }
public:

	static void ShowMainMenue()
	{
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Send Message.\n";
        cout << setw(37) << left << "" << "\t[2] Edit Your Data.\n";
        cout << setw(37) << left << "" << "\t[3] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 3]? ";
        _PerfromMainMenueOption((enMainMenueOptions)clsInputValidate<short>::ReadNumberBetween(1,3));
	}
};

