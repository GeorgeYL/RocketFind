#ifndef _H_ROCKET_FIND_ENTITY_H_
#define _H_ROCKET_FIND_ENTITY_H_
//File: RocketFind.h 
//Descriptions: provide some tools.
//Data: 2012-4-21
//Author: lyzhi
#include <io.h>
#include "CommonDefine.h"

#define BUFFER_SIZE 8192 //4096*2  8K //the size buffer 

class CRocketFindEntity
{
public:
    CRocketFindEntity(CMD_DATA_VALUE cmdParaValue);
    ~CRocketFindEntity();

    //Construct the conditions
    ROCKET_ERRORCODE executeCmd(const CMD_DATA_VALUE& cmdParaValue);
    
    //Filter files with command conditions 
    ROCKET_ERRORCODE ListFileInfo(const string& strPath, const string& strFileName, 
        const ENUM_SIGN_VALUE& enumMTSign, const time_t& lMTime,
        const ENUM_SIGN_VALUE& enumSizeSign, const long& lFileSize, 
        const string& strPatternText);

    //Doing the filter action the file with  [-text XXX] condition
    void DoStringMatch(const string& strPath, const _finddata_t& file, const string& strPatternText);

    //Find the file with [-text XXX] condition
    bool ListFileWithText(const string& strFileName, const string& strPatternText);


    
private:
    CMD_DATA_VALUE m_oCmdParaValue; //vecor saved command parameter-values
};


#endif
