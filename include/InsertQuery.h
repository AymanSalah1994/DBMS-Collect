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
    fstream checkedFile  ;
    string databaseName  ;
    vector<string> theQueryVector ;
    string theQuery  ;
public :
    InsertQuery(string _theQuery, string _dbName = "" )
    {
        databaseName  = _dbName ;
        theQuery = _theQuery ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ",", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ";", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, "(", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ")", " ") ;
        HelperStaticClass::removeSpaces(theQuery) ;
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }

    string getTableFileName()
    {
        string tableFileName  = databaseName+"-"+theQueryVector.at(2)+".txt" ;
        return tableFileName ;
    }

    int queryIsShort()
    {
        if (theQueryVector.size() < 4 )
            return 1  ;
        else
            return 0  ;
    }

    int tableExists()
    {
        int result  =  0 ;
        string tableName  = getTableFileName() ;
        const char *c = tableName.c_str();
        checkedFile.open(c) ;
        if (checkedFile)
        {
            checkedFile.close() ;
            result = 1  ;
        }
        else
        {
            checkedFile.close() ;
            return 0 ; // This Will NOT continue the Function
        }
    }

    void evaluateTheInsertion()
    {

        if (queryIsShort() == 1)
        {
            cout<<"Query is Too Short to Handle !"<<endl ;
            return ; // This Will END the Evaluation
        }


        if (tableExists() == 0)
        {
            cout<<"There is NO Table With This Name or a Database !"<<endl ;
            return ; // This Will END the Evaluation
        }


        if (HelperStaticClass::queryToUpper(theQueryVector.at(3)) == HelperStaticClass::queryToUpper("values"))
        {
            try
            {
                vector<string>numberOfColumn  ; // From the File
                vector<string>valuesOfColumns ; // From the Query
                string firstLineOfTable  ;
                string tableName =  getTableFileName() ;
                const char *c = tableName.c_str();
                checkedFile.open(c) ;
                getline(checkedFile, firstLineOfTable , '\n') ;
                cout<<firstLineOfTable<<endl  ;
                cout<<getTableFileName() <<endl  ;
                checkedFile.close() ;
                int i  = 4  ;
                for (i ; i<theQueryVector.size(); i++)
                {
                        cout<<"Column Value:"<<theQueryVector.at(i)<<endl ;
                        valuesOfColumns.push_back(theQueryVector.at(i)) ;

                }
                numberOfColumn = HelperStaticClass::vectorFromString(firstLineOfTable) ;
                if (numberOfColumn.size() == valuesOfColumns.size())
                {
                    cout<<"Data Inserted Successfully"<<endl ;
                    int j  = 0 ;
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
                    throw 888 ;

                }

            }
            catch(int numError)
            {
                cout<<"Err Code 778" <<endl ;
            }

        }
        else
        {
            cout<<"Invalid Query , Check [Values] KeyWord and Syntax"<<endl ;
        }

    }

};

#endif // INSERTQUERY_H
