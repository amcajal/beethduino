/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:          
*
*   Description:    Unit testing for "reset_bpm" function.
*                   Checks established preconditions and postconditions, related
*                   to the initial or default values of several variables.   
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

int bpm;
int bpm_modifier;       /* 1 or -1 */
int bpm_freq_req_iter;  /* bpm frequency required iterations. */
            
boolean is_buzzer_muted;  

boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    is_unit_testing_done = false;
    
    restore_initial_test_values();
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("UNIT TESTING STARTED\n******************************");
    Serial.println("%%%Testing function: reset_bpm\n");
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
    test_initialization_values();
    test_bpm_changes();
    test_bpm_modifier_changes();
    test_req_iter_changes();
    test_buzzer_changes();
}


void test_initialization_values()
{
    Serial.println("Test_initialization_values");
    reset_bpm();
    check_assertions();
    restore_initial_test_values();
}


void test_bpm_changes()
{
    Serial.println("test_bpm_changes");
    bpm = 200;
    reset_bpm();
    check_assertions();
    restore_initial_test_values();
}


void test_bpm_modifier_changes()
{
    Serial.println("test_bpm_modifier_changes");
    bpm_modifier = -1;
    reset_bpm();
    check_assertions();
    restore_initial_test_values();
}


void test_req_iter_changes()
{
    Serial.println("test_req_iter_changes");
    bpm_freq_req_iter = 30000;
    reset_bpm();
    check_assertions();
    restore_initial_test_values();
}


void test_buzzer_changes()
{
    Serial.println("test_buzzer_changes");
    is_buzzer_muted = false;
    reset_bpm();
    check_assertions();
    restore_initial_test_values();
}


void restore_initial_test_values()
{
    Serial.println("");
}


void check_assertions()
{
    assert (bpm == 60);
    assert (bpm_modifier == 1);
    assert (bpm_freq_req_iter <= 975);
    assert (is_buzzer_muted == true);
}


/**
* PRECONDITIONS     =>      (bpm AND bpm_modifier AND bpm_freq_req_iter AND
*                           is_buzzer_muted ARE DECLARED BUT NO INITIALIZED)
*                       OR
*                               bpm <= 300 
*                           AND bpm >= 1
*                           AND ( (bpm_modifier = 1) OR (bpm_modifier = -1) )
*                           AND bpm_freq_req_iter <= 59975
*                           AND bpm_freq_req_iter >= 175
*                           AND (   (is_buzzer_muted = true) 
*                               OR  (is_buzzer_muted = false))
*
* EXCEPTIONS        =>  No exceptions expected.
*
* POSTCONDITIONS    =>      bpm = 60
*                       AND bpm_modifier = 1
*                       AND bpm_freq_req_iter = 975
*                       AND is_buzzer_muted = true
*
* ANALYSIS          =>  Basic assignments are performed. All values are inside
*                       established ranges. No errors expected.
*/ 
void reset_bpm()
{
    bpm                 = 60;
    bpm_modifier        = 1;
    bpm_freq_req_iter   = 975;
    is_buzzer_muted     = true;
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