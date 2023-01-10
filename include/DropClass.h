#ifndef DROPCLASS_H
#define DROPCLASS_H
#include <iostream>
#include<vector>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include<string>
#include<HelperStaticClass.h>
#include<GeneralQuery.h>

class DropClass : public GeneralQuery
{
public:
    DropClass(string _theQuery,string _dataBaseName =""):GeneralQuery(_theQuery , _dataBaseName )
    {

    }

    void showDrop()
    {
        cout<<theQuery<<endl ;
    }
};

#endif // DROPCLASS_H
