#ifndef _H_ROCKET_COMMON_H_
#define _H_ROCKET_COMMON_H_
//Description:create the right process task object according to the input command
#include "CommonDefine.h"
#include "RocketFindTask.h"

class CRocketCommonTask
{
public:
    CRocketCommonTask(string strInputCmd);
    ~CRocketCommonTask();

    //Get the key word of command
    void DeCodeCommand();

    //According to the command key word, transact the command. 
    ROCKET_ERRORCODE ProductFactory();

private:    
    string m_strInputCommand; //save the input command
    map<ENUM_CMD_KEY, string> m_mapCmdList; //map the <command keyword, input command>
    CRocketFindTask* m_pRocketFindTask; //
};

#endif
