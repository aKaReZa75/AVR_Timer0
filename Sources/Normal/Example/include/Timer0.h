/**
 * @file     Timer0.h
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

#ifndef _Timer0_H_
#define _Timer0_H_

#include "aKaReZa.h"


/**
 * @brief Defines the default value for Timer0 interrupt.
 * 
 * This macro defines the initial value for the Timer0 interrupt. It plays a role in determining 
 * the overflow duration of Timer0 based on the system clock frequency and the prescaler settings.
 * 
 * @note To achieve desired timing intervals, this value may need to be adjusted according to 
 *       the system clock frequency and specific application requirements. The interrupt value 
 *       determines how frequently the timer overflows, so careful tuning is necessary for precise 
 *       timing intervals.
 */
#define Timer0_intValue 6


#define OC0A_Config  DDRD  /**< Define DDRD as the configuration register for OC0A */
#define OC0A_Control PORTD /**< Define PORTD as the control register for OC0A */
#define OC0A_Pin     6     /**< Define Pin 6 as the OC0A output pin */

#define OC0B_Config DDRD   /**< Define DDRD as the configuration register for OC0B */
#define OC0A_Control PORTD /**< Define PORTD as the control register for OC0B */
#define OC0B_Pin    5      /**< Define Pin 5 as the OC0B output pin */


/**
 * @brief Initializes Timer0 in normal mode.
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the Timer0 peripheral.
 * 
 */
void Timer0_Init(bool _initStatus);


#endif