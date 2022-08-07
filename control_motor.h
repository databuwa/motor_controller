#pragma once
#include "common.h"
#include <DS3231.h>
#include "eeprom_helper.h"

RTClib rtc;

void ControlMotor_(bool on)
{
    digitalWrite(MOTOR_PIN, on ? LOW : HIGH);
    digitalWrite(MOTOR_STATE_INDICATOR_PIN, on?HIGH:LOW);
}

/**
 * @brief Test whether enough time is elapsed from the last motor start.
 * 
 * @param now The current time seconds.
 * @param interval Interval to wait in seconds.
 * @return true Return true is the timeout elapsed.
 */
bool EnoughTimeElapsed(const uint32_t &now, const uint32_t &interval)
{
    return ((now - GetLastTime()) > interval);
}

void ControlMotor(void)
{
    PRINTLN("Controlling motor");
    static boolean turned_on = false;

    if (!turned_on)
    {
        if (EnoughTimeElapsed(real_time.unixtime, OFF_DURATION))
        {
            ControlMotor_(true);
            turned_on = true;
            SetLastTime(real_time.unixtime);
            current_motor_state = MotorState::RUNNING;
            last_event_time = real_time.unixtime;
            PRINTLN("Motor turned ON");
        }
        else
        {
            //PRINTLN("Not enough time is passed to turn ON the motor");
        }
    }
    else
    {
        if (EnoughTimeElapsed(real_time.unixtime, ON_DURATION))
        {
            ControlMotor_(false);
            turned_on = false;
            current_motor_state = MotorState::IDLE;
            last_event_time = real_time.unixtime;
            PRINTLN("Motor turned off");
        }
        else
        {
            //PRINTLN("Not enough time is passed to turn OFF the motor");
        }
    }
}