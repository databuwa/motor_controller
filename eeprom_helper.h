#pragma once
#include <EEPROM.h>

/**
 * @brief Get the Last Time the motor started in unix time (seconds).
 * 
 * @return uint32_t 
 */
uint32_t GetLastTime()
{
    uint32_t t;
    EEPROM.get(0, t);
    return t;
}

/**
 * @brief Set the Last Time the motor started in unix time (seconds).
 * 
 * @param last_time 
 */
void SetLastTime(const uint32_t &last_time)
{
    EEPROM.put(0, last_time);
}
