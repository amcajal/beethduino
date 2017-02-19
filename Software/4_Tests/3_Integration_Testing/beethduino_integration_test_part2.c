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
    Serial.println("INTEGRATION TESTING part 2 STARTED\n*********************");
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
    test_unmute_buzzer();
    test_bpm_frequency();                      
    test_restart_state();
    test_bpm_upper_limit();
    test_bpm_lower_limit();
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


void test_unmute_buzzer()
{
    Serial.println("test_unmute_buzzer");
    
    digitalWrite(beethduino.MUTE_BUZZER_BUTTON_PIN, HIGH);
    
    /* Arbitrary number of iterations. */
    for (int i = 0; i < 10; i++)
    {
        beethduino.exec_main_loop();
        if (i == 8)
        {
            digitalWrite(beethduino.MUTE_BUZZER_BUTTON_PIN, LOW);
        }
    }
    
    assert (beethduino.last_pressed_button_pin == 0);
    
    assert (beethduino.is_buzzer_muted == false);
    
    assert (beethduino.buzzer_bips == 0);
    assert (beethduino.iteration_counter == 1); /* Iteration counter now shall 
                                                * be one, because the software 
                                                * has entered in the 
                                                * process_bpm_frequency.
                                                */
   
    assert (beethduino.bpm == 60);
    assert (beethduino.bpm_modifier == 1);
    assert (beethduino.bpm_freq_req_iter == 975);
    
    /* First line now has no characters. */
    assert (beethduino.bpm_text_info == "LFCRADD BPM: 60");
}


void test_bpm_frequency()
{
    Serial.println("test_bpm_frequency");
    
    /* bpm_freq_req_iter is now 975. The previous test (test_unmute_buzzer)
    * executed the process_bpm_frequency one time, so iteration_counter is
    * now '1'. This for loop will increase its value up to 974.
    */
    for (int i = 0; i <= 972; i++)
    {
        beethduino.exec_main_loop();
    }
    
    assert (beethduino.buzzer_bips == 0);
    assert (beethduino.iteration_counter == 974);
    
    /* Fulfil the required iterations, and make the buzzer "bip" once. */
    beethduino.exec_main_loop();
    assert (beethduino.buzzer_bips == 1);
    assert (beethduino.iteration_counter == 0);
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

    /* buzzer_bips is a variable with testing purposes; no need to check here.*/
    
    assert (beethduino.iteration_counter == 9); /* Because buzzer is not muted
                                                * iteration_counter still
                                                * being updated in the previous
                                                * for loop.
                                                */
   
    assert (beethduino.bpm == 60);
    assert (beethduino.bpm_modifier == 1);
    assert (beethduino.bpm_freq_req_iter == 975);
    
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRADD BPM: 60");
}


void test_bpm_upper_limit()
{
    Serial.println("test_bpm_upper_limit");
    
    /* Increase BPM enough times to force the bound checkings 
    * inside update_bpm process. In this case, the button is pressed 50 times.
    */    
    for (int i = 0; i < 99; i++)
    {
        if (i%2 == 0)
        {
            digitalWrite(beethduino.CHANGE_BPM_BY_TEN_BUTTON_PIN, HIGH);
        }
        else
        {
            digitalWrite(beethduino.CHANGE_BPM_BY_TEN_BUTTON_PIN, LOW);
        }
        beethduino.exec_main_loop();
    }
    
    assert (beethduino.bpm == 300);
    assert (beethduino.bpm_freq_req_iter == 175);
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRADD BPM: 300");
    
}


void test_bpm_lower_limit()
{
    Serial.println("test_bpm_lower_limit");

    /* Button pressing is simulated to simplify test. */
    beethduino.bpm_modifier = -1;
    
    for (int j = 0; j < 199; j++)
    {
        if (j%2 == 0)
        {
            digitalWrite(beethduino.CHANGE_BPM_BY_TEN_BUTTON_PIN, HIGH);
        }
        else
        {
            digitalWrite(beethduino.CHANGE_BPM_BY_TEN_BUTTON_PIN, LOW);
        }
        beethduino.exec_main_loop();
    }
    
    assert (beethduino.bpm == 1);
    assert (beethduino.bpm_freq_req_iter == 59975);
    assert (beethduino.bpm_text_info == "MUTE_MUTE_MUTE_LFCRSUB BPM: 1");
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