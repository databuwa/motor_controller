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
    lcd.setCursor(0,0);
    lcd.print(F("Motor controller"));
    delay(500);
    lcd.setCursor(0,0);
    lcd.print(F("                "));
}

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
    memset(s,0,sizeof(s));
    
    switch (current_motor_state)
    {
    case MotorState::RUNNING:
        snprintf(s,sizeof(s), "Off in %02d:%02d",(int)(GetTimeToNextEvent()/60), (int)(GetTimeToNextEvent()%60) );
        lcd.print(s);
        PRINT("Off in ");
        PRINT(GetTimeToNextEvent());
        PRINTLN("S");
        break;
    case MotorState::IDLE:
        snprintf(s,sizeof(s), "On in  %02d:%02d",(int)(GetTimeToNextEvent()/60), (int)(GetTimeToNextEvent()%60) );
        lcd.print(s);
        PRINT("On in ");
        PRINT(GetTimeToNextEvent());
        PRINTLN("S");
        break;
    default:
        break;
    }
}