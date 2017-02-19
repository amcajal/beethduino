/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           Beethduino.cpp        
*
*   Description:    Body file of Beethduino library. The library contains
*                   the exact same code than the main code (final functionality
*                   executed in the Arduino), but adapted to be easely called
*                   and tested in the integration test files. Modifications
*                   respect to the original code includes additional variables,
*                   methods and behaviour changes, all with testing purposes.
*
*   Language:       Arduino (C/C++ set, compatible with avr-g++).
*                   Compiled in Arduino IDE, version 1.6.13
*
*   Dependencies:   Arduino.h
*                   Beethduino.h 
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

#include "Arduino.h"
#include "Beethduino.h"

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

Beethduino::Beethduino()
{
    /* pinMode inverted in purpose, in order to maintain the signal in HIGH
    * or LOW the required time to check certain conditions 
    * during integration testing.
    */
    pinMode(MUTE_BUZZER_BUTTON_PIN, OUTPUT);
    pinMode(CHANGE_BPM_BY_TEN_BUTTON_PIN, OUTPUT);
    pinMode(CHANGE_BPM_BY_ONE_BUTTON_PIN, OUTPUT);
    pinMode(ADD_OR_SUB_BPM_BUTTON_PIN, OUTPUT);
    pinMode(RESTART_BPM_BUTTON_PIN, OUTPUT);
    
    pinMode(ACTIVE_BUZZER_PIN, OUTPUT);

    lcd.begin(16, 2); /* Set LCD number of columns and rows. */
    
    reset_bpm();
    update_lcd();
    update_serial_monitor();
    
    buzzer_bips = 0;  
    last_pressed_button_pin     = 0;
    iteration_counter           = 0;
}


void Beethduino::exec_main_loop()
{
    check_button_pressing();
    process_bpm_frequency();
}


void Beethduino::check_button_pressing()
{
    int pin_to_check;
    
    for (pin_to_check = 9; pin_to_check <= 13; pin_to_check++)
    {
        detect_single_pulsation(pin_to_check);
    }
}

/*
* Detect the button that, after being pressed, has been released.
* The method allows to detect the pulsation of a button, and its release.
* Actions are performed only in the releasing process of a button, not in
* the pressings. This is done to avoid comples State Change Detection
* methods, and to allow the user to control the modifications (start and stop).
*/
void Beethduino::detect_single_pulsation(int pin_to_check)
{
    /* Detect what button is pressed. */
    if (digitalRead(pin_to_check) == HIGH)
    {
        last_pressed_button_pin = pin_to_check;
    }
    
    /* Detect if the pressed button is now released. */
    if ((digitalRead(pin_to_check) == LOW)
        && (last_pressed_button_pin == pin_to_check))
    {
        last_pressed_button_pin = 0;
        perform_operation(pin_to_check);
    } 
}


void Beethduino::perform_operation(int pin_to_check)
{
    switch (pin_to_check) 
    {
        case 9:
            reset_bpm();
            break;
        case 10:
            invert_bpm_modifier();
            break;
        case 11:
            update_bpm(1);
            break;
        case 12:
            update_bpm(10);
            break;
        case 13:
            change_mute_state();
            break;
        default: 
            /* No operation. */
        break;
    }
    
    update_lcd();
    update_serial_monitor();
}


void Beethduino::reset_bpm()
{
    bpm                 = 60;
    bpm_modifier        = 1;
    bpm_freq_req_iter   = 975;
    is_buzzer_muted     = true;
}


void Beethduino::invert_bpm_modifier()
{
    bpm_modifier = bpm_modifier * -1;
}


void Beethduino::update_bpm(int value)
{
    bpm = bpm + (bpm_modifier * value);
    
    if (bpm > BPM_UPPER_BOUND)
    {
        bpm = BPM_UPPER_BOUND;
    } 
    else if (bpm < BPM_LOWER_BOUND)
    {
        bpm = BPM_LOWER_BOUND;
    }
    else 
    {
        /* No operation. */
    }
    
    calculate_required_iterations();
}


void Beethduino::calculate_required_iterations()
{
    double temp_required_iterations;
    
    temp_required_iterations 
        = ((SECONDS_IN_MINUTE / bpm) * MILLISECONDS_IN_SECOND) - SOUND_DURATION;
        
    bpm_freq_req_iter = (unsigned int) temp_required_iterations;
}


void Beethduino::change_mute_state()
{
    is_buzzer_muted = !is_buzzer_muted;
}


void Beethduino::update_lcd()
{    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    if (is_buzzer_muted == true)
    {
        lcd.print("MUTE_MUTE_MUTE_"); 
    }
    else if (is_buzzer_muted == false)
    {
        lcd.print("");
    }
    else 
    {
        /* No operation. */
    }
    
    String bpm_text_info;
    lcd.setCursor(0, 1);
    
    if (bpm_modifier == -1)
    {
        bpm_text_info = "SUB BPM: ";        
    }
    else if (bpm_modifier == 1)
    {
        bpm_text_info = "ADD BPM: ";
    }
    else
    {
        /* No operation. */
    }
    
    bpm_text_info.concat(bpm);
    lcd.print(bpm_text_info);
}

void Beethduino::update_serial_monitor()
{
    bpm_text_info = "";
    
    if (is_buzzer_muted == true)
    {
        bpm_text_info = "MUTE_MUTE_MUTE_LFCR";/*Line Feed and Carriage Return.*/
    }
    else if (is_buzzer_muted == false)
    {
        bpm_text_info = "LFCR";
    }
    else 
    {
        /* No operation. */
    }
    
    if (bpm_modifier == -1)
    {
        bpm_text_info.concat("SUB BPM: ");        
    }
    else if (bpm_modifier == 1)
    {
        bpm_text_info.concat("ADD BPM: ");  
    }
    else
    {
        /* No operation. */
    }
    
    bpm_text_info.concat(bpm);
}

void Beethduino::process_bpm_frequency()
{
    if (is_buzzer_muted == false)
    {
        delay(1);
        iteration_counter++;
        if (iteration_counter >= bpm_freq_req_iter)
        {
            play_buzzer();
            iteration_counter = 0;
        }
    }
}


void Beethduino::play_buzzer()
{
    digitalWrite(ACTIVE_BUZZER_PIN, HIGH);
    delay(SOUND_DURATION);
    digitalWrite(ACTIVE_BUZZER_PIN, LOW);
    
    buzzer_bips ++;
}