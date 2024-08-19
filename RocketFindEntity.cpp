//RocketFindEntity.cpp
//used for parse the command and verify it

#include "RocketFindEntity.h"
#include "CommonDefine.h"
#include "CommonUtil.h"
#include <iostream>
#include <direct.h>
#include <ctime>
using namespace std;

/************************************************************************/
/* Function:Constructor                                                 */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
CRocketFindEntity::CRocketFindEntity(CMD_DATA_VALUE cmdParaValue)
{
    m_oCmdParaValue = cmdParaValue;
}

/************************************************************************/
/* Function:Destructor                                                  */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
CRocketFindEntity::~CRocketFindEntity()
{

}

/************************************************************************/
/* Function: Construct the conditions for the find command              */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
ROCKET_ERRORCODE CRocketFindEntity::executeCmd(const CMD_DATA_VALUE& cmdParaValue)
{
    string strCondition = ROCKET_BLANK_STRING;    
    string strFindPath = ROCKET_BLANK_STRING;
    string strFindName = "*.*"; //set the default file to find;
    string strPatterText = ROCKET_BLANK_STRING; //-text "XXX"
    int iMTime = 0;
    ENUM_SIGN_VALUE enumMTSign = enum_SIGN_OTHER; //record the time sign
    ENUM_SIGN_VALUE enumSizeSign = enum_SIGN_OTHER; //file size sign
    time_t lFileModifyTime = 0; //record the time point which is a border. 
                              //The file modify time is before(sign is plus) or latter( sign is minus) than it  

    long lFindSize = -1; // the size file want to find.

    ROCKET_ERRORCODE iRet = ROCKET_SUCCESS;

    for (CMD_DATA_VALUE::size_type i= 0 ;i < cmdParaValue.size() ;i++)
    {
        //cout << cmdParaValue[i].enumParaType << " : " << cmdParaValue[i].pairParaValue.first<< ":"<< cmdParaValue[i].pairParaValue.second <<endl; 

        if ((enum_Find_Exp_Level == cmdParaValue[i].enumParaType) ||
            (enmu_Find_Exp_Mtime == cmdParaValue[i].enumParaType))
        {
            bool bDigit = CommonUtils::isDigit(cmdParaValue[i].pairParaValue.second);

            if (!bDigit)
            {
                CommonUtils::WriteLog(__LINE__ , "CRocketFindEntity::executeCmd() ","CommonUtils::isDigit", ERR_COMMAND);
                return ERR_COMMAND;
            }
        }

        //path
        if (enum_Find_Path == cmdParaValue[i].enumParaType)
        {
            strFindPath = cmdParaValue[i].pairParaValue.second;
        }
        //name
        if (enum_Find_Exp_Name == cmdParaValue[i].enumParaType)
        {
            strFindName = cmdParaValue[i].pairParaValue.second;
        }

        //level +number
        //I don't know what the level mean. so this parameter is not implement

        //mtime: if the sign is plus : find the older file
        //if the sign is minus: find the newer file
        if (enmu_Find_Exp_Mtime == cmdParaValue[i].enumParaType)
        {
            time_t tNow = time(NULL);
            //cout << tNow <<endl;
            string strTime=ROCKET_BLANK_STRING;
            CommonUtils::timeToString(tNow, strTime);
            //cout<< strTime <<endl;            
            lFileModifyTime = tNow - atol(cmdParaValue[i].pairParaValue.second.c_str()) * (ROCKET_DAY_SECONDS);
            enumMTSign = cmdParaValue[i].pairParaValue.first;            
        }

        //size
        if (enum_Find_Exp_Size == cmdParaValue[i].enumParaType)
        {
            //judge the appendix of size is K or M
            if ((-1 != cmdParaValue[i].pairParaValue.second.find("k")) ||
                (-1 != cmdParaValue[i].pairParaValue.second.find("K")))
            {
                //cout << cmdParaValue[i].pairParaValue.second <<endl;
                enumSizeSign = cmdParaValue[i].pairParaValue.first;
                //get the string before last character, it will be k/K/m/M or nothing
                string strSize = cmdParaValue[i].pairParaValue.second.substr(0,cmdParaValue[i].pairParaValue.second.size() -1);
                if (CommonUtils::isDigit(strSize))
                {
                    lFindSize = atol(strSize.c_str()) * 1024;
                }
                else
                {
                    CommonUtils::WriteLog(__LINE__ , "CRocketFindEntity::executeCmd() ","CommonUtils::isDigit", ERR_COMMAND);
                    return ERR_COMMAND;
                }

            }
            else if ((-1 !=cmdParaValue[i].pairParaValue.second.find("m")) ||
                (-1 != cmdParaValue[i].pairParaValue.second.find("M")))
            {
                //cout << cmdParaValue[i].pairParaValue.second <<endl;
                enumSizeSign = cmdParaValue[i].pairParaValue.first;
                string strSize = cmdParaValue[i].pairParaValue.second.substr(0,cmdParaValue[i].pairParaValue.second.size() -1);
                if (CommonUtils::isDigit(strSize))
                {
                    lFindSize = atol(strSize.c_str()) * 1024 *1024; //compute the size of file. MB
                }
                else
                {
                    CommonUtils::WriteLog(__LINE__ , "CRocketFindEntity::executeCmd() ","CommonUtils::isDigit", ERR_COMMAND);
                    return ERR_COMMAND;
                }
            }
            else
            {
                //cout << cmdParaValue[i].pairParaValue.second <<endl;
                enumSizeSign = cmdParaValue[i].pairParaValue.first;
                string strSize = cmdParaValue[i].pairParaValue.second;
                if (CommonUtils::isDigit(strSize))
                {
                    lFindSize = atol(strSize.c_str()) * 1024; //compute the file bytes: default unit is KB
                }
                else
                {
                    CommonUtils::WriteLog(__LINE__ , "CRocketFindEntity::executeCmd() ","CommonUtils::isDigit", ERR_COMMAND);
                    return ERR_COMMAND;
                }
            }

        }// end of size parameter

        //-text "good"
        if (enum_Find_Exp_Text == cmdParaValue[i].enumParaType)
        {
            strPatterText = cmdParaValue[i].pairParaValue.second;
        }
      
    }
    //list all files at current directory
    ListFileInfo(strFindPath, strFindName, enumMTSign, lFileModifyTime, enumSizeSign,lFindSize, strPatterText);
    //ListFileWithText(strFindPath,strFindName);


    //string strSource = "122goodmorning verryone movieifirocketle";
    //string strTarget ="ifirocketl";
    //string::size_type lPOs = CommonUtils::DoKMPFind(strSource,strTarget);
    //cout <<"find gde:" << lPOs <<endl;
    return iRet;
}

/************************************************************************/
/* Function:List the find result                                        */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
ROCKET_ERRORCODE CRocketFindEntity::ListFileInfo(const string& strPath, const string& strFileName, 
                                                 const ENUM_SIGN_VALUE& enumMTSign, const time_t& lMTime,
                                                 const ENUM_SIGN_VALUE& enumSizeSign, const long& lFileSize,
                                                 const string& strPatternText)
{    
   // _chdir(strPath.c_str());
    cout <<endl << "Current Path: " << strPath <<endl;
    string strTargetFile = strPath + strFileName; 
    string strSubTarget = strPath + "*.*"; //����������Ŀ¼
    //cout <<endl << "Current Path: " << strTargetFile <<endl;
    string strTmpFormatTime = ROCKET_BLANK_STRING; //Temp variable for the format time
    _finddata_t file;
    intptr_t lf;
    if((lf = _findfirst(strTargetFile.c_str(), &file))==-1l)//_findfirst���ص���long��; long __cdecl _findfirst(const char *, struct _finddata_t *)
        cout<<"File was not found!" << endl;
    else
    {
        cout<<"File List:" <<endl;
        cout<<left<<setw(20)<< "Modify Time" << "  " <<setw(8)<< "Size(B)" << "  " ;
        cout<<"File Name" << endl;
        do//int __cdecl _findnext(long, struct _finddata_t *);����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1
        {            
            //filter file with modify time
            if (enum_SIGN_BIG == enumMTSign)
            {
                //file's modify time should be older than the border
                if ((file.time_write <= lMTime) && (file.attrib != _A_SUBDIR) )
                {
                    //filter file with size
                    if (enum_SIGN_BIG == enumSizeSign)
                    {
                        if (file.size >= lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);                             
                        }
                    }
                    else if (enum_SIGN_SMALL == enumSizeSign) 
                    {
                        if (file.size <= lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else if (enum_SIGN_EQUAL == enumSizeSign )
                    {
                        if (file.size == lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else
                    {
                       //the parameter without size condition
                        DoStringMatch(strPath, file, strPatternText);
                    }//end filter size
                }
            }
            else if (enum_SIGN_SMALL == enumMTSign) 
            {
                //file's modify time is at the scope from now to +XX days before
                if ((file.time_write >= lMTime) && (file.attrib != _A_SUBDIR) )
                {
                    //filter file with size
                    if (enum_SIGN_BIG == enumSizeSign)
                    {
                        if (file.size >= lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText); 
                        }
                    }
                    else if (enum_SIGN_SMALL == enumSizeSign) 
                    {
                        if (file.size <= lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else if (enum_SIGN_EQUAL == enumSizeSign )
                    { 
                        DoStringMatch(strPath, file, strPatternText);
                    }
                    else
                    {
                        //the parameter without size condition
                        DoStringMatch(strPath, file, strPatternText);
                    }//end filter size
                    
                }
            }
            else if (enum_SIGN_EQUAL == enumMTSign)
            {
                //file's modify time is in the scope from +XX days to XX Days+1 
                //older than XXDays and newer XX Days +1
                if ((file.time_write <= lMTime) && 
                    (file.time_write > (lMTime - ROCKET_DAY_SECONDS)) && 
                    (file.attrib != _A_SUBDIR))
                {
                    //filter file with size
                    if (enum_SIGN_BIG == enumSizeSign)
                    {
                        if (file.size >= lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else if (enum_SIGN_SMALL == enumSizeSign) 
                    {
                        if (file.size <= lFileSize)
                        {
                           DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else if (enum_SIGN_EQUAL == enumSizeSign )
                    {
                        if (file.size == lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else
                    {
                        //the parameter without size condition
                        DoStringMatch(strPath, file, strPatternText);
                    }//end filter size
                    
                }//end modify time           
            }
            else
            {
                //List all file modified at any time
                if (file.attrib != _A_SUBDIR)
                {
                    //filter file with size
                    if (enum_SIGN_BIG == enumSizeSign)
                    {
                        if (file.size >= lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else if (enum_SIGN_SMALL == enumSizeSign) 
                    {
                        if (file.size <= lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else if (enum_SIGN_EQUAL == enumSizeSign )
                    {
                        if (file.size == lFileSize)
                        {
                            DoStringMatch(strPath, file, strPatternText);
                        }
                    }
                    else
                    {
                        //the parameter without size condition
                        DoStringMatch(strPath, file, strPatternText);

                    }//end filter size                    
                }
            }

        }while( _findnext( lf, &file ) == 0 );
    }             
    _findclose(lf);

    //Access the sub folder
    //_chdir(strPath.c_str());
    if((lf = _findfirst(strSubTarget.c_str(), &file)) != -1l)
    {
        do//int __cdecl _findnext(long, struct _finddata_t *);����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1
        {
            //cout<<file.name;
            if(file.attrib == _A_SUBDIR)
            {
                //cout<<" <DIR>  ";
                //if not current directory or parent directory, then access the sub folder
                if (strcmp(file.name,".") != 0 && strcmp(file.name,"..") != 0)
                {
                    string strSubPath = strPath + file.name + "\\";
                    ListFileInfo(strSubPath, strFileName,enumMTSign, lMTime, enumSizeSign,lFileSize, strPatternText);
                }
            }            
        }while( _findnext( lf, &file ) == 0 );

    }    
    _findclose(lf);
    
    return ROCKET_SUCCESS;
}

/************************************************************************/
/* Function:Filter the file whether it has the "-text" key word         */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
bool CRocketFindEntity::ListFileWithText(const string& strFileName, const string& strPatternText)
{

    //string strPattern = "Rocket";
    char buff[BUFFER_SIZE];

    //string filename= strFileName;

    ifstream ifFileIn(strFileName.c_str(),ios::in | ios::binary);

    if(!ifFileIn)
    {
        cout<<"Could not open file: "<<endl;
        CommonUtils::WriteLog(__LINE__ , "CRocketFindEntity::ListFileWithText",string("Could not open the file") + strFileName, 0);
        return false;
    }

    long readPosition = 0;
    while(!ifFileIn.eof())
    {
        ifFileIn.seekg(readPosition);
        ifFileIn.read((char*)buff,BUFFER_SIZE);
        string strMain;
        strMain.assign(buff);
        long lPos = CommonUtils::DoKMPFind(strMain, strPatternText);
        if (-1 != lPos)
        {
            //if find the key word, return true
            ifFileIn.clear();
            ifFileIn.close();  
            //cout << "Find Position:" << lPos <<endl;
            CommonUtils::WriteLog(__LINE__ , "CRocketFindEntity::ListFileWithText","CommonUtils::DoKMPFind", lPos);
            return true;
        }    
        long buffsize = ifFileIn.gcount();

        //Consider the pattern_str may be at border of the buffer area.
        //The next buffer should be retreat the pattern_str size
        readPosition = (readPosition+ buffsize)- strPatternText.size(); //
    }
    ifFileIn.clear();
    ifFileIn.close();

    return false;
}

/************************************************************************/
/* Function:According to the pattern text, filter the files             */
/* Input:                                                               */
/* Output:                                                              */
/* Return:                                                              */
/* Date:                                                                */
/************************************************************************/
void CRocketFindEntity::DoStringMatch(const string& strPath, const _finddata_t& file, const string& strPatternText)
{
    string strTmpFormatTime = ROCKET_BLANK_STRING; //Temp variable for the format time   
    if (ROCKET_BLANK_STRING != strPatternText)
    {
        string strPatternFile = strPath + file.name;        
        if (true == ListFileWithText(strPatternFile, strPatternText))
        {
            CommonUtils::WriteLog(__LINE__ , "CRocketFindEntity::DoStringMatch()","ListFileWithText", false);            
            CommonUtils::timeToString(file.time_write, strTmpFormatTime);
            cout<<left<<setw(20)<< strTmpFormatTime << "  " <<setw(8)<< file.size << "  " ;
            cout<<file.name << endl;
        }
    }
    else
    {
        CommonUtils::WriteLog(__LINE__ , "CRocketFindEntity::DoStringMatch()","ListFileWithText", false);
        CommonUtils::timeToString(file.time_write, strTmpFormatTime);
        cout<< left << setw(20) <<strTmpFormatTime << "  " <<setw(8)<< file.size << "  " ;
        cout<<file.name << endl;
    }

    return;
}

