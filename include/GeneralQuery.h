#ifndef GENERALQUERY_H
#define GENERALQUERY_H
#include <iostream>
#include<vector>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include<string>
#include<HelperStaticClass.h>

class GeneralQuery
{
protected :
    string databaseName  ;
    string theQuery  ;
    vector<string> theQueryVector ;
public :
    GeneralQuery(string _theQuery,string _dataBaseName ="")
    {
        databaseName = _dataBaseName ;
        theQuery = _theQuery ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ",", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ";", " ") ;
        HelperStaticClass::removeSpaces(theQuery) ;
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }



};

#endif // GENERALQUERY_H
