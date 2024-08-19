#include "RocketCommonTask.h"
#include "CommonUtil.h"
#include "RocketFindTask.h"


/************************************************************************/
/* Function:Constructor                                                 */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
CRocketCommonTask::CRocketCommonTask(std::string strInputCmd)
:m_strInputCommand(strInputCmd)
{
    m_pRocketFindTask = NULL;
    //do some simple process to the input command.
    DeCodeCommand();
    
    //Call the corresponding class to process the command details
    ROCKET_ERRORCODE iRet = ProductFactory();
    {
        CommonUtils::WriteLog(__LINE__,"CRocketCommonTask::CRocketCommonTask()","ProductFactory",iRet);
    }
}

/************************************************************************/
/* Function:Destructor                                                  */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
CRocketCommonTask::~CRocketCommonTask()
{
    if (m_pRocketFindTask)
    {
        delete m_pRocketFindTask;
    }

}

/************************************************************************/
/* Function:Get the key word of command                                 */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
void CRocketCommonTask::DeCodeCommand()
{
    if (ROCKET_BLANK_STRING == m_strInputCommand)
    {
        return;
    }

    //get the fist word of command.
    string strCommandWord = CommonUtils::GetCommandKeyWord(m_strInputCommand);
    if (ROCKET_FIND_COMMAND == strCommandWord)
    {
        m_mapCmdList.insert(pair<ENUM_CMD_KEY,string>(enum_Key_Find, m_strInputCommand));
    }
    else
    {
        //other commands
        m_mapCmdList.insert(pair<ENUM_CMD_KEY,string>(enum_Key_Others, m_strInputCommand));
    }

    return;
}

/************************************************************************/
/* Function:According to the command key word, transact the command.    */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
ROCKET_ERRORCODE CRocketCommonTask::ProductFactory()
{
    ROCKET_ERRORCODE iRet = ROCKET_SUCCESS;
    if (m_mapCmdList.empty())
    {
        CommonUtils::ShowCmdTips();
        return iRet;
    }
    map<ENUM_CMD_KEY, string>::iterator iter = m_mapCmdList.begin();
    for (; iter != m_mapCmdList.end(); iter++)
    {
        switch(iter->first)
        {
        case enum_Key_Find:
            {
                m_pRocketFindTask = new CRocketFindTask(iter->second);
                iRet = m_pRocketFindTask->GetCommandInfo();
                {
                    CommonUtils::WriteLog(__LINE__,"CRocketCommonTask::ProductFactory()","GetCommandInfo",iRet);
                    CommonUtils::ShowCmdTips();
                    return iRet;
                }
                break;
            }

        case enum_Key_Others:
            {                
                CommonUtils::OtherProcess(iter->second);
                break;
            }

        default: break;
        }
    }
    CommonUtils::ShowCmdTips();

    return iRet;
}
