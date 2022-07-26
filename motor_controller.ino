#include "control_motor.h"
#include "time_delay.h"
#include "eeprom_helper.h"
#include "lcd_controller.h"
#include "eeprom_helper.h"
#include <DS3231.h>

RTClib clock_lib;

CTimeDelay motor_control_scheduler(_10S);
CTimeDelay display_time_scheduler(_1S);
CTimeDelay display_motor_status_scheduler(_1S);
CTimeDelay real_time_update_scheduler(_1S);

void UpdateRealTime()
{
    auto now = clock_lib.now();
    real_time.seconds = now.second();
    real_time.hours = now.hour();
    real_time.minutes = now.minute();
    real_time.unixtime = now.unixtime();
    real_time.temperature = now.temperature();
}

uint32_t GetTimeToNextEvent()
{
    auto time_elapsed = real_time.unixtime - last_event_time;
    uint32_t next_event_in = 0;
    switch (current_motor_state)
    {
    case MotorState::IDLE:
        next_event_in = time_elapsed>OFF_DURATION? 0 : OFF_DURATION - time_elapsed;
        break;
    case MotorState::RUNNING:
        next_event_in =time_elapsed>ON_DURATION? 0 : ON_DURATION - time_elapsed;
        break;
    default:
        break;
    }
    return next_event_in;
}

void setup()
{
    SERIAL_BEGIN(115200);
    Wire.begin();
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(MOTOR_STATE_INDICATOR_PIN,OUTPUT);
    SetupLCD();
    last_event_time = GetLastTime();
    
}

void loop()
{
    real_time_update_scheduler.TimeDelay(UpdateRealTime);
    display_time_scheduler.TimeDelay(DisplayTime);
    motor_control_scheduler.TimeDelay(ControlMotor);
    display_motor_status_scheduler.TimeDelay(DisplayMotorStatus);

}