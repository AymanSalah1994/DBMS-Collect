#ifndef CREATEQUERY_H
#define CREATEQUERY_H
#include <iostream>
#include<vector>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include<HelperStaticClass.h>
using namespace std;
class CreateQuery
{
private :
    vector<string> theQueryVector ;
    string theQuery  ;
public :
    string databaseName  ;
    CreateQuery(string _theQuery, string _dbName = "")
    {
        databaseName  = _dbName ;
        theQuery = _theQuery ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ",", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, "(", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ")", " ") ;
        HelperStaticClass::removeSpaces(theQuery) ;
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }

    void evaluateTheCreation()
    {
        if (HelperStaticClass::queryToUpper(theQueryVector.at(1)) == HelperStaticClass::queryToUpper("database") && HelperStaticClass::dbExists(databaseName) != 1)
        {
            fstream newFileObject  ;
            newFileObject.open("Databases.txt", ios::app) ;
            newFileObject<<theQueryVector.at(2)<<"\n" ;
            newFileObject.close() ;
            databaseName = theQueryVector.at(2)  ;
            cout<<"The Database "<<theQueryVector.at(2) ;
            cout<<" Created Successfully"<<endl ;
        }
        else if (HelperStaticClass::dbExists(databaseName) == 1 && HelperStaticClass::queryToUpper(theQueryVector.at(1)) == HelperStaticClass::queryToUpper("database") )
        {
            cout<<"Database Already Exists !"<<endl ;
            return ;
        }


        else if (HelperStaticClass::queryToUpper(theQueryVector.at(1)) == HelperStaticClass::queryToUpper("table"))
        {
            if (databaseName == "")
                {
                    cout<<"Please Specify a DB Name First"<<endl ;
                return ;
                }
            else
            {
                vector<string>types  ;
                vector<string>columnsNames ;
                string databaseName2 = databaseName ;
                string tableFileName = databaseName2.append("-").append(theQueryVector.at(2)).append(".txt") ;
                const char *c = tableFileName.c_str();
                //Those For Hoisting the Table
                int i  = 0  ;
                for (i ; i<theQueryVector.size(); i++)
                {
                    if (HelperStaticClass::queryToUpper(theQueryVector.at(i)) == HelperStaticClass::queryToUpper("int") || HelperStaticClass::queryToUpper(theQueryVector.at(i)) == HelperStaticClass::queryToUpper("varchar") )
                    {
                        cout<<"Type"<<theQueryVector.at(i)<<endl ;
                        types.push_back(HelperStaticClass::queryToUpper(theQueryVector.at(i))) ;
                    }
                    else if (theQueryVector.at(i) != "," && theQueryVector.at(i) != ";" && i>2 && !isdigit(theQueryVector.at(i)[0])  )
                    {
                        cout<<"Column"<<theQueryVector.at(i)<<endl ;
                        columnsNames.push_back(HelperStaticClass::queryToUpper(theQueryVector.at(i))) ;
                    }
                }

                if (columnsNames.size() == types.size())
                {
                    fstream newFileObject  ;
                    newFileObject.open(c, ios::out) ;
                    int j  =  0  ;
                    for (j ; j < columnsNames.size(); j++)
                    {
                        newFileObject<<columnsNames.at(j)<<" " ;
                    }
                    newFileObject<<"\n" ;
                    newFileObject.close() ;
                    cout<<"The Table "<<theQueryVector.at(2) ;
                    cout<<" Created Successfully"<<endl ;
                }
                else
                    cout<<"No matching size"<<endl ;
            }
        }

    }


};






#endif // CREATEQUERY_H
