/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino_unit_testing_detect_single_pulsation.c    
*
*   Description:    Unit testing for "detect_single_pulsation" function.
*                   Checks established preconditions and postconditions, related
*                   to the behaviour of last_pressed_button_pin when buttons
*                   are pressed or released.
*
*   Language:       Arduino (C/C++ set, compatible with avr-g++).
*                   Compiled in Arduino IDE, version 1.6.13
*
*   Dependencies:   assert.h
*                   https://gist.github.com/jlesech/3089916     
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
#define __ASSERT_USE_STDERR

#include <assert.h>

int last_pressed_button_pin;
int pin_to_check = 9;

boolean is_button_being_pressed;

boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    last_pressed_button_pin = 0;
    
    /*  pinMode inverted in purpose, in order to allow the pin_to_check
    *   remain HIGH until is not required. */
    pinMode(pin_to_check, OUTPUT); 
    
    is_unit_testing_done = false;
    
    is_button_being_pressed = true;
    
    restore_initial_test_values();
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("UNIT TESTING STARTED\n******************************");
    Serial.println("%%%Testing function: detect_single_pulsation");
}


void loop() /* Cyclic Executive at 16MHz. */
{
    if (is_unit_testing_done == false)
    {
        execute_tests();
        is_unit_testing_done = true;
        Serial.println("UNIT TESTING FINISHED\n******************************");
    }
}


void execute_tests()
{
    simulate_button_press(pin_to_check);
    simulate_button_release(pin_to_check);
}

void simulate_button_press(int pin_to_check)
{
    Serial.println("simulate_button_press");
    digitalWrite(pin_to_check, HIGH);
    detect_single_pulsation(pin_to_check);
    check_assertions(pin_to_check);
    restore_initial_test_values();
}


void simulate_button_release(int pin_to_check)
{
    Serial.println("simulate_button_release");
    digitalWrite(pin_to_check, LOW);
    detect_single_pulsation(pin_to_check);
    check_assertions(pin_to_check);
    restore_initial_test_values();
}

void restore_initial_test_values()
{
    Serial.println("");
}


void check_assertions(int pin_to_check)
{
    if (is_button_being_pressed == true)
    {
        assert (last_pressed_button_pin == pin_to_check);
        is_button_being_pressed = false;
    }
    else 
    {
        assert (last_pressed_button_pin == 0);
        is_button_being_pressed = true;
    }
}


/**
* PRECONDITIONS     =>      pin_to_check GREATER OR EQUAL TO 9
*                       AND pin_to_check LESS OR EQUAL TO 13
*                       AND ( (pin_to_check = HIGH) OR (pin_to_check = LOW))
*
* EXCEPTIONS        =>  No exceptions expected.
*
* POSTCONDITIONS    =>  IF pin_to_check = HIGH THEN
*                           last_pressed_button_pin = pin_to_check
*                       ELSE
*                           last_pressed_button_pin = 0
*
* ANALYSIS          =>  In the worst case, when pin_to_check is HIGH and LOW
*                       in the same cycle, the program flow allows a correct
*                       data processing. No errors expected.
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
        // perform_operation(pin_to_check);
    } 
}


void __assert(const char *__func, const char *__file, 
              int __lineno, const char *__sexp) 
{
    Serial.println("TEST_FAILED");
    Serial.println(__file);
    Serial.println(__func);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    Serial.flush();

    //abort();
}