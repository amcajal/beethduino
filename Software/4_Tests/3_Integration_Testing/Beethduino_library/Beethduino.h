/*******************************************************************************
*   Project:        Beethduino, an Arduino Do-it-yourself electronic metronome.
*
*   File:           Beethduino.h         
*
*   Description:    Header file of Beethduino library. The library contains
*                   the exact same code than the main code (final functionality
*                   executed in the Arduino), but adapted to be easely called
*                   and tested in the integration test files. Modifications
*                   respect to the original code includes additional variables,
*                   methods and behaviour changes, all with testing purposes.
*
*   Language:       Arduino (C/C++ set, compatible with avr-g++).
*                   Compiled in Arduino IDE, version 1.6.13
*
*   Dependencies:   Arduino.h 
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

#ifndef Beethduino_h
#define Beethduino_h

#include "Arduino.h"

class Beethduino
{
    /* All variables and methods are public to made the integration
    * testing easier; in this way, no getters and setters are required to access 
    * the many variables that must to be checked to assert the test conditions.
    */
    public:
        /* VARIABLES */
        const int MUTE_BUZZER_BUTTON_PIN        = 13;              
        const int CHANGE_BPM_BY_TEN_BUTTON_PIN  = 12;                                             
        const int CHANGE_BPM_BY_ONE_BUTTON_PIN  = 11;                                        
        const int ADD_OR_SUB_BPM_BUTTON_PIN     = 10;       
        const int RESTART_BPM_BUTTON_PIN        = 9;    
        const int ACTIVE_BUZZER_PIN             = 8; 
        
        const int BPM_UPPER_BOUND               = 300;
        const int BPM_LOWER_BOUND               = 1;

        const int SOUND_DURATION                = 25;
        const int MILLISECONDS_IN_SECOND        = 1000; 
          
        const double SECONDS_IN_MINUTE = 60.00;
        
        int last_pressed_button_pin;
        int bpm;
        int bpm_modifier;
        int iteration_counter;
        
        int buzzer_bips;    /* Count number of times buzzer has "bip" while 
                            * it was unmuted. Variable used only in testing; 
                            * it shall not appear in the final software.
                            */

        unsigned int bpm_freq_req_iter;
        
        String bpm_text_info;   /* Text to be shown in the LCD, loaded in a 
                                * string to allow testing operations.
                                * Variable used only in testing; 
                                * it shall not appear in the final software.
                                */
                                                   
        boolean is_buzzer_muted;

        
        /* METHODS */
        Beethduino();
        void exec_main_loop();
        void check_button_pressing();
        void detect_single_pulsation(int pin_to_check);
        void perform_operation(int pin_to_check);
        void reset_bpm();
        void invert_bpm_modifier();
        void update_bpm(int value);
        void calculate_required_iterations();
        void change_mute_state();
        void update_lcd();
        void update_serial_monitor(); /* Simulation of LCD operations. */
        void process_bpm_frequency();
        void play_buzzer();
};

#endif