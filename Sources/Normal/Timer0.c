/**
 * @file     Timer0.c
 * @brief    Timer0 Initialization for Normal Mode on AVR Microcontrollers
 * @note     This file provides functions to initialize and manage Timer0 in Normal mode 
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
 * @brief Interrupt Service Routine for Timer0 Overflow
 * 
 * @note **Important**: For the interrupt to work, `globalInt_Enable` must be called to enable global interrupts. 
 *       Alternatively, you can set the I-bit (Interrupt Enable) in the `SREG` (Status Register) manually by writing `1` to the I-bit.
 */
ISR(TIMER0_OVF_vect)
{
    /* Place your code here */

    TCNT0 = Timer0_intValue;    /**< Reset Timer0 counter to predefined value */
};


/**
 * @brief Initializes Timer0 in normal mode.
 * 
 * This function is used to configure and initialize Timer0 for normal operation. 
 * Timer0 will run without any prescaler settings and will increment every clock cycle. 
 * The function takes a boolean input to determine whether the timer should be initialized or not.
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the Timer0 peripheral.
 * 
 */
void Timer0_Init(bool _initStatus)
{
    if(_initStatus)
    {
        /* Configure Timer0 for Normal Mode (Mode 0) */
        bitClear(TCCR0A, WGM00);
        bitClear(TCCR0A, WGM01);
        bitClear(TCCR0B, WGM02);

        /* Set Prescaler = 64 for a timer frequency of 250 KHz (assuming a 16 MHz system clock) */
        bitSet  (TCCR0B, CS00);
        bitSet  (TCCR0B, CS01);
        bitClear(TCCR0B, CS02);

        bitSet  (TIMSK0, TOIE0);  /**< Enable Timer0 overflow interrupt */

        intFlag_clear(TIFR0, TOIE0); /**< Clear Timer0 overflow interrupt flag */

        TCNT0 = Timer0_intValue;  /**< Initialize the Timer0 counter to the predefined value */
    }
    else
    {
        /* Deinitialize Timer0: Reset all control and configuration bits */
        bitClear(TCCR0A, WGM00);
        bitClear(TCCR0A, WGM01);
        bitClear(TCCR0B, WGM02);
        bitClear(TCCR0B, CS00);
        bitClear(TCCR0B, CS01);
        bitClear(TCCR0B, CS02);

        bitSet  (TIMSK0, TOIE0);  /**< Enable Timer0 overflow interrupt */

        TCNT0 = 0;
    };
};
