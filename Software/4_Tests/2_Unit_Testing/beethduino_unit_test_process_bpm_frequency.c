/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino_unit_test_process_bpm_frequency.c
*
*   Description:    Unit testing for "process_bpm_frequency" function.
*                   Checks established preconditions and postconditions, related
*                   to the possible values and behaviour of iteration_counter.   
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

int iteration_counter;

unsigned int bpm_freq_req_iter; /*  bpm frequency required iterations.
                                *   unsigned int in order to store a max. value
                                *   of 59975.
                                */
                                           
boolean is_buzzer_muted;

boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    is_unit_testing_done = false;
   
    restore_initial_test_values();
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("UNIT TESTING STARTED\n******************************");
    Serial.println("%%%Testing function: process_bpm_frequency");
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
    test_mute_condition();
    test_simple_iteration_condition();
    test_complex_iteration_increase();
    test_complex_iteration_decrease();
}


/**
* Test that when muted, no operation is performed, and thus,
* the value of iteration_counter is not altered.
*/
void test_mute_condition()
{
    Serial.println("test_mute_condition");
    for (int i = 0; i < 10; i++)
    {
        process_bpm_frequency();
    }
    check_assertions(0);
    restore_initial_test_values();
}


/**
* Test that iteration_counter is updated to the correct value, equal
* to the number of iterations of the for loop that executes the method
* process_bpm_frequency().
*/
void test_simple_iteration_condition()
{
    Serial.println("test_simple_iteration_condition");
    is_buzzer_muted = false;
    bpm_freq_req_iter = 100;
    for (int i = 0; i < 30; i++)
    {
        process_bpm_frequency();
    }
    check_assertions(30);
    restore_initial_test_values();
}


/**
* Test that iteration_counter increases if bpm_req_iteration value is increased 
* while the process_bpm_frequency method is executing. This test simulates
* the pulsation of a button that modifies bpm while the comparisson of
* iteration_counter and req_iteration is taking place.
*/
void test_complex_iteration_increase()
{
    Serial.println("test_complex_iteration_increase");
    is_buzzer_muted = false;
    bpm_freq_req_iter = 100;
    
    for (int i = 0; i < bpm_freq_req_iter-1; i++)
    {
        process_bpm_frequency();
    }
    
    bpm_freq_req_iter = 150;
    
    process_bpm_frequency();
    process_bpm_frequency();
    
    check_assertions(101);
    restore_initial_test_values();
}


/**
* Test that iteration_counter sets to 0 if bpm_req_iteration value is decreased 
* below the actual iteration_counter value while the process_bpm_frequency
* is executed. This test simulates the pulsation of a button that modifies bpm 
* while the comparisson of iteration_counter and req_iteration is taking place.
*/
void test_complex_iteration_decrease()
{
    Serial.println("test_complex_iteration_decrease");
    is_buzzer_muted = false;
    bpm_freq_req_iter = 100;
    for (int i = 0; i < bpm_freq_req_iter-1; i++)
    {
        process_bpm_frequency();
    }
    
    bpm_freq_req_iter = 10;
    
    for (int i = 0; i < bpm_freq_req_iter; i++)
    {
        process_bpm_frequency();
    }
    
    check_assertions(bpm_freq_req_iter - 1);
    restore_initial_test_values();
}


void restore_initial_test_values()
{
    iteration_counter = 0;
    bpm_freq_req_iter = 0;
    is_buzzer_muted = true;
    Serial.println("");
}


void check_assertions(int check_value)
{
    assert (iteration_counter <= 59975);
    assert (iteration_counter >= 0);
    assert (iteration_counter == check_value);
}


/**
* PRECONDITIONS     =>      (is_buzzer_muted = TRUE OR is_buzzer_muted = TRUE)
*                       AND (iteration_counter >= 0) 
*                       AND (iteration_counter <= 59975)
*
* EXCEPTIONS        =>  Integer overflow (caused by iteration_counter).
*
* POSTCONDITIONS    =>      (is_buzzer_muted = TRUE OR is_buzzer_muted = TRUE)
*                       AND (iteration_counter >= 0)
*                       AND (iteration_counter <= 59975)
*
* ANALYSIS          =>  iteration_counter is initialized a to 0. The max. value
*                       of bpm_freq_req_iter is 59975. Even in the worst case
*                       when bpm_freq_req_iter is updated after the IF check,
*                       the condition of "greater than or equal to" avoids
*                       a infinite iteration_counter increase. 
*                       No errors expected.
*/
void process_bpm_frequency()
{
    if (is_buzzer_muted == false)
    {
        delay(1);
        iteration_counter++;
        if (iteration_counter >= bpm_freq_req_iter)
        {
            //play_buzzer();
            iteration_counter = 0;
        }
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