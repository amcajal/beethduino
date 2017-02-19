/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino.c
*
*   Description:    Source code of Beethduino. 
*                   It implements an electronic metronome. A metronome is 
*                   a device that produces an audible sound at regular intervals
*                   that the user can set in beats per minute (BPM). 
*                   Musicians use the device to practice playing 
*                   to a regular pulse (https://en.wikipedia.org/wiki/Metronome)
*                   All necessary data and functions to implement the metronome
*                   are present in this file; No additional files are required.
*
*   Language:       Arduino (C/C++ set, compatible with avr-g++).
*                   Compiled in Arduino IDE, version 1.6.13
*
*   Dependencies:   LiquidCrystal.h (Library required to handle an LCD).     
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

#include <LiquidCrystal.h>

const int MUTE_BUZZER_BUTTON_PIN        = 13;              
const int CHANGE_BPM_BY_TEN_BUTTON_PIN  = 12;                                             
const int CHANGE_BPM_BY_ONE_BUTTON_PIN  = 11;                                        
const int ADD_OR_SUB_BPM_BUTTON_PIN     = 10;       
const int RESTART_BPM_BUTTON_PIN        = 9;    
const int ACTIVE_BUZZER_PIN             = 8;    

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int BPM_UPPER_BOUND           = 300;
const int BPM_LOWER_BOUND           = 1;

const int SOUND_DURATION            = 25;   /* In Milliseconds. */
const int MILLISECONDS_IN_SECOND    = 1000; 
  
const double SECONDS_IN_MINUTE = 60.00; /*  double type to force decimals
                                        *   in the divisions.
                                        */  

int last_pressed_button_pin;
int bpm;
int bpm_modifier; /* 1 (one) or -1 (minus one). */
int iteration_counter;

unsigned int bpm_freq_req_iter; /*  bpm frequency required iterations.
                                *   unsigned int in order to store a max. value
                                *   of 59975.
                                */
                                           
boolean is_buzzer_muted;   

/******************************************************************************/


void setup()
{
    pinMode(MUTE_BUZZER_BUTTON_PIN, INPUT);
    pinMode(CHANGE_BPM_BY_TEN_BUTTON_PIN, INPUT);
    pinMode(CHANGE_BPM_BY_ONE_BUTTON_PIN, INPUT);
    pinMode(ADD_OR_SUB_BPM_BUTTON_PIN, INPUT);
    pinMode(RESTART_BPM_BUTTON_PIN, INPUT);
    
    pinMode(ACTIVE_BUZZER_PIN, OUTPUT);

    lcd.begin(16, 2); /* Set LCD number of columns and rows. */ 
    
    reset_bpm();
    update_lcd();
    
    last_pressed_button_pin     = 0;
    iteration_counter           = 0;
}


void loop() /* Cyclic Executive at 16MHz. */
{
    check_button_pressing();
    process_bpm_frequency();
}


void check_button_pressing()
{
    int pin_to_check;
    
    for (pin_to_check = 9; pin_to_check <= 13; pin_to_check++)
    {
        detect_single_pulsation(pin_to_check);
    }
}


/**
* Detect the button that, after being pressed, has been released.
* Actions are performed only in the releasing process of a button, not in
* the pressings. This is done to avoid complex State Change Detection
* methods, and to allow the user to control the modifications (start and stop).
*/
void detect_single_pulsation(int pin_to_check)
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


void perform_operation(int pin_to_check)
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
}


void reset_bpm()
{
    bpm                 = 60;
    bpm_modifier        = 1;
    bpm_freq_req_iter   = 975;
    is_buzzer_muted     = true;
}


void invert_bpm_modifier()
{
    bpm_modifier = bpm_modifier * -1;
}


void update_bpm(int value)
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


void calculate_required_iterations()
{
    double temp_required_iterations;
    
    temp_required_iterations 
        = ((SECONDS_IN_MINUTE / bpm) * MILLISECONDS_IN_SECOND) - SOUND_DURATION;
        
    bpm_freq_req_iter = (unsigned int) temp_required_iterations;
}


void change_mute_state()
{
    is_buzzer_muted = !is_buzzer_muted;
}


void update_lcd()
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


void process_bpm_frequency()
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


void play_buzzer()
{
    digitalWrite(ACTIVE_BUZZER_PIN, HIGH);
    delay(SOUND_DURATION);
    digitalWrite(ACTIVE_BUZZER_PIN, LOW);
}
