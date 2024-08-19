#ifndef _H_ROCKET_FIND_TASK_H_
#define _H_ROCKET_FIND_TASK_H_
//File: RocketFind.h 
//Descriptions: provide some tools.
//Data: 2012-4-21
//Author: lyzhi

#include "CommonDefine.h"

class CRocketFindTask
{
public:
    CRocketFindTask(string strInputCmd);
    ~CRocketFindTask();

    //Parse the command parameters and execute command. 
    ROCKET_ERRORCODE GetCommandInfo();

    //parse the input command and save parameters at vector
    void CommandParse(const string& strCmd);

private:
    string m_strInputCmd; //The command inputted by user.
    CMD_DATA_VALUE m_vecCmdDataValue; //vector to save the command parameter-value pairs: map(key word,<sign,value>)  
    
};




#endif
