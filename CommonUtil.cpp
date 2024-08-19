//File: CommonUtils.h 
//Descriptions: provide some tools.
//Data: 2012-4-21
//Author: lyzhi
#include <iostream>
#include <direct.h>
#include "CommonUtil.h"
using namespace std;

/************************************************************************/
/* Function:Show Command Tips                                           */
/* Input:                                                               */
/* Output:                                                              */
/* Return:void                                                          */
/* Date:                                                                */
/************************************************************************/
void CommonUtils::ShowCmdTips()
{
    cout << "<RocketFind>:";
}

/************************************************************************/
/* Function:Split the input command to words, and save them to vector   */
/* Input:string of input command                                        */
/* Output:                                                              */
/* Return:vector: parameter vector                                      */
/* Date:                                                                */
/************************************************************************/
vector<string> CommonUtils::SplitCmd(const string& strCmd)
{ 
    vector<string> retCmd;                                                                                                                     
    string::size_type iWordStart = 0;                                                                           

    // invariant: we have processed characters [original value of i, i)                          
    while (iWordStart != strCmd.size()) 
    {                                                                      

        // ignore leading blanks                
        while (iWordStart !=strCmd.size() && iswspace(strCmd[iWordStart])) 
        {
            ++iWordStart;
        }
            
        // find end of next word                                                                 
        string::size_type iPos = iWordStart;                                                                       
        // invariant: none of the characters in rang [original j, current j) is a space          
        while (iPos != strCmd.size() && !iswspace(strCmd[iPos]))  
        {
            ++iPos;
        }
        
        // if we found some one with space characters                                             
        if (iWordStart != iPos) 
        {                                                                            
            // copy from strCmd starting at iBlankCount and taking iPos - iBlankCount chars                                  
            retCmd.push_back(strCmd.substr(iWordStart, iPos - iWordStart));                                                   
            iWordStart = iPos;                                                                               
        }                                                                                        
    }                                                                                            
    return retCmd;                                                                              
}


/************************************************************************/
/* Function:Get the keyword of input command                            */
/* Input:string of input command                                        */
/* Output:                                                              */
/* Return:string: the keyword of input command(always is the first word)*/
/* Date:                                                                */
/************************************************************************/
string CommonUtils::GetCommandKeyWord(const std::string &strCmd)
{
                                                                                                                        
    string::size_type iWordStart = 0; 
    string strCmdKey = ROCKET_BLANK_STRING;

    // ignore leading blanks                
    while (iWordStart !=strCmd.size() && iswspace(strCmd[iWordStart])) 
    {
        ++iWordStart;
    }

    // find end of next word                                                                 
    string::size_type iPos = iWordStart;                                                                       
    // invariant: none of the characters in rang [original j, current j) is a space          
    while (iPos != strCmd.size() && !iswspace(strCmd[iPos]))  
    {
        ++iPos;
    }

    // if we found some nonewithspace characters                                             
    if (iWordStart != iPos) 
    {
        // copy from strCmd starting at iBlankCount and taking iPos - iBlankCount chars                                  
        strCmdKey = strCmd.substr(iWordStart, iPos - iWordStart); 
    }   

    return strCmdKey;

}

/************************************************************************/
/* Function:The process of input command is not "find"                  */
/* Input:                                                               */
/* Output:                                                              */
/* Return:void                                                          */
/* Date:                                                                */
/************************************************************************/
void CommonUtils::OtherProcess(string strCmdInput)
{
    //judge the input command is empty or not
    if (ROCKET_BLANK_STRING == strCmdInput)
    {
        CommonUtils::ShowCmdTips();
        return ;
    }

    //judge the command is exit or quit or "q"
    if ((ROCKET_EXIT == strCmdInput)   || \
        (ROCKET_QUIT_1 == strCmdInput) || \
        (ROCKET_QUIT_2 == strCmdInput))
    {
        exit(0);
    }
    //others let the system process
    system(strCmdInput.c_str());
}

/************************************************************************/
/* Function:GetCurrent Work path                                        */
/* Input:                                                               */
/* Output:                                                              */
/* Return:string -Current work path                                     */
/* Date:                                                                */
/************************************************************************/
string CommonUtils::GetCurrentWorkPath()
{
    string strCurrentWorkPath = ROCKET_BLANK_STRING;
    char* pbuffer;
    //Get Current work path
    pbuffer = _getcwd( NULL, 0 );
    if( NULL == pbuffer )
    {
        return strCurrentWorkPath;
    }
    else
    {
        strCurrentWorkPath.assign(pbuffer);
        free(pbuffer); 
    }
    //if workpath is not end of '\', add it at the end.
    if ('\\' != strCurrentWorkPath[strCurrentWorkPath.size()-1])
    {
        strCurrentWorkPath += "\\";
    }
    return strCurrentWorkPath;
}

/************************************************************************/
/* Function:Write logs                                                  */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
void CommonUtils::WriteLog(const int iLine, const string& strClass, const string &strDesc /* =  */, const int& iRet /* = 0 */)
{
    ////Write to Log
    //FILE* pF_log;
    //errno_t err;
    //err = fopen_s(&pF_log, "d:\\Rocket\\RocketFind_log.log", "a");
    //if (NULL != err)
    //{
    //    //OutputDebugString("Log file open failed.");  
    //    return;
    //}

    //string strNowTime;
    //time_t nowTime;
    //nowTime = time(NULL);
    //
    //
    //fprintf(pF_log, "[%s]\n",strLog.c_str());
    //fclose(pF_log);

    //get current work path
    string strLogPath = GetCurrentWorkPath();
    
    time_t tNow = time(NULL);
    string strNow;
    timeToString(tNow, strNow);
    //get the full path of log file. 
    strLogPath = strLogPath + "RocketFind_" + strNow.substr(0, strNow.find(" ")) + ".log";

    //write the logs
    ofstream outLog(strLogPath.c_str(), ofstream::out | ofstream::app);
    outLog << "[" << strNow << "] " <<"Line:" << iLine << ", " << strClass;
    outLog << ", " << strDesc << ", Return Code = " << iRet <<endl;
    outLog.clear();
    outLog.close();
        
}

/************************************************************************/
/* Function:Do string match with KMP algorithm                          */
/* Input:strSource The main string                                      */
/* Input:strTarget: The string want to find at file                     */
/* Output:                                                              */
/* Return: the position of string to be found                           */
/* Date:                                                                */
/************************************************************************/
string::size_type CommonUtils::DoKMPFind(const string& strSource,const string& strTarget)
{    
    //string::size_type next[100]; //save the next
    string::size_type *next = new string::size_type[strTarget.length()+1];
   
    GetKMPNext(strTarget, next);
    int i= 0,j=0;
    int len1=strSource.length(),len2=strTarget.length();
    while((i<len1)&&(j<len2))
    {
        if((j==-1)||(strSource[i]==strTarget[j])) 
        {
            j++;
            i++;
        }
        else 
        {
            j = next[j];
        }
    }

    delete next;

    if(j==len2) return i-len2;
    else return -1;
}

/************************************************************************/
/* Function:Get the "Next" arrary of KMP algorithm                      */
/* Input:strPattern: string want to be matched                          */
/* Input:iNext: the pointer to the start address of "Next" array        */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
long CommonUtils::GetKMPNext(const string& strPattern, string::size_type* iNext)
{
    //memset(iNext,0,sizeof(iNext));
    string::size_type i=-1,j = 0;
    iNext[0] = -1;
    while(j < strPattern.size())
    {
        if(i==-1||strPattern[i]==strPattern[j])
        {
            i++;  j++;  
            iNext[j] = i;
        }
        else 
        {
            i=iNext[i];
        } 
        //cout <<"iNext["<< j <<"]"<< iNext[j] << endl;
    }

    return 0;
}

/************************************************************************/
/* Function:Get the (sign,value) pair of expression parameters          */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
void CommonUtils::GetParaSignValue(const std::string &strExp, ENUM_SIGN_VALUE &enumSign, std::string &strParaValue)
{  
    if( 0 >= strExp.size())
    {
        CommonUtils::WriteLog(__LINE__,"CommonUtils::GetParaSignValue()","the size of command expression is 0.");
        return ;
    }

    //if the path is . then use the full path.
    if (ROCKET_CURRENT_PATH == strExp)
    {
        enumSign = enum_SIGN_EQUAL;
        strParaValue = CommonUtils::GetCurrentWorkPath();
        CommonUtils::WriteLog(__LINE__,"CommonUtils::GetParaSignValue()","GetCurrentWorkPath().");
        return ;
    }

    if ( ROCKET_FIND_EXP_SIGN_BIG == strExp[0])
    {
        enumSign = enum_SIGN_BIG;
        strParaValue = strExp.substr(1, strExp.size() -1);
    }
    else if (ROCKET_FIND_EXP_SIGN_SMALL == strExp[0])
    {
        enumSign = enum_SIGN_SMALL;
        strParaValue = strExp.substr(1, strExp.size() -1);
    }
    else if ((ROCKET_FIND_EXP_SIGN_EQUAL == strExp[0]))
    {
        enumSign = enum_SIGN_EQUAL;
        strParaValue = strExp.substr(1, strExp.size() -1);
    }
    else
    {
        //The first is not a sign.
        enumSign = enum_SIGN_EQUAL;
        strParaValue = strExp;
    }    

    return;
}

/************************************************************************/
/* Function:Judge the string is filled with numbers or not              */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
bool CommonUtils::isDigit(const string &str)
{
    for (string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if (!::isdigit(*it))
        {
            return false;
        }
    }
    return true;
}

/************************************************************************/
/* Function:Get the format output of time                               */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
bool CommonUtils::timeToString(const time_t& iTime, string& strTime)
{
    char str_time[100];  
    struct tm tmLocalTime;  
    errno_t err = localtime_s(&tmLocalTime, &iTime); 
    if (ROCKET_SUCCESS != err)
    {
        return false;
    }
    //asctime_s(str_time, 100, &tmLocalTime);    
    strftime(str_time, 100, "%Y-%m-%d %H:%M:%S", &tmLocalTime);  
    strTime.assign(str_time); 
    return true;  
}

