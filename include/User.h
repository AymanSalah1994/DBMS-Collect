#ifndef USER_H
#define USER_H
#include <iostream>
#include<string.h>
#include <stdio.h>
#include <fstream>
#include<sstream>
#include <cstdlib>
using namespace std;
class User
{
private :
    string name  ;
    string password ;

public:
    string DBName ;
    char userCommand[200] ;
    int loggedIn ;
    User()
    {
        name = "" ;
        password = "" ;
        loggedIn = 0  ;
    }
    User (string _name, string _password)
    {
        name  = _name ;
        password = _password ;
        loggedIn = 0 ;
    }

    void promptAccountCreation()
    {
        char nameEnter[20] = "" ;
        char passEnter[20] = "" ;
        cout<<"Enter User Name:" ;
        cin>>nameEnter ;
        cout<<"Enter Password:";
        cin>>passEnter ;
        cout<<endl ;
        name = nameEnter ;
        password = passEnter ;
        loggedIn = 1  ;
    }

    void showIntro()
    {
        cout<<"Welcome,If this is the First Time you should create and Account ."<<endl ;
        cout<<"Write q() or quit() To Quit,new() to create new User or login() to signin"<<endl;
        cout<<"Hit Enter ONLY without anything to Exit" ;
        cout<<"--> $ " ;
    }

    void showUserInfoWelcome()
    {
        cout<<"======User-"<<name<<"======"<<endl ;
        cout<<"Hit Enter ONLY without anything to Exit"<<endl ;
        if (DBName == "")
        {
         cout<<"Please Create Or Specify a Database to Use"<<endl ;
        }
        else
        {
            cout<<"======"<<DBName<<"======"<<endl ;
        }
    }

    void insertUserData()
    {
        // This will Be Method To save New User Credits  ;
        fstream newFileObject  ;
        newFileObject.open("UsersFile.txt", ios::app) ;
        newFileObject<<name<<":"<<password<<"\n" ;
        newFileObject.close() ;
        cout<<"\nData Saved Successfully"<<endl ;
    }

    void logInUser(string _userName, string _password)
    {
        fstream newFileObject  ;
        newFileObject.open("UsersFile.txt") ; // Here we Just Open it to Read Not Append
        while(!newFileObject.eof())
        {
            string lineInFile  = "" ; // We Need String reading Line , Char Gives and Error ;
            getline(newFileObject, lineInFile) ;
            string userLine  = _userName+":"+_password ;
            string usrName  = lineInFile.substr(0, lineInFile.find(":")) ;
            string pass = lineInFile.substr(lineInFile.find(":")+1, lineInFile.find("\n")) ;
            if (lineInFile  == userLine)
            {
                loggedIn = 1  ;
                name = usrName ;
                password = pass ;
                newFileObject.close() ;
            }
            if(newFileObject.eof() && loggedIn == 0 )
            {
                cout<<"Invalid Data"<<endl ;
                newFileObject.close() ;
            }
        }
        newFileObject.close() ;
    }

    void waitForCommand()
    {
        cout<<"Enter Command ~$ " ;
    }
};

#endif // USER_H
