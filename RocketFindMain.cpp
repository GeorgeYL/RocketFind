// RocketFind.cpp : The main entrance
//
#include "CommonDefine.h"
#include "CommonUtil.h"
#include "RocketCommonTask.h"
#include <iostream>
using namespace std;



/************************************************************************/
/* Function: the entry of the function                                  */
/* Input:                                                               */
/* Output:                                                              */
/* Date:                                                                */
/************************************************************************/

int main(int argc, char* argv[])
{     
    if (COMMAND_WITHOUT_PARAMETER == argc)
    {
        CommonUtils::ShowCmdTips(); 
        while (true)
        {
            string strInput = ROCKET_BLANK_STRING;

            //find . -name "*.c" -text "Rocket" -size +100k
            while (getline(cin, strInput, '\n'))
            {
                //cout << strInput;
                CommonUtils::WriteLog(__LINE__ ,strInput, "main function.");
                CRocketCommonTask oRocketCommonTask(strInput);                 
            }
        }       
        
    }
    return 0;
}

