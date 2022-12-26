#ifndef UPDATINGQUERY_H
#define UPDATINGQUERY_H
#include <iostream>
#include<vector>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include<HelperStaticClass.h>
using namespace std;
class UpdatingQuery
{
private :
    string databaseName  ;
    vector<string> theQueryVector ;
    string theQuery  ;
public :
    UpdatingQuery(string _theQuery, string _dbName = "" )
    {
        databaseName  = _dbName ;
        theQuery = _theQuery ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, "=", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ";", " ") ;
        HelperStaticClass::removeSpaces(theQuery) ;
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }


    int hasWhereClause()
    {
        int result  = 0  ;
        int i = 0  ;
        for (i ; i < theQueryVector.size() ; i++)
        {
            if (HelperStaticClass::queryToUpper(theQueryVector.at(i)) == "WHERE" )
            {
                result   = 1  ;
                break ;
            }
        }
        return result  ;
    }

    void evaluateTheUpdate()
    {
        string tableFileName  = databaseName+"-"+theQueryVector.at(1)+".txt" ;
        const char *c = tableFileName.c_str();
        ifstream checkedFile  ;
        checkedFile.open(c) ;
        if (checkedFile)
        {
        }
        else
        {
            cout<<"There is No Table with this Name , Please Check Syntax Or specify a Database First !"<<endl ;
            checkedFile.close() ;
            return ; // This Will NOT continue the Function
        }

        // Check the SET KeyWord
        if (HelperStaticClass::queryToUpper(theQueryVector.at(2)) == HelperStaticClass::queryToUpper("set")  )
        {
            cout<<"Set KeyWord"<<endl;
            //Get the Column Names
            string firstLineOfTable  ;
            getline(checkedFile, firstLineOfTable) ;
            vector<string>columnNames = HelperStaticClass::vectorFromString(firstLineOfTable) ;
            vector<string>UpdatedColumnNames  ;
            vector<string>UpdatedColumnValues  ; // TO Expand For More Columns later
            int updatedValueIndex  ;
            string updatedValueValue ;
            int conditionUpdateIndex  ;
            string conditionUpdateColumnName  ;

            int UCNindex  = 3  ;
            while (HelperStaticClass::queryToUpper(theQueryVector.at(UCNindex)) != HelperStaticClass::queryToUpper("where") && hasWhereClause())
            {
                // It is a loop But for One Value Only For Now  to UPdate
                updatedValueValue = theQueryVector.at(UCNindex+1)  ;
                cout<<theQueryVector.at(UCNindex)<<theQueryVector.at(UCNindex+1) ;
                UpdatedColumnNames.push_back(HelperStaticClass::queryToUpper(theQueryVector.at(UCNindex))) ;
                // The Column we want to update value For
                UpdatedColumnValues.push_back(theQueryVector.at(UCNindex+1)) ;
                if (HelperStaticClass::queryToUpper(theQueryVector.at(UCNindex)) != HelperStaticClass::queryToUpper("where"))
                    UCNindex += 2 ;
            }

            string realStringCondionValue ;
            if (hasWhereClause())
            {
                try
                {
                cout<<"Where index" <<UCNindex ;
                conditionUpdateColumnName = theQueryVector.at(UCNindex+1) ;
                realStringCondionValue = theQueryVector.at(UCNindex+2) ;
                cout<<conditionUpdateColumnName ;
                cout<<"===BBB===="<<endl ;
                cout<<realStringCondionValue ;
                }
                catch (const std::out_of_range& e)
                {
                    cout << "Check the SQL Syntax !";
                    return ;
                }

            }
            else
            {
                cout<<"For Safety Of your Data , General Update is Not Allowed ! " <<endl ;
                return ;
            }

            int y =  0  ;
            for (y ;  y < columnNames.size() ; y++)
            {
                if (HelperStaticClass::queryToUpper(columnNames.at(y))== HelperStaticClass::queryToUpper(conditionUpdateColumnName))
                {
                    conditionUpdateIndex = y  ;
                    cout<<"Condition "<<conditionUpdateIndex<<endl ;
                    cout<<realStringCondionValue<<endl ;
                }
                if (HelperStaticClass::queryToUpper(columnNames.at(y)) == HelperStaticClass::queryToUpper(UpdatedColumnNames.at(0)))
                {
                    cout<<"TO Update"<<y<<endl ;
                    updatedValueIndex = y  ;
                }
            }

            HelperStaticClass::updateFileData(c, conditionUpdateIndex, realStringCondionValue, updatedValueIndex, updatedValueValue) ;
            //FileName  , conditionIndex , conditionValue , updatedIndex , UpdatedValue

        }
        else
        {
            cout<<"Please Check the SQL Syntax" <<endl  ;
        }

    }

};

#endif // UPDATINGQUERY_H
