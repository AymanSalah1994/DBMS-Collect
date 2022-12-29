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
        theQueryVector = HelperStaticClass::vectorFromString(theQuery) ;
    }

    void evaluateDlete()
    {
        string tableFileName = databaseName+"-"+theQueryVector.at(2)+".txt" ;
        const char *table = tableFileName.c_str();
        ifstream checkedFile  ;
        checkedFile.open(table) ;
        if (checkedFile)
        {
            cout<<"File is There "<<endl  ;
            if(theQueryVector.size() == 3)
            {
                checkedFile.close() ;
                remove(table);
                cout <<table << endl;
                cout << "Table delete succeffuly";
                return;
            }
            else
            {
                ofstream temp;
                temp.open("temp.txt");
                vector<string>numberOfColumn  ; // From the File
                vector<string>valuesOfColumns ; // From the File
                string lineOfTable ;
                getline(checkedFile, lineOfTable);
                temp << lineOfTable << std::endl;
                getline(checkedFile, lineOfTable);
                temp << lineOfTable << std::endl;
                numberOfColumn = HelperStaticClass::vectorFromString(lineOfTable);
                valuesOfColumns =HelperStaticClass::vectorFromString(lineOfTable);
                int index;
                for(int i=0 ; i<numberOfColumn.size() ; i++)
                {
                    if (HelperStaticClass::queryToUpper(theQueryVector.at(4)) == HelperStaticClass::queryToUpper(numberOfColumn.at(i)))
                    {
                        index = i;
                        break;
                    }
                }

                while(getline(checkedFile, lineOfTable))
                {
                    valuesOfColumns = HelperStaticClass::vectorFromString(lineOfTable);
                    if(valuesOfColumns.at(index) != theQueryVector.at(6))
                    {
                        temp << lineOfTable << std::endl;
                    }
                }

                temp.close();
                checkedFile.close();
                const char * p = tableFileName.c_str();
                /*
                remove(p);
                rename("temp.txt", p);
                 cout << "records succeffuly delete";
                */
            }

        }
        else
        {
            cout<<"There is NO file"<<endl ;
            cout<<tableFileName ;
            return ; // This Will NOT continue the Function
        }

    }

};


#endif // DELETECLASS_H
