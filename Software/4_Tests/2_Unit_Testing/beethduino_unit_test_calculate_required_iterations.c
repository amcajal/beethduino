/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino_unit_test_calculate_required_iterations.c
*
*   Description:    Unit testing for "calculate_required_iterations" function.
*                   Checks established preconditions and postconditions, related
*                   to the possible values of BPM and required iterations.
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

const int SOUND_DURATION          = 25;   /* In Milliseconds. */
const int MILLISECONDS_IN_SECOND  = 1000;

const double SECONDS_IN_MINUTE = 60.00; /*  double type to force decimals
                                        *   in the divisions.
                                        */                                                  

unsigned int bpm_freq_req_iter;
int bpm;

boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    is_unit_testing_done = false;
    
    restore_initial_test_values();
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("UNIT TESTING STARTED\n******************************");
    Serial.println("%%%Testing function: calculate_required_iterations()");
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
    test_bpm_lower_bound();
    test_bpm_upper_bound();
    test_bpm_nominal_value();
}


void test_bpm_lower_bound()
{
    Serial.println("Test_bpm_lower_bound");
    bpm = BPM_LOWER_BOUND;
    calculate_required_iterations();
    check_assertions();
    restore_initial_test_values();
}


void test_bpm_upper_bound()
{
    Serial.println("test_bpm_upper_bound");
    bpm = BPM_UPPER_BOUND;
    calculate_required_iterations();
    check_assertions();
    restore_initial_test_values();
}


void test_bpm_nominal_value()
{
    Serial.println("test_bpm_nominal_value");
    bpm = 146;
    calculate_required_iterations();
    check_assertions();
    assert (bpm_freq_req_iter == 385);
    restore_initial_test_values();
}


void restore_initial_test_values()
{
    bpm_freq_req_iter = 0;
    bpm = 0;
    Serial.println("");
}


void check_assertions()
{
    assert (bpm >= 1);
    assert (bpm <= 300);
    assert (bpm_freq_req_iter <= 59975);
    assert (bpm_freq_req_iter >= 175);
}


/**
* PRECONDITIONS     =>      bpm GREATER OR EQUAL TO 1
*                       AND bpm LESS OR EQUAL TO 300
*
* EXCEPTIONS        =>  temp_required_iterations OUT OF RANGE (double)
*
* POSTCONDITIONS    =>      temp_required_iterations LESS OR EQUAL TO 59975
*                       AND temp_required_iterations GREATER OR EQUAL TO 175
*
* ANALYSIS          =>  double type occupy 32 bits in Arduino UNO based boards.
*                       temp_required_iterations occupy 16 bits. Max. and min.
*                       values are inside double type range. No out of range 
*                       exceptions expected.
*/ 
void calculate_required_iterations()
{
    double temp_required_iterations;
    
    temp_required_iterations 
        = ((SECONDS_IN_MINUTE / bpm) * MILLISECONDS_IN_SECOND) - SOUND_DURATION;
        
    bpm_freq_req_iter = (unsigned int) temp_required_iterations;
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