/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           buzzer_unit_test.c
*
*   Description:    Beethduino Component Test. 
*                   Its purpose is to:
*                   - Check components physical integrity: buzzer shall
*                   produce sounds as it specification establishes.
*                   - Check physical connection: buzzer shall be connected to
*                   the correct pins, as design phase establishes.
*
*   Language:       Arduino (C/C++ set, compatible with avr-g++).
*                   Compiled in Arduino IDE, version 1.6.13
*
*   Dependencies:   None.    
*
*   Notes:          BPM - Beats Per Minute.
*                   LCD - Liquid Crystal Display.
*
*   Author:         Alberto Martin Cajal
*                   amartin.glimpse23@gmail.com
*                   amartin<DOT>glimpse23<AT>gmail<DOT>.com
*  
*   License:        GNU GPL v3.0
*
*   URL:            https://github.com/amcajal/beethduino        
*             
*******************************************************************************/

const int ACTIVE_BUZZER_PIN                = 8;  

/******************************************************************************/


void setup()
{  
    pinMode(ACTIVE_BUZZER_PIN, OUTPUT);
}

void loop() /* Cyclic Executive at 16MHz. */
{
    digitalWrite(ACTIVE_BUZZER_PIN, HIGH);
    delay(25);
    digitalWrite(ACTIVE_BUZZER_PIN, LOW);
    delay(975);
}