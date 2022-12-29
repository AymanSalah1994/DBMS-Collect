#ifndef SELECTCLASS_H
#define SELECTCLASS_H
#include <iostream>
#include<vector>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include<string>
#include<HelperStaticClass.h>

class SelectClass
{
private:
    string databaseName  ;
    vector<string> theQueryVector ;
    string theQuery  ;
    vector<string>allTableColumns ;
    vector<string>queryColumnNames  ;
    vector<int>theQueryIndexesVector ;
public:
    SelectClass(string _theQuery,string _dataBaseName ="")
    {
        databaseName = _dataBaseName ;
        theQuery = _theQuery ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ",", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ";", " ") ;
        HelperStaticClass::removeSpaces(theQuery) ;
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }




    int queryIsShort()
    // A Select Query is at Least 4
    {
        if (theQueryVector.size() < 4 )
            return 1  ;
        else
            return 0  ;
    }


    int hasFromClause()
    {
        int hasFrom = 0 ;
        int i  = 0 ;
        for (i ; theQueryVector.size() ; i++)
        {
            if (HelperStaticClass::queryToUpper(theQueryVector.at(i)) == "FROM")
            {
                hasFrom = 1 ;
                break ;
            }
        }
        return hasFrom ;
    }


    int fromIndex()
    {
        int fromIndex = 0 ;
        int i =  0;
        for (i ; theQueryVector.size() ; i++)
        {
            if (HelperStaticClass::queryToUpper(theQueryVector.at(i)) == "FROM")
            {
                fromIndex = i ;
                break ;
            }
        }
        return fromIndex ;
    }


    void fillAllTableColumnNames()
    {
        int fromIndexNumber = fromIndex() ;
        string tableFileName  = databaseName+"-"+theQueryVector.at(fromIndexNumber + 1)+".txt" ;
        const char *c = tableFileName.c_str();
        ifstream checkedFile  ;
        checkedFile.open(c) ;
        string firstLineOfTable  ;
        getline(checkedFile, firstLineOfTable) ;
        allTableColumns =HelperStaticClass::vectorFromString(firstLineOfTable) ;
        checkedFile.close() ;
    }

    void fillQueryColumnNames()
    {
        if (theQueryVector.at(1) == "*")
        {
            queryColumnNames = allTableColumns ;
            // Should it Be Loop ?
            // TODO
        }
        else
        {
            int index = 1  ;
            while (true)
            {
                if (HelperStaticClass::queryToUpper(theQueryVector.at(index)) == "FROM" )
                    break ;
                queryColumnNames.push_back(HelperStaticClass::queryToUpper(theQueryVector.at(index))) ;
                index += 1 ;
            }
        }
    }

    int invalidColumnsInQuery()
    {
        int result  = 0  ;
        int i = 0  ;
        for (i ; i < queryColumnNames.size() ; i++)
        {
            if (std::find(allTableColumns.begin(), allTableColumns.end(),queryColumnNames.at(i))!=allTableColumns.end())
            {
                // Nothing to Do , Keep Going
            }
            else
            {
                result = 1  ;
                break ;
            }
        }
        return result ;
    }



    void fillTheIndexes()
    {
        int i = 0  ;
        for (i ; i < queryColumnNames.size() ; i++)
        {
            int j = 0  ;
            for (j ; j < allTableColumns.size() ; j++)
            {
                if (HelperStaticClass::queryToUpper(queryColumnNames.at(i)) == HelperStaticClass::queryToUpper(allTableColumns.at(j)))
                {
                    theQueryIndexesVector.push_back(j) ;
                }
            }
        }
    }




    int tableExits()
    {
        int result  ;
        // We Will Assume DB Name != "" Here Since We Will Check that in the Evaluation Method
        try
        {
            int fromIndeX = fromIndex() ;
            string tablePostFix = theQueryVector.at(fromIndeX + 1) ;
            string tableFileName  = databaseName+"-"+tablePostFix+".txt" ;
            const char *c = tableFileName.c_str();
            fstream checkedFile ;
            checkedFile.open(c) ;
            if (checkedFile)
            {
                // In Case It opened Then It Exists
                checkedFile.close() ;
                result = 1  ;
            }
            else
            {
                checkedFile.close() ;
                result =  0 ;
            }
            return result ;
        }
        catch (int dummy)
        {
            cout<<"Error From Table Naming"<<endl ;
        }
    }



    void evaluateTheSelection()
    {
        if (databaseName == "")
        {
            cout<<"Error ! Specify Database Name First , try USE KeyWord" <<endl ;
            return ;
        }
        if (queryIsShort() == 1 )
        {
            cout<<"Error ! Query is Short Or Wrong Syntax " <<endl ;
            return ;
        }

        if (hasFromClause() == 0 )
        {
         cout<<"Error ! Need From Clause " <<endl ;
            return ;
        }

        if (tableExits() == 0 )
        {
            cout<<"Error , No Table With This Name" <<endl ;
            return ;
        }

        fillAllTableColumnNames() ;
        fillQueryColumnNames() ;
        if (invalidColumnsInQuery() == 1)
        {
            cout<<"Error ! Query Does NOT match Column Names in Table " <<endl ;
            return ;
        }

        fillTheIndexes() ;


            int fromIndeX = fromIndex() ;
            string tablePostFix = theQueryVector.at(fromIndeX + 1) ;
            string tableFileName  = databaseName+"-"+tablePostFix+".txt" ;
            const char *c = tableFileName.c_str();
            fstream checkedFile ;
            checkedFile.open(c) ;

    while(!checkedFile.eof())
        {
            string lineInFile  = "" ;
            getline(checkedFile, lineInFile) ;
            vector<string>CurrentLineInTable = HelperStaticClass::vectorFromString(lineInFile) ;
            int i =  0 ;
           if (CurrentLineInTable.size() >= 1)
           {
            for (i ; i < theQueryIndexesVector.size(); i++)
            {
                int ind = theQueryIndexesVector.at(i) ;
                cout<<CurrentLineInTable.at(ind)<<"\t" ;
            }
            cout<<"\n" ;
           }

            if(checkedFile.eof())
            {
                checkedFile.close() ;
                break ;
            }
        }

    }





};

#endif // SELECTCLASS_H
