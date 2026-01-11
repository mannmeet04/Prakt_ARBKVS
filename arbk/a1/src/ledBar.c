/*
 * ledBar.c
 *
 * Created: 14.08.2024 16:26:52
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "ledBar.h"
#include <avr/io.h>
#include "util.h"

/*!
 * Initialized PORTs connected to the LED bar
 */
void ledBar_init()
{
	DDRD = 0xFF;//0b11111111;  D0 bis D7)

    DDRB |= 0x03; //0bxxxxxx11;  B0 bis B1
}

/*!
 * Writes the LED bar to the PORTs
 */
void ledBar_set(uint16_t leds)
{

    PORTD = leds & 0xFF; // unteren bits auf PORTD 
    //PORTB = (leds >> 8 ) & 0x03;

    // durch gbi den zustand 0/1 aus Led 8te bit holen und auf PORTB0 aktualisieren
    ubi(PORTB, PORTB0, gbi(leds, 8)); 

    ubi(PORTB, PORTB1, gbi(leds, 9));
}

/*!
 * Takes a number from 0 to 10 and returns a bar with the given number of ones
 */
uint16_t bar(uint8_t n) { return ((int16_t)0x8000 >> (15 - n)) ^ 0xFFFF; }

/*!
 * Writes a value in percent as bar-graph
 */
void ledBar_setProgress(uint8_t percent)
{
	// Round 0 - 100 to 0 - 10 and get a bar graph 
	ledBar_set(bar((percent + 5) / 10));
}