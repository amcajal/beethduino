/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino_unit_test_invert_bpm_modifier.c          
*
*   Description:    Unit testing for "invert_bpm_modifier" function.
*                   Checks established preconditions and postconditions, related
*                   to the invert_bpm_modifier value and its changes.   
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

int bpm_modifier; /* 1 (one) or -1 (minus one). */

boolean is_mod_positive_before_invert;

boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    bpm_modifier        = 1;
    
    is_unit_testing_done = false;
    
    is_mod_positive_before_invert = true;
    
    restore_initial_test_values();
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("UNIT TESTING STARTED\n******************************");
    Serial.println("%%%Testing function: invert_bpm_modifier");
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
    test_positive_to_negative();
    test_negative_to_positive();
}


void test_positive_to_negative()
{
    Serial.println("test_positive_to_negative");
    invert_bpm_modifier();
    check_assertions();
    restore_initial_test_values();
}

void test_negative_to_positive()
{
    Serial.println("test_negative_to_positive");
    invert_bpm_modifier();
    check_assertions();
    restore_initial_test_values();
}


void restore_initial_test_values()
{
    Serial.println("");
}


void check_assertions()
{
    if (is_mod_positive_before_invert == true)
    {
        assert (bpm_modifier == -1);
        is_mod_positive_before_invert = false;
    }
    else
    { 
        assert (bpm_modifier == 1);
        is_mod_positive_before_invert = true;
    }
}


/**
* PRECONDITIONS     =>      bpm_modifier EQUAL TO 1 
*                       OR  bpm_modifier EQUAL TO -1
*
* EXCEPTIONS        =>  No exceptions expected.
*
* POSTCONDITIONS    =>      bpm_modifier EQUAL TO 1 
*                       OR  bpm_modifier EQUAL TO -1
*                       AND ( IF bpm_modifier WAS 1 then bpm_modifier NOW -1
*                           AND IF bpm_modifier WAS -1 then bpm_modifier NOW 1)
*
* ANALYSIS          =>  Basic multiplication is performed. bpm_modifier possible
*                       values are inside established range. No errors expected.
*/ 
void invert_bpm_modifier()
{
    bpm_modifier = bpm_modifier * -1;
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