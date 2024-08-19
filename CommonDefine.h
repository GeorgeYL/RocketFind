#ifndef _H_COMMON_DEFINE_H_
#define _H_COMMON_DEFINE_H_
//File: RocketFind.h 
//Descriptions: 
//Data: 2012-4-21
//Author: lyzhi
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

#define ROCKET_DAY_SECONDS 86400 //60(seconds)*60(minutes)*24(hours)

#define MAX_PATH 260

#define ROCKET_ERRORCODE int 
#define ROCKET_SUCCESS 0
#ifndef NULL
#define NULL 0
#endif
#define ROCKET_BLANK_STRING ""
#define ROCKET_EXIT "exit"
#define ROCKET_QUIT_1 "quit"
#define ROCKET_QUIT_2 "q"


#define COMMAND_WITHOUT_PARAMETER 1

//define the command options
#define ROCKET_FIND_COMMAND    "find"
#define ROCKET_FIND_PATH       "path"
#define OPTION_COMMAND_LEVEL "-level"
#define OPTION_COMMAND_MTIME "-mtime"
#define OPTION_COMMAND_NAME "-name"
#define OPTION_COMMAND_SIZE "-size"
#define OPTION_COMMAND_TEXT "-text"

#define COMMAND_SIZE_UNIT_K "k"
#define COMMAND_SIZE_UNIT_M "m"

#define ROCKET_CURRENT_PATH "."

#define ROCKET_FIND_EXP_SIGN_BIG '+'
#define ROCKET_FIND_EXP_SIGN_SMALL '-'
#define ROCKET_FIND_EXP_SIGN_EQUAL '='
enum ENUM_SIGN_VALUE
{    
    enum_SIGN_SMALL = -1,
    enum_SIGN_EQUAL = 0,
    enum_SIGN_BIG = 1,
    enum_SIGN_OTHER = 2,
};


enum ENUM_CMD_PARA
{
    enum_Find_Command =1,
    enum_Find_Path,
    enum_Find_Exp_Level,
    enmu_Find_Exp_Mtime,
    enum_Find_Exp_Name,
    enum_Find_Exp_Size,
    enum_Find_Exp_Text,
};
//enum of command type
enum ENUM_CMD_KEY
{
    enum_Key_Find =1,
    enum_Key_Others =2,
};




//para-value pair of command
struct CMD_PARA 
{
    ENUM_CMD_PARA enumParaType;
    pair<ENUM_SIGN_VALUE, string> pairParaValue;
};

//struct CMD_INPUT
//{
//    string strInputCommand;
//    string strCurrentPath;
//
//    CMD_INPUT(string strCmd, string strPath)
//    {
//        strInputCommand = strCmd;
//        strCurrentPath = strPath;
//    }
//};

typedef vector<CMD_PARA> CMD_DATA_VALUE;

//Error Code
#define ERR_COMMAND 100

struct CMD_FIND_DATA
{
    string strLevelSig;
    string strTimeSig;
    string strSizeSig;

    int iLevelNum;
    string strTime;
    string strFileName;
    int iSizeNum;
    string strTextString;    
};


#endif
