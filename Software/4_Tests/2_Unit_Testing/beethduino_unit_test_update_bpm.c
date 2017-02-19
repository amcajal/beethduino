/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino_unit_test_update_bpm.c       
*
*   Description:    Unit testing for "update_bpm" function.
*                   Checks established preconditions and postconditions, related
*                   to bpm upper and lower value bounds.           
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

const int BPM_UPPER_BOUND           = 300;
const int BPM_LOWER_BOUND           = 1;

int bpm;
int bpm_modifier; /* 1 (one) or -1 (minus one). */

boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    is_unit_testing_done = false;
    
    restore_initial_test_values();
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("UNIT TESTING STARTED\n******************************");
    Serial.println("%%%Testing function: update_bpm");
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
    test_bpm_upper_bound();
    test_bpm_lower_bound();
    test_bpm_nominal_value();
}


void test_bpm_upper_bound()
{
    Serial.println("test_bpm_upper_bound");
    update_bpm(500); /* Precondition violated in order to simplify test. */
    check_assertions(BPM_UPPER_BOUND);
    restore_initial_test_values();
}


void test_bpm_lower_bound()
{
    Serial.println("test_bpm_lower_bound");
    bpm_modifier = -1;
    update_bpm(500); /* Precondition violated in order to simplify test. */
    check_assertions(BPM_LOWER_BOUND);
    restore_initial_test_values();
}


void test_bpm_nominal_value()
{
    Serial.println("test_bpm_nominal_value");
    update_bpm(60); /* Precondition violated in order to simplify test. */
    check_assertions(120);
    restore_initial_test_values();
}


void restore_initial_test_values()
{
    bpm = 60;
    bpm_modifier = 1;
    Serial.println("");
}


void check_assertions(int check_value)
{
    assert (bpm >= 1);
    assert (bpm <= 300);
    assert (bpm == check_value);
}


/**
* PRECONDITIONS     =>      bpm GREATER OR EQUAL TO 1
*                       AND bpm LESS OR EQUAL TO 300
*                       AND ( (bpm_modifier = 1) OR (bpm_modifier = -1) )
*                       AND ( (value = 1) OR (value = 10) )
*
* EXCEPTIONS        =>  No exceptions expected.
*
* POSTCONDITIONS    =>      bpm GREATER OR EQUAL TO 1
*                       AND bpm LESS OR EQUAL TO 300
*
* ANALYSIS          =>  Basic additions are performed. bpm value is always
*                       in range. No errors expected.
*/ 
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
    
    // calculate_required_iterations();
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