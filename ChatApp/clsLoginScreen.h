#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsString.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsRegisterNewUser.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short FaildLoginCount = 0;

        cout << "\t\t\t\t\tDo you have an account ? Y/N? ";
        if (!clsInputValidate<bool>::ReadYandN())
        {
            clsRegisterNewUser::Register();
            system("cls");
            _DrawScreenHeader("\t    Login Screen");
        }

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                FaildLoginCount++;

                cout << "\n\t\t\t\t\tInvlaid Username/Password!";
                cout << "\n\t\t\t\t\tYou have " << (3 - FaildLoginCount)
                    << " Trial(s) to login.\n\n";
            }

            if (FaildLoginCount == 3)
            {
                cout << "\n\t\t\t\t\tYour are Locked after 3 faild trails \n\n";
                return false;
            }

            cout << "\t\t\t\t\tEnter Username? ";
            cin >> Username;

            cout << "\t\t\t\t\tEnter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t    Login Screen");
        return _Login();

    }

};
