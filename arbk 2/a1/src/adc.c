/*
 * adc.c
 *
 * Created: 19.07.2024 14:46:29
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "adc.h"
#include "util.h"
#include <avr/io.h>

/*!
 * This method initializes the necessary registers for using the ADC module.
 * Reference voltage:    internal
 * Input channel:        PORTA7
 * Conversion frequency: 125kHz
 */
void adc_init()
{

    ADMUX = 0x00; 
    //AVCC Refspannung 5V, kanal auf ADC7 (PORTA7)
    ADMUX |= (1<<REFS0)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0); 
    // Prescaler auf 128 setzen für 125kHz bei 16MHz Takt
    // Start Conversion, zündung
    // aden, hauptschalter
    // free running mode, dauerbetrieb
    ADCSRA |=(1<<ADPS2)|(1<<ADPS1) | (1<<ADPS0)| (1<<ADSC) | (1<<ADEN) | (1<<ADATE); 


}

/*!
 * Returns the ADC value of the last conversion
 * \return The converted voltage (0 = 0V, 1023 = AVCC)
 */
uint16_t adc_getValue()
{
    return ADC;
}