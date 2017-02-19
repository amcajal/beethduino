/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino_unit_test_perform_operation.c  
*
*   Description:    Unit testing for "perform_operation" function.
*                   Checks established preconditions and postconditions, related
*                   to the possible branches in a SWITCH statement.  
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

int function_called;

boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    is_unit_testing_done = false;
    
    restore_initial_test_values();
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("UNIT TESTING STARTED\n******************************");
    Serial.println("%%%Testing function: perform_operation");
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
    for (int i = 9; i <= 13; i++)
    {
        Serial.print("Testing branch function: ");
        Serial.println(i);
        perform_operation(i);
        check_assertions(i * -1);
    }
}


void restore_initial_test_values()
{
    Serial.println("");
}


void check_assertions(int check_value)
{
    assert (function_called == check_value);
}


/**
* PRECONDITIONS     =>      pin_to_check GREATER OR EQUAL TO 9
*                       AND pin_to_check LESS OR EQUAL TO 13
*
* EXCEPTIONS        =>  No exceptions expected.
*
* POSTCONDITIONS    =>      function_called DIFFERENT FROM 0
*                       AND function_called GREATER OR EQUAL TO -13
*                       AND function called LESS OR EQUAL TO -9
*
*                           function_called represents a call to a certain
*                           function in the SWITCH statement.
*
* ANALYSIS          =>  Basic comparissons operations performed. Switch block
*                       covers all possibilities. No errors expected.
*/ 
void perform_operation(int pin_to_check)
{
    switch (pin_to_check) 
    {
        case 9:
            //reset_bpm();
            function_called = 9;
            break;
        case 10:
            //invert_bpm_modifier();
            function_called = 10;
            break;
        case 11:
            //update_bpm(1);
            function_called = 11;
            break;
        case 12:
            //update_bpm(10);
            function_called = 12;
            break;
        case 13:
            //change_mute_state();
            function_called = 13;
            break;
        default: 
            /* No operation. */
            function_called = 0;
        break;
    }
    
    function_called = function_called * -1;
    //update_lcd();
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