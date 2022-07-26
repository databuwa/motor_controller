#pragma once
#include <EEPROM.h>


    uint32_t GetLastTime()
    {
        uint32_t t;
        EEPROM.get(0, t);
        return t;
    }

    void SetLastTime(const uint32_t &last_time)
    {
        EEPROM.put(0, last_time);
    }
