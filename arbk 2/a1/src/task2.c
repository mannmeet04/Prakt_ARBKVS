/*
 * task2.c
 *
 * LED bar animation: Run a light from left to right and vice versa with increasing speed
 *
 * Created: 18.07.2024 15:53:14
 * Author : Fachbereich 5 - FH Aachen
 */
#include "tasks.h"
#include "ledBar.h"
#include "button.h"

//! Forward declarations
void task2_init();
void task2_barAnimation();

/*!
 * Main task that starts and ends a game
 */
void task2()
{
	// Init ports
	task2_init();
	
	while (1) { task2_barAnimation(); }
}

/*!
 * Initializes PORTs
 */
void task2_init()
{
	ledBar_init();
	button_init();
}

/*!
 * Animation of the LED bar
 */
void task2_barAnimation(void)
{
	// Current state of the LED bar
	
	// LED shift direction
	
	// Shift delay of game level 0 in ms
	
	// Start: wait for button press and release
	
	while (1)
	{

        while (gbi(PINC, PINC5));  // warte bis taste gedrückt wird
        while (!gbi(PINC, PINC5));  // warte bis taste losgelassen wird

        uint16_t ledBar = 1; // eine LED an Anfang einschalten
        direction_t direction = DIR_LEFT;    // am anfang nach links verschieben 
        float delay_ms_float = DELAY_INITIAL_MS; // start geschwindigkeit

        // Haupt
        while (delay_ms_float >= 2.0f) 
        {
            
            // Zustand 1 LED Bar setzen
            ledBar_set(ledBar);

           // 200ms warten dann aber decremental 
            uint16_t delay_ms_int = (uint16_t)delay_ms_float;
            for (uint16_t i = 0; i < delay_ms_int; i++) {
                _delay_ms(1);
            }
            // Richtung wechseln nach links
            if ((ledBar & (1 << 0)) && (direction == DIR_RIGHT)) {
                delay_ms_float *= DELAY_DECREMENT_FACTOR; 
                direction = DIR_LEFT;
            } 
            // Richtung wechseln nach rechts
            else if ((ledBar & (1 << 9)) && (direction == DIR_LEFT)) {
                delay_ms_float *= DELAY_DECREMENT_FACTOR; 
                direction = DIR_RIGHT;
            }

            if (direction == DIR_RIGHT) {
                ledBar >>= 1;  // nach rechts verschieben
            } else { 
                ledBar <<= 1; 
            }
        } 
        ledBar_set(LED_MAX_VALUE); 
    }
    
}