/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           beethduino_integration_test.c
*
*   Description:    Integration test of Beethduino project. Aimed to achieve a
*                   100% code coverage, executing all possible situations
*                   at least once, and checking interface between functions
*                   are correct, as well as the final functionality.
*
*   Language:       Arduino (C/C++ set, compatible with avr-g++).
*                   Compiled in Arduino IDE, version 1.6.13
*
*   Dependencies:   assert.h
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
#define __ASSERT_USE_STDERR

#include <assert.h>
#include <Beethduino.h>

Beethduino beethduino;
boolean is_unit_testing_done;

/******************************************************************************/


void setup()
{
    is_unit_testing_done = false;
    
    Serial.begin(9600); /* Start serial port at 9600 bits per second. */
    Serial.println("INTEGRATION TESTING part 1 STARTED\n*********************");
}


void loop() /* Cyclic Executive at 16MHz. */
{
    if (is_unit_testing_done == false)
    {
        execute_tests();
        is_unit_testing_done = true;
        Serial.println("INTEGRATION TESTING FINISHED\n***********************");
    }
}


void execute_tests()
{
    test_initial_condition();
    test_increase_bpm_by_one();
    test_increase_bpm_by_ten();
    test_change_mod();
    test_decrease_bpm_by_one();
    test_decrease_bpm_by_ten();
    test_restart_state();
}


void test_initial_condition()
{
    Serial.println("test_initial_condition");
    
    /* Arbitrary number of iterations. */
    for (int i = 0; i < 100; i++)
    {
        beethduino.exec_main_loop();
    }
    
    assert (beethduino.last_pressed_button_pin == 0);
    
    assert (beethduino.is_buzzer_muted == true);
    
    assert (beethduino.buzzer_bips == 0);
    assert (beethduino.iteration_counter == 0);
   
    assert (beethduino.bpm == 60);
    assert (beethduino.bpm_modifier == 1);
    assert (beethduino.bpm_freq_req_iter == 975);
    
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRADD BPM: 60");
}


void test_increase_bpm_by_one()
{
    Serial.println("test_increase_bpm_by_one");
    
    digitalWrite(beethduino.CHANGE_BPM_BY_ONE_BUTTON_PIN, HIGH);
    
    /* Arbitrary number of iterations. */
    for (int i = 0; i < 10; i++)
    {
        beethduino.exec_main_loop();
        if (i == 8)
        {
            digitalWrite(beethduino.CHANGE_BPM_BY_ONE_BUTTON_PIN, LOW);
        }
    }
    
    assert (beethduino.last_pressed_button_pin == 0);
    
    assert (beethduino.is_buzzer_muted == true);
    
    assert (beethduino.buzzer_bips == 0);
    assert (beethduino.iteration_counter == 0);
   
    assert (beethduino.bpm == 61); /* Changed from 60 to 61. */
    assert (beethduino.bpm_modifier == 1);
    assert (beethduino.bpm_freq_req_iter == 958); /* Previously was 975.*/
    
    /* Changed from 60 to 61. */
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRADD BPM: 61");
}


void test_increase_bpm_by_ten()
{
    Serial.println("test_increase_bpm_by_ten");
    
    digitalWrite(beethduino.CHANGE_BPM_BY_TEN_BUTTON_PIN, HIGH);
    
    /* Arbitrary number of iterations. */
    for (int i = 0; i < 10; i++)
    {
        beethduino.exec_main_loop();
        if (i == 8)
        {
            digitalWrite(beethduino.CHANGE_BPM_BY_TEN_BUTTON_PIN, LOW);
        }
    }
    
    assert (beethduino.last_pressed_button_pin == 0);
    
    assert (beethduino.is_buzzer_muted == true);
    
    assert (beethduino.buzzer_bips == 0);
    assert (beethduino.iteration_counter == 0);
   
    assert (beethduino.bpm == 71); /* Changed from 61 to 71. */
    assert (beethduino.bpm_modifier == 1);
    assert (beethduino.bpm_freq_req_iter == 820); /* Previously was 958.*/
    
    /* Changed from 61 to 71. */
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRADD BPM: 71");
}


void test_change_mod()
{
    Serial.println("test_change_mod");
    
    digitalWrite(beethduino.ADD_OR_SUB_BPM_BUTTON_PIN, HIGH);
    
    /* Arbitrary number of iterations. */
    for (int i = 0; i < 10; i++)
    {
        beethduino.exec_main_loop();
        if (i == 8)
        {
            digitalWrite(beethduino.ADD_OR_SUB_BPM_BUTTON_PIN, LOW);
        }
    }
    
    assert (beethduino.last_pressed_button_pin == 0);
    
    assert (beethduino.is_buzzer_muted == true);
    
    assert (beethduino.buzzer_bips == 0);
    assert (beethduino.iteration_counter == 0);
   
    assert (beethduino.bpm == 71);
    assert (beethduino.bpm_modifier == -1); /* Changed from 1 to -1. */
    assert (beethduino.bpm_freq_req_iter == 820);
    
    /* Changed from ADD to SUB. */
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRSUB BPM: 71");
}


void test_decrease_bpm_by_one()
{
    Serial.println("test_decrease_bpm_by_one");
    
    digitalWrite(beethduino.CHANGE_BPM_BY_ONE_BUTTON_PIN, HIGH);
    
    /* Arbitrary number of iterations. */
    for (int i = 0; i < 10; i++)
    {
        beethduino.exec_main_loop();
        if (i == 8)
        {
            digitalWrite(beethduino.CHANGE_BPM_BY_ONE_BUTTON_PIN, LOW);
        }
    }
    
    assert (beethduino.last_pressed_button_pin == 0);
    
    assert (beethduino.is_buzzer_muted == true);
    
    assert (beethduino.buzzer_bips == 0);
    assert (beethduino.iteration_counter == 0);
   
    assert (beethduino.bpm == 70); /* Changed from 71 to 70. */
    assert (beethduino.bpm_modifier == -1);
    assert (beethduino.bpm_freq_req_iter == 832); /* Previously was 820.*/
    
    /* Changed from 71 to 70. */
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRSUB BPM: 70");
}


void test_decrease_bpm_by_ten()
{
    Serial.println("test_decrease_bpm_by_ten");
    
    digitalWrite(beethduino.CHANGE_BPM_BY_TEN_BUTTON_PIN, HIGH);
    
    /* Arbitrary number of iterations. */
    for (int i = 0; i < 10; i++)
    {
        beethduino.exec_main_loop();
        if (i == 8)
        {
            digitalWrite(beethduino.CHANGE_BPM_BY_TEN_BUTTON_PIN, LOW);
        }
    }
    
    assert (beethduino.last_pressed_button_pin == 0);
    
    assert (beethduino.is_buzzer_muted == true);
    
    assert (beethduino.buzzer_bips == 0);
    assert (beethduino.iteration_counter == 0);
   
    assert (beethduino.bpm == 60); /* Changed from 70 to 60. */
    assert (beethduino.bpm_modifier == -1);
    assert (beethduino.bpm_freq_req_iter == 975); /* Previously was 832.*/
    
    /* Changed from 70 to 60. */
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRSUB BPM: 60");
}


void test_restart_state()
{
    Serial.println("test_restart_state");

    digitalWrite(beethduino.RESTART_BPM_BUTTON_PIN, HIGH);
    
    /* Arbitrary number of iterations. */
    for (int i = 0; i < 10; i++)
    {
        beethduino.exec_main_loop();
        if (i == 8)
        {
            digitalWrite(beethduino.RESTART_BPM_BUTTON_PIN, LOW);
        }
    }
    
    assert (beethduino.last_pressed_button_pin == 0);
    
    assert (beethduino.is_buzzer_muted == true);
   
    assert (beethduino.bpm == 60);
    assert (beethduino.bpm_modifier == 1);
    assert (beethduino.bpm_freq_req_iter == 975);
    
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRADD BPM: 60");
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