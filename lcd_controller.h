#pragma once
#include "common.h"
#include <DS3231.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

extern uint32_t GetTimeToNextEvent();

char s[16];

void SetupLCD()
{
    lcd.begin(16,2);
}

int i=0;
void DisplayTime()
{
    lcd.setCursor(0,0);
    char t[5];
    char* val = dtostrf(real_time.temperature, 4, 2, t );
    snprintf(s,sizeof(s), "%02i:%02i:%02i T%s", (int)real_time.hours, (int)real_time.minutes, (int)real_time.seconds, val);
    lcd.print(s);
    PRINTLN(s);
}

void DisplayMotorStatus()
{
    lcd.setCursor(0,1);
    switch (current_motor_state)
    {
    case MotorState::RUNNING:
    #ifndef MOTOR_DEBUG_
        snprintf(s,sizeof(s), "Off in %02d:%02d",(int)(GetTimeToNextEvent()/60), (int)(GetTimeToNextEvent()%60) );
        lcd.print(s);
        /*lcd.print("Off in ");
        lcd.print(GetTimeToNextEvent() );
        lcd.print("S");*/
        #endif
        PRINT("Off in ");
        PRINT(GetTimeToNextEvent());
        PRINTLN("S");
        break;
    case MotorState::IDLE:
    #ifndef MOTOR_DEBUG_
        snprintf(s,sizeof(s), "On in %02d:%02d",(int)(GetTimeToNextEvent()/60), (int)(GetTimeToNextEvent()%60) );
        lcd.print(s);
        // lcd.print("On in ");
        // lcd.print(GetTimeToNextEvent());
        // lcd.print("S");
        #endif
        PRINT("On in ");
        PRINT(GetTimeToNextEvent());
        PRINTLN("S");
        break;
    default:
        break;
    }
}