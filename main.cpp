#include <iostream>
#include<conio.h>
#include<HelperStaticClass.h>
#include<User.h>
#include<CreateQuery.h>
#include<InsertQuery.h>
#include<UpdatingQuery.h>
#include<SelectClass.h>
#include<DeleteClass.h>
using namespace std;

int main()
{
    User u;
    while (true)
    {
        if (u.loggedIn == 0 )
        {
            u.showIntro() ;
            cin.get(u.userCommand, 200) ;

            if (u.userCommand[0] == 0 )
                break ;
            else if (strcmp(u.userCommand,"login()") == 0 )
            {
                string nameEnter;
                string passEnter;
                cout<<"Enter User Name:" ;
                cin>>nameEnter ;
                cout<<"Enter Password:";
                cin>>passEnter ;
                cout<<endl ;
                u.logInUser(nameEnter, passEnter) ;
                 strcpy(u.userCommand, "*");

                cin.ignore();
                continue ;
            }
            else if (strcmp(u.userCommand,"new()") == 0 )
            {
                strcpy(u.userCommand, "" );
                u.promptAccountCreation();
                u.insertUserData() ;

            }
            else if (strcmp(u.userCommand,"q()") == 0   || strcmp(u.userCommand,"quit()") == 0 )
            {
                strcpy(u.userCommand, "" );
                break ;
            }
            else
            {
                cout<<"\n" ;
                cout<<"Invalid Command , Press ENTER and Write One Of Available Commands !"<<endl ;
                strcpy(u.userCommand, "*");
                _getch() ;
                cin.ignore();
                continue ;
            }

        }
        if (u.loggedIn == 1 )
        {
            break ;
        }
    }


    if (u.loggedIn == 1 )
    {
        while(true)
        {
            system("cls") ;
            u.showUserInfoWelcome() ;
            u.waitForCommand() ;
            cin.ignore();
            cin.get(u.userCommand, 200) ;

            if (u.userCommand[0]  == 0 )
            {
                break ;
            }

            string userCommandAsString(u.userCommand) ;
            userCommandAsString.append(" ;") ;
            vector<string> userCommandAsVector   ;
            userCommandAsVector = HelperStaticClass::vectorFromString(userCommandAsString) ;


            if (HelperStaticClass::queryToUpper(userCommandAsVector.at(0)) == "USE")
            {
                if (HelperStaticClass::dbExists(userCommandAsVector.at(1)) == 1 )
                {
                    u.DBName = userCommandAsVector.at(1);
                    cout<<"Query Finished 200 OK" ;
                    _getch() ;
                    continue ;
                }
                else
                {
                    cout<<"Invalid DataBase Name"<<endl ;
                    _getch() ;
                    continue ;
                }
            }


            else if (HelperStaticClass::queryToUpper(userCommandAsVector.at(0)) == "CREATE" )
            {
                CreateQuery CQ(userCommandAsString, u.DBName);
                CQ.evaluateTheCreation() ;
                u.DBName = CQ.databaseName ;
                _getch() ;
            }


            else if (HelperStaticClass::queryToUpper(userCommandAsVector.at(0)) == "INSERT" )
            {
                InsertQuery IQ(userCommandAsString, u.DBName);
                IQ.evaluateTheInsertion() ;
                _getch() ;
            }



            else if (HelperStaticClass::queryToUpper(userCommandAsVector.at(0)) == "UPDATE" )
            {
                UpdatingQuery UQ(userCommandAsString, u.DBName);
                UQ.evaluateTheUpdate() ;
                _getch() ;
            }


            else if (HelperStaticClass::queryToUpper(userCommandAsVector.at(0)) == "SELECT" )
            {
                SelectClass SQ(userCommandAsString, u.DBName);
                SQ.evaluateTheSelection() ;
                _getch() ;
            }


            else if (HelperStaticClass::queryToUpper(userCommandAsVector.at(0)) == "DELETE" )
            {
                DeleteClass DC(userCommandAsString, u.DBName) ;
                DC.evaluateDelete() ;
                _getch() ;
            }


            else if (HelperStaticClass::queryToUpper(userCommandAsVector.at(0)) == "EXIT()" )
            {
                break ;
            }

            else
            {
                cout<<"Invalid Command ! Write a SQL Query Or exit() to Quit Or Manual To Show Manual"<<endl ;
                _getch() ;
            }

        }
    }// End If logged in = 1



    return 0;
}
