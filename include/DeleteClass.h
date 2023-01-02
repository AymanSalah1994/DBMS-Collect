#ifndef DELETECLASS_H
#define DELETECLASS_H
#include <iostream>
#include<vector>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include<HelperStaticClass.h>

using namespace std;
class DeleteClass
{
private :
    string databaseName  ;
    vector<string> theQueryVector ;
    string theQuery  ;
public :
    DeleteClass(string _theQuery, string _dbName = "")
    {
        databaseName  = _dbName ;
        theQuery = _theQuery ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ";", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, "=", " ") ;
        HelperStaticClass::removeSpaces(theQuery) ;
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }


    // Check that the DB Names is Specified and Not Null
    int dbNotNull()
    {
        if (databaseName == "")
            return 0 ;
        else
            return 1  ;
    }

    void evaluateDelete()
    {

        if (dbNotNull() == 0)
        {
            cout<<"Please Specify a Database First , use USE keyWord "<<endl  ;
            return ;
        }



        string tableFileName = databaseName+"-"+theQueryVector.at(2)+".txt" ;
        const char *table = tableFileName.c_str();
        ifstream checkedFile  ;
        checkedFile.open(table) ;
        if (checkedFile)
        {
            cout<<"File is There "<<endl  ;
            if(theQueryVector.size() == 3)
            {
                //Todo , this Needs a Refactor
                checkedFile.close() ;
                remove(table);
                cout <<table << endl;
                cout << "Table deleted successfully";
                return;
            }
            else
            { // Else if Length is Not 3 , There is a Where
                ofstream temp;
                temp.open("temp.txt");
                vector<string>numberOfColumn  ; // From the File
                vector<string>valuesOfColumns ; // From the File
                string lineOfTable ;
                getline(checkedFile, lineOfTable);
                temp << lineOfTable << std::endl;
                //getline(checkedFile, lineOfTable);
                //temp << lineOfTable << std::endl;
                numberOfColumn = HelperStaticClass::vectorFromString(lineOfTable);
                valuesOfColumns =HelperStaticClass::vectorFromString(lineOfTable);
                int index;
                for(int i=0 ; i<numberOfColumn.size() ; i++)
                {
                    if (HelperStaticClass::queryToUpper(theQueryVector.at(4)) == HelperStaticClass::queryToUpper(numberOfColumn.at(i)))
                    {
                        // Delete From users where id = 34
                        index = i;
                        cout<<"Index of I  (the Condition) is :" <<index<<endl ;
                        break;
                    }
                }

                while(getline(checkedFile, lineOfTable))
                {
                    valuesOfColumns = HelperStaticClass::vectorFromString(lineOfTable);
                    if(valuesOfColumns.at(index) != theQueryVector.at(5)) // This was the BUG
                    {
                        temp << lineOfTable << std::endl;
                    }
                }

                temp.close();
                checkedFile.close();
                const char * p = tableFileName.c_str();

                remove(p);
                rename("temp.txt", p);
                 cout << "records successfully deleted";

            }

        }
        else
        {
            cout<<"There is NO Table With this Name !"<<endl ;
            cout<<tableFileName ;
            return ; // This Will NOT continue the Function
        }

    }

};


#endif // DELETECLASS_H
