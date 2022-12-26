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
        theQuery = HelperStaticClass::equalReplacer(theQuery, ";", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, "(", " ") ;
        theQuery = HelperStaticClass::equalReplacer(theQuery, ")", " ") ;
        HelperStaticClass::removeSpaces(theQuery) ; // Change is In Place , Using Reference
        if (databaseName != "")
        {
            HelperStaticClass::removeDigits(theQuery);
        }
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }





    int queryIsShort()
    {
        if (theQueryVector.size() < 3 )
            return 1  ;
        else
            return 0  ;
    }

    int dbAlreadExists ()
    {
        if (HelperStaticClass::queryToUpper(theQueryVector.at(1)) == HelperStaticClass::queryToUpper("database") && HelperStaticClass::dbExists(databaseName) == 1)
        {
            return 1 ;
        }
        else
            return 0 ;
    }


    void evaluateTheCreation()
    {

        if (queryIsShort() == 1)
            // Should Be the First thing to Check
        {
            cout<<"Query is Too Short to Handle !"<<endl ;
            return ; // This Will END the Evaluation
        }

        if (dbAlreadExists() == 1 )
        {
            cout<<"Database Already Exists ! " <<endl ;
            return ; // This Will END the Evaluation
        }




        if (HelperStaticClass::queryToUpper(theQueryVector.at(1)) == HelperStaticClass::queryToUpper("database") && dbAlreadExists() != 1)
        {
            fstream newFileObject  ;
            newFileObject.open("Databases.txt", ios::app) ;
            newFileObject<<theQueryVector.at(2)<<"\n" ;
            newFileObject.close() ;
            databaseName = theQueryVector.at(2)  ;
            cout<<"The Database "<<theQueryVector.at(2) ;
            cout<<" Created Successfully"<<endl ;
            return ;
        }



        if (HelperStaticClass::queryToUpper(theQueryVector.at(1)) == HelperStaticClass::queryToUpper("table"))
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
                try
                {
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
                    {
                        cout<<"No matching size"<<endl ;
                        throw 777 ;
                    }

                }
                catch(int numError)
                {
                    cout<<"Err Code 777" <<endl ;
                }
            }
        }

    }


};






#endif // CREATEQUERY_H
