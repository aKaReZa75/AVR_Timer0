/**
 * @file     Timer0.h
 * @brief    Timer0 Initialization for CTC Mode on AVR Microcontrollers
 * @note     This file provides functions to initialize and manage Timer0 in CTC mode 
 *           for AVR microcontrollers, specifically for ATmega328 and similar models.
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     For detailed explanations of this library, along with additional notes and examples of usage, 
 *           please visit the following repository:
 *           https://github.com/aKaReZa75/AVR_Timer0
 */

#include "Timer0.h"


/**
 * @brief Interrupt Service Routine for Timer0 Compare Match A
 * 
 * @note **Important**: For the interrupt to work, `globalInt_Enable` must be called to enable global interrupts. 
 *       Alternatively, you can set the I-bit (Interrupt Enable) in the `SREG` (Status Register) manually by writing `1` to the I-bit.
 */
ISR(TIMER0_COMPA_vect)
{
    /* Place your code here */
};


/**
 * @brief Interrupt Service Routine for Timer0 Compare Match B
 * 
 * @note **Important**: For the interrupt to work, `globalInt_Enable` must be called to enable global interrupts. 
 *       Alternatively, you can set the I-bit (Interrupt Enable) in the `SREG` (Status Register) manually by writing `1` to the I-bit.
 */
ISR(TIMER0_COMPB_vect)
{
    /* Place your code here */
};


/**
 * @brief Initializes or deinitializes Timer0 in CTC mode.
 * 
 * This function configures Timer0 to operate in CTC (Clear Timer on Compare Match) mode, 
 * where the timer counts from 0 to a specified value (OCR0A). When the timer matches 
 * this value, it resets to 0 and triggers an interrupt if enabled. 
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the Timer0 peripheral.
 * 
 * @note The prescaler is set to 64, resulting in a timer clock frequency of 250 kHz (with a 16 MHz system clock).
 *       The function configures OCR0A and OCR0B for generating timing intervals of 1ms and 1ms, respectively.
 *       If you only need one output (e.g., `OC0A`), you can modify the code accordingly to disable `OC0B`.
 */
void Timer0_Init(bool _initStatus)
{
    if(_initStatus)
    {
        /* Configure Timer0 in CTC mode (Mode 2) */
        bitClear(TCCR0A, WGM00);
        bitSet  (TCCR0A, WGM01);
        bitClear(TCCR0B, WGM02);

        /* Configure OC0A in toggle mode */
        bitSet  (TCCR0A, COM0A0);
        bitClear(TCCR0A, COM0A1);

        /* Configure OC0B in toggle mode */
        bitSet  (TCCR0A, COM0B0);
        bitClear(TCCR0A, COM0B1);

        GPIO_Config_OUTPUT(OC0A_Config, OC0A_Pin);  /**< Set pin PD6 (OC0A) as output */
        GPIO_Config_OUTPUT(OC0B_Config, OC0B_Pin);  /**< Set pin PD5 (OC0B) as output */

        // Prescaler = 64 => 16Mhz/64=250KHz
        /* Set Prescaler = 64 => Timer clock frequency = 16MHz/64 = 250 kHz */
        bitSet  (TCCR0B, CS00);
        bitSet  (TCCR0B, CS01);
        bitClear(TCCR0B, CS02);

        bitSet(TIMSK0, OCIE0A); /**< Enable Compare Match A interrupt */
        bitSet(TIMSK0, OCIE0B); /**< Enable Compare Match B interrupt */

        /* Clear the interrupt flags for Compare Match A and B */
        intFlag_clear(TIFR0, OCF0A);
        intFlag_clear(TIFR0, OCF0B);

        OCR0A = 249;  /**< 1ms interval */
        OCR0B = 124;  /**< 1ms interval */  
    }
    else
    {
        /* Deinitialize Timer0 and reset all settings */
        bitClear(TCCR0A, WGM00);
        bitClear(TCCR0A, WGM01);
        bitClear(TCCR0B, WGM02);
        bitClear(TCCR0A, COM0A0);
        bitClear(TCCR0A, COM0A1);
        bitClear(TCCR0B, COM0B0);
        bitClear(TCCR0B, COM0B1);
        GPIO_Config_INPUT(OC0A_Config, OC0A_Pin); 
        GPIO_Config_INPUT(OC0B_Config, OC0B_Pin); 
        bitClear(TCCR0B, CS00);
        bitClear(TCCR0B, CS01);
        bitClear(TCCR0B, CS02);
        bitClear(TIMSK0, OCIE0A); 
        bitClear(TIMSK0, OCIE0B);
        OCR0A = 0; 
        OCR0B = 0;   
    };
};
