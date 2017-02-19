/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino_unit_test_change_mute_state.c          
*
*   Description:    Unit testing for "change_mute_state" function.
*                   Checks established preconditions and postconditions, related
*                   to the is_buzzer_muted possible states or values.   
*
*   Language:       Arduino (C/C++ set, compatible with avr-g++).
*                   Compiled in Arduino IDE, version 1.6.13
*
*   Dependencies:   assert.h   
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

boolean is_buzzer_muted;
boolean is_buzzer_muted_before_change;

boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    is_buzzer_muted     = true;
    is_buzzer_muted_before_change = true;
    
    is_unit_testing_done = false;
    
    restore_initial_test_values();
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("UNIT TESTING STARTED\n******************************");
    Serial.println("%%%Testing function: change_mute_state");
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
    test_muted_to_unmuted();
    test_unmuted_to_muted();
}


void test_muted_to_unmuted()
{
    Serial.println("test_muted_to_unmuted");
    change_mute_state();
    check_assertions();
    restore_initial_test_values();
}


void test_unmuted_to_muted()
{
    Serial.println("test_unmuted_to_muted");
    change_mute_state();
    check_assertions();
    restore_initial_test_values();
}


void restore_initial_test_values()
{
    Serial.println("");
}


void check_assertions()
{
    if (is_buzzer_muted_before_change == true)
    {
        assert (is_buzzer_muted == false);
        is_buzzer_muted_before_change = false;
    }
    else
    { 
        assert (is_buzzer_muted == true);
        is_buzzer_muted_before_change = true;
    }
}


/**
* PRECONDITIONS     =>      is_buzzer_muted = TRUE
*                       OR  is_buzzer_muted = FALSE
*
* EXCEPTIONS        =>  No exceptions expected.
*
* POSTCONDITIONS    =>      is_buzzer_muted = TRUE
*                       OR  is_buzzer_muted = FALSE
*                       AND (   IF is_buzzer_muted WAS TRUE then NOW is FALSE
*                           AND IF is_buzzer_muted WAS FALSE then NOW is TRUE)
*
* ANALYSIS          =>  Basic boolean operation is performed. is_buzzer_muted
*                       stay in established range. No errors expected.
*/ 
void change_mute_state()
{
    is_buzzer_muted = !is_buzzer_muted;
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