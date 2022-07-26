#pragma once
#include <Arduino.h>

#define MOTOR_PIN A0
#define MOTOR_STATE_INDICATOR_PIN LED_BUILTIN
#define LCD_RS_PIN 6
#define LCD_EN_PIN 5
#define LCD_D4 8
#define LCD_D5 9
#define LCD_D6 10
#define LCD_D7 11
#define _1S 1000
#define _10S 10000
#define _1H 3600
#define _5M 300
#define OFF_DURATION _1H    // 3600
#define ON_DURATION _5M     // 300

struct Time
{
    uint32_t seconds;
    uint32_t minutes;
    uint32_t hours;
    uint32_t unixtime;
    float temperature;
};

enum MotorState
{
    IDLE,
    RUNNING
};

MotorState current_motor_state = MotorState::IDLE;
uint32_t last_event_time = 0;
Time real_time = {};


//#define MOTOR_DEBUG_

#ifdef MOTOR_DEBUG_
#define PRINTLN(x) Serial.println(x)
#define PRINT(x) Serial.print(x)
#define SERIAL_BEGIN(x) Serial.begin(x)
#else
#define PRINTLN(x)
#define PRINT(x)
#define SERIAL_BEGIN(x)
#endif