//
#include <iostream>
#include "RocketFindTask.h"
#include "CommonDefine.h"
#include "CommonUtil.h"
#include "RocketFindEntity.h"
using namespace std;

/************************************************************************/
/* Function:construct of class CRocketFindTask                          */
/* Input: strInputCmd  the input command string                         */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
CRocketFindTask::CRocketFindTask(std::string strInputCmd)
:m_strInputCmd(strInputCmd)
{       
}

/************************************************************************/
/* Function:destruct of class CRocketFindTask                           */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
CRocketFindTask::~CRocketFindTask()
{
}

/************************************************************************/
/* Function:Parse the command parameters and execute command.           */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
ROCKET_ERRORCODE CRocketFindTask::GetCommandInfo()
{
    ROCKET_ERRORCODE iRet = ROCKET_SUCCESS;
    
    //parse the command and save the parameters to Vector: map(key, <sign, value>)   
    CommandParse(m_strInputCmd);
    
    //Verify the command and execute it
    CRocketFindEntity oEntity(m_vecCmdDataValue);
    iRet = oEntity.executeCmd(m_vecCmdDataValue);
    if (ROCKET_SUCCESS != iRet)
    {
        CommonUtils::WriteLog(__LINE__,"CRocketFindTask::GetCommandInfo()","executeCmd",iRet);
        return iRet;
    }
    if (m_vecCmdDataValue.empty())
    {
        return ROCKET_SUCCESS;
    }
    
    return ROCKET_SUCCESS;

}

/************************************************************************/
/* Function:parse the input command and save parameters at vector       */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/
void CRocketFindTask::CommandParse(const string& strCmd)
{
    vector<string> VecCmd;
    string strTmpCmd(strCmd);
    CMD_PARA cmdParaValue;

    //Split the command to words by blank, save the command words to Vector
    VecCmd = CommonUtils::SplitCmd(strTmpCmd);

    //the key word "find" must at Vector, else the input is error.
    if (VecCmd.size() > 0 && (ROCKET_FIND_COMMAND == VecCmd[0]))
    {       
        //mapCmdInfo[ROCKET_FIND_COMMAND] = VecCmd[0];
        cmdParaValue.enumParaType = enum_Find_Command;
        CommonUtils::GetParaSignValue(VecCmd[0], cmdParaValue.pairParaValue.first, cmdParaValue.pairParaValue.second);
        m_vecCmdDataValue.push_back(cmdParaValue);
    }
    //Command Path is at Vector[1]
    if (VecCmd.size() > 1)
    {
        //mapCmdInfo[ROCKET_FIND_COMMAND] = VecCmd[0];
        cmdParaValue.enumParaType = enum_Find_Path;
        CommonUtils::GetParaSignValue(VecCmd[1], cmdParaValue.pairParaValue.first, cmdParaValue.pairParaValue.second);
        m_vecCmdDataValue.push_back(cmdParaValue);
    }

    //get the parameters of the last expression
    for (vector<string>::size_type iPos = 2; (VecCmd.size() > 2) && (iPos != VecCmd.size()); ++iPos)
    {

        if ((iPos +1) < VecCmd.size())
        {

            if (OPTION_COMMAND_LEVEL == VecCmd[iPos])
            {
                cmdParaValue.enumParaType = enum_Find_Exp_Level;
                CommonUtils::GetParaSignValue(VecCmd[iPos+1], cmdParaValue.pairParaValue.first, cmdParaValue.pairParaValue.second);
                m_vecCmdDataValue.push_back(cmdParaValue);

            }

            if (OPTION_COMMAND_MTIME == VecCmd[iPos])
            {
                cmdParaValue.enumParaType = enmu_Find_Exp_Mtime;
                CommonUtils::GetParaSignValue(VecCmd[iPos+1], cmdParaValue.pairParaValue.first, cmdParaValue.pairParaValue.second);
                m_vecCmdDataValue.push_back(cmdParaValue);
            }

            if (OPTION_COMMAND_NAME == VecCmd[iPos])
            {
                cmdParaValue.enumParaType = enum_Find_Exp_Name;

                CommonUtils::GetParaSignValue(VecCmd[iPos+1], cmdParaValue.pairParaValue.first, cmdParaValue.pairParaValue.second);
                m_vecCmdDataValue.push_back(cmdParaValue);
            }

            if (OPTION_COMMAND_SIZE == VecCmd[iPos])
            {
                cmdParaValue.enumParaType = enum_Find_Exp_Size;

                CommonUtils::GetParaSignValue(VecCmd[iPos+1], cmdParaValue.pairParaValue.first, cmdParaValue.pairParaValue.second);
                m_vecCmdDataValue.push_back(cmdParaValue);
            }

            if (OPTION_COMMAND_TEXT == VecCmd[iPos])
            {
                cmdParaValue.enumParaType = enum_Find_Exp_Text;
                CommonUtils::GetParaSignValue(VecCmd[iPos+1], cmdParaValue.pairParaValue.first, cmdParaValue.pairParaValue.second);
                m_vecCmdDataValue.push_back(cmdParaValue);
            }
        }        
    }

    return;

}
