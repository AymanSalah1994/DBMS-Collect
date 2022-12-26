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
public:
    SelectClass(string _theQuery,string _dataBaseName ="")
    {
        _dataBaseName = databaseName   ;
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
                checkedFile.close() ;
                result = 1  ;
            }
            else
            {
                checkedFile.close() ;
                return 0 ;
            }
            return result ;
        }
        catch (int dummy)
        {
            cout<<"Error From Table Naming"<<endl ;
        }
    }





};

#endif // SELECTCLASS_H
