#ifndef HELPERSTATICCLASS_H
#define HELPERSTATICCLASS_H
#include <iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;
class HelperStaticClass
{
public:
    static vector<string> vectorFromString(string userInput)
    {
        // A Function Takes String and Return a Vector
        string temporaryWord ;
        stringstream streamFromLine(userInput);
        vector<string> words;
        while(getline(streamFromLine, temporaryWord, ' '))
            // The Separator is ALWAYS a Space
        {
            words.push_back(temporaryWord);
        }
        return words ;
    }

    static string queryToUpper(string userInput)
    {
        // Takes any String "create" and Makes it Capital "CREATE"
        for(int i = 0; i < userInput.size(); i++)
        {
            // Looping Character By Character
            userInput.at(i) = toupper(userInput.at(i));
        }
        return userInput ;
    }

    static void removeDigits(string &myString)
    {
        char numberLiterals[] =  {'0','1','2','3','4','5','6','7','8','9'} ;
        int i =  0 ;
        for (i ;  i < sizeof(numberLiterals) ; i++)
        {
            myString.erase(remove(myString.begin(), myString.end(), numberLiterals[i]), myString.end());
            //remove A from string
        }
    }

    static void removeSpaces(string &str)
    {
        // A Function to Take a String and Remove ALL redundant spaces
        // n is length of the original string
        int n = str.length();
        // i points to next position to be filled in
        // output string/ j points to next character
        // in the original string
        int i = 0, j = -1;
        // flag that sets to true is space is found
        bool spaceFound = false;
        // Handles leading spaces
        while (++j < n && str[j] == ' ');
        // read all characters of original string
        while (j < n)
        {
            // if current characters is non-space
            if (str[j] != ' ')
            {
                // remove preceding spaces before dot,
                // comma & question mark
                if ((str[j] == '.' ||
                        str[j] == '?') && i - 1 >= 0 &&
                        str[i - 1] == ' ')
                    str[i - 1] = str[j++];

                else
                    // copy current character at index i
                    // and increment both i and j
                    str[i++] = str[j++];

                // set space flag to false when any
                // non-space character is found
                spaceFound = false;
            }
            // if current character is a space
            else if (str[j++] == ' ')
            {
                // If space is encountered for the first
                // time after a word, put one space in the
                // output and set space flag to true
                if (!spaceFound)
                {
                    str[i++] = ' ';
                    spaceFound = true;
                }
            }
        }
        // Remove trailing spaces
        if (i <= 1)
            str.erase(str.begin() + i, str.end());
        else
            str.erase(str.begin() + i - 1, str.end());
    }



    static string equalReplacer(string mainString, string replacedOne, string replacerOne )
    {
        // A Function Takes a String and The Two Symbols , One That is Currently In String
        // And the Other That We Want to replace with the Old One
        size_t pos;
        while ((pos = mainString.find(replacedOne)) != string::npos)
        {
            mainString.replace(pos, 1, replacerOne);
        }
        return mainString ;
    }


    static string stringFromVector(vector<string> vectorToString)
    {
        // A Function Takes a Vector and Return a string
        string finalString = "" ;
        int i =  0 ;
        for (i  ; i < vectorToString.size() ; i++)
        {
            finalString += vectorToString.at(i) ;
            if (i < vectorToString.size() - 1 )
            {
                finalString +=" " ;
            }
        }
        return finalString ;
    }

    static void updateFileData(const char *fileName,int conditionIndex, string conditionValue, int updateIndex, string updateValue )
    //FileName  , conditionIndex , conditionValue , updatedIndex , UpdatedValue
    //Update a File , Given A New Value and Its Index and the Condition Value and Its Index
    {
        ifstream oldFile; // Open the File First and Get all Of the Data in a Variable
        oldFile.open(fileName); //open the input file
        stringstream strStream;
        string oldLineFromStream ; //oldLineFromStream
        strStream << oldFile.rdbuf(); //read the file
        oldFile.close();

        fstream newFileObject  ; // OPen the Same File again and Write with New Data
        newFileObject.open(fileName,ios::out) ; // Here we Just Open it to Read Not Append
        while(getline(strStream, oldLineFromStream, '\n'))
        {
            vector<string>oldLineVector  = vectorFromString(oldLineFromStream) ;
            if (oldLineVector.at(conditionIndex) == conditionValue)
            {
                oldLineVector.at(updateIndex) = updateValue ;
                string oldLineStringAgain = HelperStaticClass::stringFromVector(oldLineVector) ;
                newFileObject<<oldLineStringAgain<<"\n" ;
            }
            else
            {
                string oldLineStringAgain = HelperStaticClass::stringFromVector(oldLineVector) ;
                newFileObject<<oldLineStringAgain<<"\n" ;
            }
        }
        newFileObject.close() ;
    }


    static int dbExists(string dbName)
    {
        // A Function that Checks if a DB Exists and Saved !
        int result =  0  ;
        ifstream DbFile;
        DbFile.open("Databases.txt");
        stringstream strStream;
        string dbNameThatExist ;
        strStream << DbFile.rdbuf(); //read the file
        DbFile.close();

        while(getline(strStream, dbNameThatExist, '\n'))
        {
            if (dbName == dbNameThatExist)
                result = 1 ;
        }
        return result ;
    }

};

#endif // HELPERSTATICCLASS_H
