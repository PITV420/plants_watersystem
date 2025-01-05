//
//  utilities.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 18/12/24.
//

#ifndef utilities_hpp
#define utilities_hpp

#include "globals.hpp"
#include <stdio.h>
#include <string>

#ifdef SIMULATION
#include <chrono>
#include <ctime>
#else
#endif

template<typename T> void GetDate(T* inputBuff)
{
#ifdef SIMULATION
    time_t tNow = time(0);
    tm* tLtm = localtime(&tNow);
    
    int iYear = 1900 + tLtm->tm_year;
    int iMonth = 1 + tLtm->tm_mon;
    int iDay = tLtm->tm_mday;
    int iDate = iDay * 1000000 + iMonth * 10000 + iYear;

    if (std::is_integral_v<T>)
        *inputBuff = iDate;
    else if (std::is_same_v<T, std::string>)
    {
        *inputBuff = iDay < 9 ? "0" + std::to_string(iDate) : std::to_string(iDate);
    }
    else if (std::is_same_v<T, char*>)
    {
        if (iDay > 9)
            snprintf((char*)inputBuff, sizeof(iDate) / sizeof(int), "%d", iDate);
        else
            snprintf((char*)inputBuff, sizeof(iDate) / sizeof(int), "0%d", iDate);
    }
#else

#endif
}

template<typename T> void GetTime(T* inputBuff)
{
#ifdef SIMULATION
    time_t tNow = time(0);
    tm* tLtm = localtime(&tNow);

    int iHour = 5 + tLtm->tm_hour;
    int iMinute = 30 + tLtm->tm_min;
    int iTime = iHour * 100 + iMinute;

    if (std::is_integral_v<T>)
        *inputBuff = iTime;
    else if (std::is_same_v<T, std::string>)
    {
        *inputBuff = iHour < 9 ? "0" + std::to_string(iTime) : std::to_string(iTime);
    }
    else if (std::is_same_v<T, char*>)
    {
        if (iHour > 9)
            snprintf((char*)inputBuff, sizeof(iTime) / sizeof(int), "%d", iTime);
        else
            snprintf((char*)inputBuff, sizeof(iTime) / sizeof(int), "0%d", iTime);
    }
#else

#endif
}

#endif
