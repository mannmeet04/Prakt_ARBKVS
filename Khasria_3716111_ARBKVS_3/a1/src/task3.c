/*
 * task3.c
 *
 * LED bar game: Run a light from left to right and vice versa with increasing speed,
 * the player has to press the button in time to change direction. Pressing is allowed
 * while the two outermost LEDs are on
 *
 * Created: 19.07.2024 14:09:26
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "tasks.h"
#include "ledBar.h"
#include "button.h"
#include "sevenSeg.h"

//! Game level
uint8_t level;

//! Forward declarations
void task3_init();
gameover_t task3_game();

/*!
 * Main task that starts and ends a game
 */
void task3()
{
	// Init ports
	task3_init();
	
	while (1)
	{
		// Play game
		gameover_t result = task3_game();
		
		// Game over animation
		gameOverAnimation(result);
		
		// Show reached level (display level / 2)
		showScore(level);
	}
}

/*!
 * Initializes PORTs
 */
void task3_init()
{
	ledBar_init();
	button_init();
	sevenSeg_init();
}

/*!
 * Game logic
 */
gameover_t task3_game()
{

    uint8_t current_level = 0;
    
    while(!button_waitForPressRelease(1)); 
    
    uint16_t ledBar = 1;                     
    direction_t direction = DIR_LEFT;        
    float delay_ms_float = DELAY_INITIAL_MS; 
    
    sevenSeg_displayDecimal(current_level);


    while (1)
    {
        if (ledBar == 0 || ledBar == 0x0400) { // 2^10 =  1024 = 0x400
            level = current_level;
            return GAME_OVER_OUT_OF_BOUNDS; // grenze erreicht
        }

        // Zustand ausgeben
        ledBar_set(ledBar);
        sevenSeg_displayDecimal(current_level);
        
        uint16_t timeout_ms = (uint16_t)delay_ms_float;
        bool pressed = button_waitForPressRelease(timeout_ms); // in der zeit auf tastendruck warten

        
        if (pressed) {

            // zu früh gedrückt             
            if (ledBar & LED_BAR_INNER) {
                level = current_level;
                return GAME_OVER_TOO_EARLY;
            }
            
            // level erhöhen
            current_level++; 

            // Geschwindigkeit erhöhen
            delay_ms_float *= DELAY_DECREMENT_FACTOR;
            
            // Richtung wechseln
            if (direction == DIR_LEFT) {
                direction = DIR_RIGHT;
            } else {
                direction = DIR_LEFT;
            }
            
        }
        // LED verschieben
        if (direction == DIR_RIGHT) {
            ledBar >>= 1;
        } else {
            ledBar <<= 1;
        }  
    }
}