#ifndef _H_COMMON_UTIL_H_
#define _H_COMMON_UTIL_H_
//File: RocketFind.h 
//Descriptions: provide some tools.
//Data: 2012-4-21
//Author: lyzhi
#include "CommonDefine.h"

//provide some command tools
class CommonUtils
{
public:

    //Show command tips at the command terminal
    static void ShowCmdTips();
    //Get the key word of input command
    static string GetCommandKeyWord(const string& strCmd);
    //Split input command to words, which is divided by space
    static vector<string> SplitCmd(const string& strCmd);
    //Write execute logs to log file
    static void WriteLog(const int iLine, const string& strClass, const string &strDesc = " ", const int& iRet = 0);
    //Do other process if the input command is not "find" command
    static void OtherProcess(string strCmdInput);
    //Get the current work path of this utility 
    static string GetCurrentWorkPath();
    
    //Make use of KMP algorith to implement the string match  
    static string::size_type DoKMPFind(const string& strSource, const string& strTarget);
    //get the next[] array of KMP
    static long GetKMPNext(const string& strPattern, string::size_type* iNext);      

    //Get the (sign,value) pair of expression parameters
    static void GetParaSignValue(const string& strExp, ENUM_SIGN_VALUE& enumSign, string& strParaValue);

    //Judge the string is filled with numbers or not 
    static bool isDigit(const string& str);
    //Get the format output of time
    static bool timeToString(const time_t& iTime, string& strTime);
};




#endif
