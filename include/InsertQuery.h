#ifndef INSERTQUERY_H
#define INSERTQUERY_H
#include <iostream>
#include<vector>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include<HelperStaticClass.h>
using namespace std;

class InsertQuery
{
private :
    string databaseName  ;
    vector<string> theQueryVector ;
    string theQuery  ;
public :
    InsertQuery(string _theQuery, string _dbName = "" )
    {
        databaseName  = _dbName ;
        theQuery = _theQuery ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ",", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, "(", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ")", " ") ;
        HelperStaticClass::removeSpaces(theQuery) ;
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }

    void evaluateTheInsertion()
    {
        string tableFileName  = databaseName+"-"+theQueryVector.at(2)+".txt" ;
        const char *c = tableFileName.c_str();
        ifstream checkedFile  ;
        checkedFile.open(c) ;
        if (checkedFile)
        {

        }
        else
        {
            cout<<"There is NO Table With This Name !"<<endl ;
            checkedFile.close() ;
            return ; // This Will NOT continue the Function
        }

        if (HelperStaticClass::queryToUpper(theQueryVector.at(3)) == HelperStaticClass::queryToUpper("values"))
        {
            vector<string>numberOfColumn  ; // From the File
            vector<string>valuesOfColumns ; // From the Query
            string firstLineOfTable  ;
            getline(checkedFile, firstLineOfTable) ;
            cout<<firstLineOfTable<<endl  ;
            int i  = 4  ;
            for (i ; i<theQueryVector.size(); i++)
            {
                if (theQueryVector.at(i) != ";" )
                {
                    cout<<"Column Value:"<<theQueryVector.at(i)<<endl ;
                    valuesOfColumns.push_back(theQueryVector.at(i)) ;
                }
            }
            numberOfColumn = HelperStaticClass::vectorFromString(firstLineOfTable) ;
            if (numberOfColumn.size() == valuesOfColumns.size())
            {
                cout<<"Data Inserted Successfully"<<endl ;
                int j  = 0 ;
                fstream checkedFile ;
                checkedFile.open(c, ios::app) ;
                for (j ; j < valuesOfColumns.size() ; j++)
                {
                    checkedFile<<valuesOfColumns.at(j)<<" " ;
                }
                checkedFile<<"\n" ;
                checkedFile.close() ;
            }
            else
            {
                cout<<"Please Check that the Values Inserted Match the Column"<<endl ;
            }

        }
        else
        {
            cout<<"Invalid Query , Check Values KeyWord and Syntax"<<endl ;
        }

    }

};

#endif // INSERTQUERY_H
