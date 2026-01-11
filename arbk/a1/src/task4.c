/*
 * task4.c
 *
 * ADC: Convert a voltage and display it on the seven segment and on the LED bar
 *
 * Created: 19.07.2024 15:03:03
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "tasks.h"
#include "adc.h"
#include "sevenSeg.h"
#include "ledBar.h"

/*!
 * Display poti value on led-bar and 7-segments
 */
void task4()
{
	ledBar_init();
	adc_init();
	sevenSeg_init();
	
	while (1)
	{

    uint16_t adcValue = adc_getValue();

    // mitte 2,5v -> 512, dann 512/1023 * 10 = 5 leds
    uint8_t ledsOn = (uint8_t)(((float)adcValue / 1023.0f) * 10.1f);


    // (1 << 3) -1 = 0000 0111 mit 3 leds an statt 0000 1000
    uint16_t ledMask = 0;
    ledMask = (1 << ledsOn) - 1;
    ledBar_set(ledMask);

    // 512/1023=0,5 * 5,0 = 2,5v
    float voltage = ((float)adcValue / 1023.0f) * 5.0f;
    
    sevenSeg_displayFloat(voltage);
    _delay_ms(100);

    }
}

/* void task4_loop()
{
    // adc_getValue() liefert 0 (0V) bis 1023 (5V)
    uint16_t adcValue = adc_getValue();

    // mitte 2,5v -> 512, dann 512/1023 * 10 = 5 leds
    uint8_t ledsOn = (uint8_t)(((float)adcValue / 1023.0f) * 10.1f);


    // mit 5 werden die dann an 5te stelle angeschaltet
    uint16_t ledMask = 0;
    if (ledsOn > 0) {
        ledMask = (1 << ledsOn) - 1;
    }
    
    ledBar_set(ledMask);

    // 512/1023=0,5 * 5,0 = 2,5v
    float voltage = ((float)adcValue / 1023.0f) * 5.0f;
    
    sevenSeg_displayFloat(voltage);
} */