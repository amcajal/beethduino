/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           buttons_unit_test.c
*
*   Description:    Beethduino Component Test. 
*                   Its purpose is to:
*                   - Check components physical integrity: buttons shall
*                   detect the pulsations and work as expected.
*                   - Check physical connection: buttons shall be connected to
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

const int MUTE_BUZZER_BUTTON_PIN        = 13;              
const int CHANGE_BPM_BY_TEN_BUTTON_PIN  = 12;                                             
const int CHANGE_BPM_BY_ONE_BUTTON_PIN  = 11;                                        
const int ADD_OR_SUB_BPM_BUTTON_PIN     = 10;       
const int RESET_BPM_BUTTON_PIN          = 9;

int counter;

/******************************************************************************/


void setup()
{  
    pinMode(MUTE_BUZZER_BUTTON_PIN, INPUT);
    pinMode(CHANGE_BPM_BY_TEN_BUTTON_PIN, INPUT);
    pinMode(CHANGE_BPM_BY_ONE_BUTTON_PIN, INPUT);
    pinMode(ADD_OR_SUB_BPM_BUTTON_PIN, INPUT);
    pinMode(RESET_BPM_BUTTON_PIN, INPUT);
    
    Serial.begin(9600); /* Start serial port at 9600 bps. */
    Serial.print("Button test started");
}

void loop() /* Cyclic Executive at 16MHz. */
{
    if (digitalRead(CHANGE_BPM_BY_TEN_BUTTON_PIN) == HIGH)
    {
        Serial.println("CHANGE BPM BY 10 HAS BEEN PRESSED");
    }
    else if (digitalRead(CHANGE_BPM_BY_ONE_BUTTON_PIN) == HIGH)
    {
        Serial.println("CHANGE BPM BY 1 HAS BEEN PRESSED");
    }
    else if (digitalRead(ADD_OR_SUB_BPM_BUTTON_PIN) == HIGH)
    {
        Serial.println("ADD OS SUB BUTTON HAS BEEN PRESSED");
    }
    else if (digitalRead(RESET_BPM_BUTTON_PIN) == HIGH)
    {
        Serial.println("RESET BPM BUTTON HAS BEEN PRESSED");
    }
    else if (digitalRead(MUTE_BUZZER_BUTTON_PIN) == HIGH)
    {
        Serial.println("MUTE BUZZER BUTTON HAS BEEN PRESSED");
    }
    else
    {
        /* No operation. */
    }
}