/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           buzzer_unit_test.c
*
*   Description:    Beethduino Component Test. 
*                   Its purpose is to:
*                   - Check components physical integrity: LCD shall
*                   print characters in its display as expected.
*                   - Check physical connection: LCD shall be connected to
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

#include <LiquidCrystal.h>  /* Library to handle LCD. */

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int counter;

/******************************************************************************/


void setup()
{  
    lcd.begin(16, 2); /* Set LCD number of columns and rows. */
    counter = 0;
}

void loop() /* Cyclic Executive at 16MHz. */
{
    lcd.setCursor(0, 0);
    lcd.print("MUTE_MUTE_MUTE_");
    
    String bpm = "bpm: ";
    bpm.concat(counter);
    
    lcd.setCursor(0, 1);
    lcd.print(bpm);
    
    delay(2000);
    
    lcd.clear();
    counter = counter + 10;
    
    delay(1000);
}