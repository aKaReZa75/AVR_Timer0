# Timer-Counter 0 in AVR Microcontrollers

Timer/Counter 0 is one of the timers integrated into the ATmega328 microcontroller. It is an 8-bit timer used to generate precise time delays, measure time intervals, and produce PWM (Pulse Width Modulation) signals. This timer can be configured in different modes, including normal, CTC (Clear Timer on Compare Match), and PWM (Pulse Width Modulation) modes. It is commonly used for generating time delays, controlling motors, and generating specific frequencies in embedded systems.

<table>
  <tr>
  <td valign="top">
  
  > [!TIP]  
  > If you're looking to better understand how to navigate and use my GitHub repositories — including exploring their structure, downloading or cloning projects, submitting issues, and asking questions,  
  > everything you need is clearly explained in this video:  
  > [aKaReZa 95 - Programming, Git - PART B](https://youtu.be/zYiUItVFRqQ)  
  > Make sure to check it out!
  
  </td>
    <td width="360" valign="middle" style="padding: 0;">
      <a href="https://youtu.be/zYiUItVFRqQ">
       <img src="https://img.youtube.com/vi/zYiUItVFRqQ/maxresdefault.jpg"
             width="360"
             alt="aKaReZa 95 - Programming, Git - PART B Thumbnail"/>
      </a>
    </td>

  </td>
  </tr>
  <tr>
  <td colspan="2">

  > [!CAUTION]
  > It is absolutely critical that you carefully read every single word of this document, line by line, to ensure you don't miss any details. Nothing can be overlooked.
      
  </td>
  </tr>  
</table>

# Registers

Here is a list of the relevant registers for Timer/Counter 0, along with detailed descriptions of each bit:

## **TCCR0A (Timer/Counter Control Register A)**

| Bit | Description |
| --- | ----------- |
| 7   | COM0A1 (Compare Output Mode for Channel A) |
| 6   | COM0A0 (Compare Output Mode for Channel A) |
| 5   | COM0B1 (Compare Output Mode for Channel B) |
| 4   | COM0B0 (Compare Output Mode for Channel B) |
| 3   | Reserved |
| 2   | Reserved |
| 1   | WGM01 (Waveform Generation Mode) |
| 2   | WGM00 (Waveform Generation Mode) |

### **WGM02/WGM01/WGM00 (Waveform Generation Mode)**

These bits select the waveform generation mode of the timer. The possible configurations are:

> [!CAUTION]
The WGM02 bit is located in the TCCR0B register.

| **Mode** | **WGM02** | **WGM01** | **WGM00** | **Timer/Counter Mode of Operation** | **TOP**  | **Update of OCRx at** | **TOV Flag Set on** |
|----------|-----------|-----------|-----------|-------------------------------------|----------|-----------------------|---------------------|
| 0        | 0         | 0         | 0         | Normal                              | 0xFF     | Immediate             | MAX                 |
| 1        | 0         | 0         | 1         | PWM, Phase Correct                 | 0xFF     | TOP                   | BOTTOM              |
| 2        | 0         | 1         | 0         | CTC                                 | OCR0A    | Immediate             | MAX                 |
| 3        | 0         | 1         | 1         | Fast PWM                            | 0xFF     | BOTTOM                | MAX                 |
| 4        | 1         | 0         | 0         | Reserved                           | -        | -                     | -                   |
| 5        | 1         | 0         | 1         | PWM, Phase Correct                 | OCR0A    | TOP                   | BOTTOM              |
| 6        | 1         | 1         | 0         | Reserved                           | -        | -                     | -                   |
| 7        | 1         | 1         | 1         | Fast PWM                            | OCR0A    | BOTTOM                | TOP                 |
 
* **MAX** = 0xFF   
* **BOTTOM** = 0x00

> [!CAUTION]
Pay close attention to the Update of OCRx at column. This is crucial for accurate timer operation, and failing to consider it could cause timing issues or unexpected behavior in your application.

---
#### **Mode 0: Normal Mode**
The timer counts from 0 to 255, and the overflow flag (TOV0) is set when it reaches 255+1.
```c
/* Configure Timer0 for Normal Mode (Mode 0) */
bitClear(TCCR0A, WGM00);
bitClear(TCCR0A, WGM01);
bitClear(TCCR0B, WGM02);
```
Useful for simple delay or overflow interrupt generation.

---
#### **Mode 1: PWM, Phase Correct (TOP = 0xFF)**
The timer counts up to 255 then down to 0, creating a symmetrical PWM waveform.   
TOV flag set at **BOTTOM**, OCR0x updated at **TOP**.
```c
/* Configure Timer0 for PWM, Phase Correct (Mode 1) */
bitSet(TCCR0A, WGM00);
bitClear(TCCR0A, WGM01);
bitClear(TCCR0B, WGM02);
```
Suitable for power electronics or motor control where center-aligned PWM is preferred.

---
#### **Mode 2: CTC (Clear Timer on Compare Match)**
Timer counts up until it matches **OCR0A**, then resets.   
OCR0A defines the TOP.

```c
/* Configure Timer0 for CTC Mode (Mode 2) */
bitClear(TCCR0A, WGM00);
bitSet(TCCR0A, WGM01);
bitClear(TCCR0B, WGM02);
```
Ideal for precise time base or square wave generation.

---
#### **Mode 3: Fast PWM (TOP = 0xFF)**
Timer counts from 0 to 255.   
TOV flag set at **TOP**, OCR0x updated at **BOTTOM**.
```c
/* Configure Timer0 for Fast PWM (Mode 3) */
bitSet(TCCR0A, WGM00);
bitSet(TCCR0A, WGM01);
bitClear(TCCR0B, WGM02);
```
Used for generating high-frequency PWM signals with less resolution.

---
#### **Mode 4: Reserved**
> [!CAUTION]
> This mode is reserved and should not be used.

---
#### **Mode 5: PWM, Phase Correct (TOP = OCR0A)**
The timer counts up and down, OCR0A is used as TOP.   
TOV flag set at **BOTTOM**, OCR0x updated at **TOP**.
```c
/* Configure Timer0 for Phase Correct PWM (Mode 5) with TOP = OCR0A */
bitSet(TCCR0A, WGM00);
bitClear(TCCR0A, WGM01);
bitSet(TCCR0B, WGM02);
```
Provides flexible duty cycle with variable resolution.

---
#### **Mode 6: Reserved**
> [!CAUTION]
> This mode is reserved and should not be used.

---
#### **Mode 7: Fast PWM (TOP = OCR0A)**
Timer counts from 0 to OCR0A.   
TOV flag set at **TOP**, OCR0x updated at **BOTTOM**.
```c
/* Configure Timer0 for Fast PWM (Mode 7) with TOP = OCR0A */
bitSet(TCCR0A, WGM00);
bitSet(TCCR0A, WGM01);
bitSet(TCCR0B, WGM02);
```
Used when you need fast PWM with a configurable top value.

---
> [!TIP]
The x can be either A or B, depending on whether you are configuring Channel A (OC0A) or Channel B (OC0B).

### **Compare Output Mode, non-PWM Mode**

| **COM0x1** | **COM0x0** | **Description**                                              |
|------------|------------|--------------------------------------------------------------|
| 0          | 0          | Normal port operation, OCxA disconnected.                    |
| 0          | 1          | Toggle OCxA on Compare Match.                                |
| 1          | 0          | Clear OCxA on Compare Match.                                 |
| 1          | 1          | Set OCxA on Compare Match.                                   |

### **Compare Output Mode, Fast PWM Mode**

| **COM0x1** | **COM0x0** | **Description**                                                     |
|------------|------------|---------------------------------------------------------------------|
| 0          | 0          | Normal port operation, OC0x disconnected.                           |
| 0          | 1          | WGM02 = 0: Normal Port Operation, OC0x Disconnected. WGM02 = 1: Toggle OC0x on Compare Match. |
| 1          | 0          | Clear OC0x on Compare Match, set OC0x at BOTTOM (non-inverting mode). |
| 1          | 1          | Set OC0x on Compare Match, clear OC0x at BOTTOM (inverting mode).   |

> [!NOTE] 
A special case occurs when **OCR0x** equals **TOP** and **COM0x1** is set. In this case, the compare match is ignored, but the set or clear is done at **BOTTOM**.

### **Compare Output Mode, Phase Correct PWM Mode**

| **COM0x1** | **COM0x0** | **Description**                                                       |
|------------|------------|-----------------------------------------------------------------------|
| 0          | 0          | Normal port operation, OC0x disconnected.                             |
| 0          | 1          | WGM02 = 0: Normal Port Operation, OC0x Disconnected. WGM02 = 1: Toggle OC0x on Compare Match. |
| 1          | 0          | Clear OC0x on Compare Match when up-counting. Set OC0x on Compare Match when down-counting. |
| 1          | 1          | Set OC0x on Compare Match when up-counting. Clear OC0x on Compare Match when down-counting. |

> [!NOTE] 
A special case occurs when **OCR0x** equals **TOP** and **COM0x1** is set. In this case, the compare match is ignored, but the set or clear is done at **TOP**.

---
### Compare Output Mode — Normal Operation
* Timer used for internal timing only (no waveform on output pins)
* Suitable for `Normal Mode`, `CTC`, or `PWM` when no output pin is needed
```c
/* Normal Operation (OC0A disconnected) */
bitClear(TCCR0A, COM0A1);
bitClear(TCCR0A, COM0A0);

/* Normal Operation (OC0B disconnected) */
bitClear(TCCR0A, COM0B1);
bitClear(TCCR0A, COM0B0);
```

---
### Compare Output Mode — Toggle
* Generate square waves for frequency testing or simple waveform generation
* Works in `CTC` mode
* In `Fast PWM` or `Phase Correct PWM`, only works when `WGM02 = 1` (toggle on match with OCRx)
```c
/* Toggle OC0A on Compare Match */
bitClear(TCCR0A, COM0A1);
bitSet(TCCR0A, COM0A0);

/* Toggle OC0B on Compare Match */
bitClear(TCCR0A, COM0B1);
bitSet(TCCR0A, COM0B0);
```


---

### Compare Output Mode — Non-Inverting
* Standard PWM signal generation
* Output is HIGH at BOTTOM, LOW when TCNT0 = OCR0x
* Used to drive motors, LEDs, or other analog devices using PWM
* Very common for controlling power (e.g., speed, brightness)
```c
/* Non-Inverting PWM Output (Clear OC0A on Compare Match) */
bitSet(TCCR0A, COM0A1);
bitClear(TCCR0A, COM0A0);

/* Non-Inverting PWM Output (Clear OC0B on Compare Match) */
bitSet(TCCR0A, COM0B1);
bitClear(TCCR0A, COM0B0);
```

---
### Compare Output Mode — Inverting
* Inverted PWM generation
* Output is LOW at BOTTOM, HIGH when TCNT0 = OCR0x
* Used when complementary waveforms are needed (e.g., H-bridge drivers, special dimming effects)
```c
/* Inverting PWM Output (Set OC0A on Compare Match) */
bitSet(TCCR0A, COM0A1);
bitSet(TCCR0A, COM0A0);

/* Inverting PWM Output (Set OC0B on Compare Match) */
bitSet(TCCR0A, COM0B1);
bitSet(TCCR0A, COM0B0);
```

---
## **TCCR0B (Timer/Counter Control Register B)**

| Bit | Description |
| --- | ----------- |
| 7   | FOC0A (Force Output Compare A) |
| 6   | FOC0B (Force Output Compare B) |
| 5   | Reserved |
| 4   | Reserved |
| 3   | WGM02 (Waveform Generation Mode) |
| 2   | CS02 (Clock Select) |
| 1   | CS01 (Clock Select) |
| 0   | CS00 (Clock Select) |

> [!NOTE]
> **WGM02**: Combines with WGM01 and WGM00 from TCCR0A to define the waveform generation mode.

---
### **FOC0A / FOC0B (Force Output Compare)**
Force an immediate Compare Match on channel A or B, only used in **non-PWM modes**. Useful when you want to trigger an output compare action via software.

```c
/* Force Compare Match on Channel A */
bitSet(TCCR0B, FOC0A);

/* Force Compare Match on Channel B */
bitSet(TCCR0B, FOC0B);
```

### **Clock Select Bit Description**
Determine the clock source for the timer (e.g., No clock, prescaler, etc.).

| **CS02** | **CS01** | **CS00** | **Description**                                           |
|----------|----------|----------|-----------------------------------------------------------|
| 0        | 0        | 0        | No clock source (Timer/Counter stopped)                   |
| 0        | 0        | 1        | clk_I/O (No prescaling)                                  |
| 0        | 1        | 0        | clk_I/O / 8 (From prescaler)                              |
| 0        | 1        | 1        | clk_I/O / 64 (From prescaler)                             |
| 1        | 0        | 0        | clk_I/O / 256 (From prescaler)                            |
| 1        | 0        | 1        | clk_I/O / 1024 (From prescaler)                           |
| 1        | 1        | 0        | External clock source on T0 pin. Clock on falling edge.  |
| 1        | 1        | 1        | External clock source on T0 pin. Clock on rising edge.   |

> [!TIP]
> Use external clocking when Timer0 acts as a **counter** to count external events.
> Rising or falling edge options allow flexibility in signal synchronization.

#### **No clock source**
```c
/* Stop Timer (No clock source) */
bitClear(TCCR0B, CS00);
bitClear(TCCR0B, CS01);
bitClear(TCCR0B, CS02);
```
* Timer completely off
* Useful for disabling the timer or saving power
  
---
#### **clock source from Prescaler = 1**
```c
/* Set Prescaler = 1 => Timer clock frequency = 16MHz/1 = 16MHz */
bitSet(TCCR0B, CS00);
bitClear(TCCR0B, CS01);
bitClear(TCCR0B, CS02);
```

---
#### **clock source from Prescaler = 8**
```c
/* Set Prescaler = 8 => Timer clock frequency = 16MHz/8 = 2MHz */
bitClear(TCCR0B, CS00);
bitSet(TCCR0B, CS01);
bitClear(TCCR0B, CS02);
```

---
#### **clock source from Prescaler = 64**
```c
/* Set Prescaler = 64 => Timer clock frequency = 16MHz/64 = 256KHz */
bitSet(TCCR0B, CS00);
bitSet(TCCR0B, CS01);
bitClear(TCCR0B, CS02);
```

---
#### **clock source from Prescaler = 256**
```c
/* Set Prescaler = 256 => Timer clock frequency = 16MHz/256 = 256KHz */
bitClear(TCCR0B, CS00);
bitClear(TCCR0B, CS01);
bitSet(TCCR0B, CS02);
```

---
#### **clock source from T0 pin (Falling Edge)**
```c
/* 7. External Clock on Falling Edge (from T0 pin) */
bitClear(TCCR0B, CS00);
bitSet(TCCR0B, CS01);
bitSet(TCCR0B, CS02);
```

---
#### **clock source from T0 pin (Rising Edge)**
```c
/* 8. External Clock on Rising Edge (from T0 pin) */
bitSet(TCCR0B, CS00);
bitSet(TCCR0B, CS01);
bitSet(TCCR0B, CS02);
```

---
### Force Compare Match (FOC0A / FOC0B)
* Only works in **non-PWM** mode (e.g., CTC, Normal mode)
* Manually trigger output compare action
* Useful for testing or immediate interrupt trigger

```c
/* Force a Compare Match on OC0A */
bitSet(TCCR0B, FOC0A);

/* Force a Compare Match on OC0B */
bitSet(TCCR0B, FOC0B);
```

---

## **TIFR0 (Timer/Counter Interrupt Flag Register)**

| Bit | Name  | Description                             |
| --- | ----- | --------------------------------------- |
| 7–3 | —     | Reserved                                |
| 2   | OCF0B | Output Compare Match Flag for Channel B |
| 1   | OCF0A | Output Compare Match Flag for Channel A |
| 0   | TOV0  | Timer/Counter Overflow Flag             |

* **OCF0A / OCF0B**:
  Set when `TCNT0` matches `OCR0A` or `OCR0B`.

* **TOV0**:
  Set when Timer0 overflows (from `0xFF` to `0x00`). Also must be cleared by writing logic **1**.

> [!NOTE]
> Before enabling an interrupt, you should **manually clear the corresponding interrupt flag** in `TIFR0`.
Otherwise, if the flag is already set, the ISR will be triggered **immediately after `Enabling Global Interrupts`**, even if an actual event hasn't occurred yet.

> [!TIP]
> These flags must be manually cleared by writing a logic **1** to them. Writing 0 has no effect.    
> You can efficiently clear interrupt flags in `TIFR0` using the macro: `intFlag_clear(Reg, Bit)`   
> For example, to clear the **Timer/Counter Overflow Flag** (`TOV0`), you would write: intFlag_clear(TIFR0, TOV0);

---
  
## **TIMSK0 (Timer/Counter Interrupt Mask Register)**

| Bit | Name   | Description                               |
| --- | ------ | ----------------------------------------- |
| 7–3 | —      | Reserved                                  |
| 2   | OCIE0B | Output Compare Match Interrupt Enable (B) |
| 1   | OCIE0A | Output Compare Match Interrupt Enable (A) |
| 0   | TOIE0  | Timer Overflow Interrupt Enable           |

- **OCIE0B**: Enable interrupts on output compare matches for Channel B.
- **OCIE0A**: Enable interrupts on output compare matches for Channel A.
- **TOIE0**: Enable Timer/Counter overflow interrupt.

> [!CAUTION]
Always ensure that global interrupts are enabled using the `sei()` function. Without enabling global interrupts, the microcontroller will not respond to any interrupt triggers.  
The `sei()` function sets the Global Interrupt Flag (I-bit) in the Status Register (SREG), which allows interrupt requests to be processed by the microcontroller.

You can use the following macros to enable and disable global interrupts:

- **`globalInt_Enable`**: This macro is equivalent to calling `sei()`. It enables global interrupts, allowing the microcontroller to respond to interrupt requests.

- **`globalInt_Disable`**: This macro is equivalent to calling `cli()`. It disables global interrupts, preventing the microcontroller from processing any interrupts.

### Timer0 Overflow Interrupt
```c
/* ISR for Timer0 Overflow */
ISR(TIMER0_OVF_vect)
{
    /* Code executed on Timer0 overflow */
}

/**< Enable Compare Overflow interrupt */
bitSet(TIMSK0, TOIE0);

/* Clear the overflow flag */
intFlag_clear(TIFR0, TOV0);
```

---
### Timer0 Compare Match A Interrupt
```c
/* ISR for Compare Match A */
ISR(TIMER0_COMPA_vect)
{
    /* Code executed when TCNT0 == OCR0A */
}

/**< Enable Compare Match A interrupt */
bitSet(TIMSK0, OCIE0A);

/* Clear compare match A flag */
intFlag_clear(TIFR0, OCF0A);

```

---
### Timer0 Compare Match B Interrupt
```c
/* ISR for Compare Match B */
ISR(TIMER0_COMPB_vect)
{
    /* Code executed when TCNT0 == OCR0B */
}

/**< Enable Compare Match B interrupt */
bitSet(TIMSK0, OCIE0B); 

/* Clear compare match B flag */
intFlag_clear(TIFR0, OCF0B);
```

---
## **TCNT0 (Timer/Counter Register)**

| Bit | Description |
| --- | ----------- |
| 7-0 | TCNT0 (Timer/Counter Value) |

- **TCNT0**: The current value of the Timer/Counter. It increments with each clock cycle (or according to the prescaler).

---

## **OCR0A (Output Compare Register A)**

| Bit | Description |
| --- | ----------- |
| 7-0 | OCR0A (Output Compare A Value) |

- **OCR0A**: Holds the value for the output compare match for Channel A. The timer will reset when TCNT0 matches OCR0A, triggering an interrupt if enabled.

---

## **OCR0B (Output Compare Register B)**

| Bit | Description |
| --- | ----------- |
| 7-0 | OCR0B (Output Compare B Value) |

- **OCR0B**: Holds the value for the output compare match for Channel B. Similar to OCR0A but for Channel B.


# **Time Calculation**

### Normal Mode

The time period for **Timer/Counter 0** to overflow or for a compare match can be calculated as:

```
T = (N * 256) / f_clk
```

Where:
- `N` is the prescaler value.
- `256` is the maximum value the timer can count to before overflowing (in **Normal mode**).
- `f_clk` is the system clock frequency.

#### **Example Calculation for Time**

For a **16 MHz** clock and a **prescaler of 64**, the time period for a **Timer/Counter 0** overflow would be:

```
T = (64 * 256) / 16,000,000 = 16,384 / 16,000,000 = 1.024 ms
```

| **Prescaler** | **Time (ms)** |
|---------------|---------------|
| 1             | 0.016         |
| 8             | 0.128         |
| 64            | 1.024         |
| 256           | 4.096         |
| 1024          | 16.384        |

This table shows the time period for a **Timer/Counter 0** overflow for different prescaler values, with a **16 MHz** clock and a **max count of 256** before overflow.

---

## **Time Calculation with TCNT0**

If you want to reach different time intervals in Normal mode, you need to initialize the TCNT0 register to the desired value. After setting TCNT0, you can calculate the time for the timer to reach that specific value before overflowing.

```
T = ((256 - TCNT0) * N) / f_clk
```

Where:
- `TCNT0` is the current value in the **TCNT0** register (the timer's current count).
- `N` is the prescaler value.
- `f_clk` is the system clock frequency.

#### **Example Calculation for Time Using TCNT0**

If you want the interrupt to occur **1 millisecond** after the current value in **TCNT0**, let's calculate it for a **prescaler of 64** with a **16 MHz** clock.

- We want the interrupt to occur after **1 millisecond** (`T = 1 ms`).
- The formula is:  
  ```
  T = ((256 - TCNT0) * N) / f_clk
  ```

We know:
- `T = 1 ms = 0.001 s`
- `N = 64`
- `f_clk = 16,000,000 Hz`

We can rearrange the formula to find the value of **TCNT0**:

```
0.001 = ((256 - TCNT0) * 64) / 16,000,000
```

Solving for **TCNT0**:

```
16,000 = (256 - TCNT0) * 64
(256 - TCNT0) = 16,000 / 64
(256 - TCNT0) = 250
TCNT0 = 256 - 250
TCNT0 = 6
```

Since **TCNT0** is an integer register, you would round **TCNT0** to **6**.

So, if you want an interrupt to occur **1 millisecond** after the timer starts counting with a **prescaler of 64** and a **16 MHz** clock, you would set **TCNT0** to **6**.

> [!IMPORTANT]
You must re-set the TCNT0 register to the calculated value (6 in this case) at the end of the OVF (overflow) interrupt. This is crucial to maintain the timing accuracy, as failing to do so will result in incorrect timing and cause the timer to miss the intended interrupt intervals.

```c
ISR(TIMER0_OVF_vect)
{
    TCNT0 = 6;
};
```

---

## CTC Mode

In **CTC (Clear Timer on Compare Match)** mode, the timer is cleared when it matches the value in the **OCR0A** register. The period for **Timer/Counter 0** in **CTC mode** can be calculated as:

```
T = (N * (OCR0A + 1)) / f_clk
```

Where:
- `OCR0A` is the value in the **OCR0A** register (the compare match value).
- `N` is the prescaler value.
- `f_clk` is the system clock frequency.

#### **Example Calculation for Time in CTC Mode**

For a **16 MHz** clock, a **prescaler of 64**, and **OCR0A = 249**, the time period would be:

```
T = (64 * (249 + 1)) / 16,000,000 = (64 * 250) / 16,000,000 = 16,000 / 16,000,000 = 1 ms
```

In **CTC mode**, the timer counts from 0 to **OCR0A** before resetting, which is useful for generating precise periodic interrupts.

> [!TIP]
In Normal mode, we are typically looking for the Overflow interrupt (OVF). However, in CTC mode, we are looking for the Compare Match interrupt to trigger the event when the timer matches the value in OCR0A.

## **PWM Phase Correct Mode with `OCR0A` as TOP**

In **PWM Phase Correct mode**, Timer0 counts from `BOTTOM (0)` to `TOP (OCR0A)` and then back down to `BOTTOM`, forming a symmetrical up-down count. This results in more accurate frequency and duty cycle characteristics, especially important for motor control or audio PWM applications.

The formula to calculate the frequency in Phase Correct PWM mode is:

```
f_pwm = f_clk / (2 * N * (OCR0A + 1))
```

Where:

* `f_clk` is the system clock frequency (e.g., 16 MHz),
* `N` is the prescaler,
* `OCR0A` is the TOP value (maximum count before counting down).

---

### **Example: Generate 50 Hz in Phase Correct PWM mode**

Given:

* `f_clk = 16,000,000 Hz`,
* `Prescaler N = 1024`,
* Desired `f_pwm = 50 Hz`.

Use the formula:

```
OCR0A = (f_clk / (2 * N * f_pwm)) - 1
```

Plug in the numbers:

```
OCR0A = (16,000,000 / (2 * 1024 * 50)) - 1
OCR0A = (16,000,000 / 102,400) - 1
OCR0A ≈ 156.25 - 1 = 155.25
```

So you would set:

```c
OCR0A = 155;  /* Generates approximately 50 Hz */
```

> \[!IMPORTANT]
> `OCR0A` must be less than 255, as Timer0 is an 8-bit timer. This calculation is valid since the value is within the allowed range.

---

## **Fast PWM Mode with `OCR0A` as TOP**

In **Fast PWM mode**, Timer0 counts from `BOTTOM (0)` to `TOP (OCR0A)`, then resets to zero. It generates a sawtooth waveform which is more efficient for high-frequency PWM applications (e.g., LED dimming, communication systems).

The formula to calculate the PWM frequency in Fast PWM mode is:

```
f_pwm = f_clk / (N * (OCR0A + 1))
```

---

### **Example: Generate 10 kHz in Fast PWM mode**

Given:

* `f_clk = 16,000,000 Hz`,
* `Prescaler N = 64`,
* Desired `f_pwm = 10,000 Hz`.

Use the formula:

```
OCR0A = (f_clk / (N * f_pwm)) - 1
```

Plug in the numbers:

```
OCR0A = (16,000,000 / (64 * 10,000)) - 1
OCR0A = (16,000,000 / 640,000) - 1
OCR0A ≈ 25 - 1 = 24
```

So you would set:

```c
OCR0A = 24;  /* Generates approximately 10 kHz */
```


# 🔗 Resources
  Here you'll find a collection of useful links and videos related to the topic of AVR microcontrollers.  

<table style="border-collapse: collapse;">
  <tr>
    <td valign="top" style="padding: 0 10px;">
      <h3 style="margin: 0;">
        <a href="https://youtu.be/J1_z-FngLbA">aKaReZa 59 – AVR, Timer, Accurate Time, Mode 1</a>
      </h3>
      <p style="margin: 8px 0 0;">
        Learn about Timer-Counter 0 in AVR microcontrollers, Normal and CTC modes, Overflow and Compare Match interrupts, precise timing, function execution time calculation, and 7-segment display integration.
      </p>
    </td>
    <td width="360" valign="top" style="padding: 0;">
      <a href="https://youtu.be/J1_z-FngLbA">
        <img src="https://img.youtube.com/vi/J1_z-FngLbA/maxresdefault.jpg"
             width="360"
             alt="aKaReZa 59 – AVR, Timer, Accurate Time, Mode 1 Thumbnail"/>
      </a>
    </td>
  </tr>
</table>
  
> [!TIP]
> The resources are detailed in the sections below.  
> To access any of them, simply click on the corresponding blue link.

- [AVR Microntroller](https://github.com/aKaReZa75/AVR)
  ---  
    This repository contains comprehensive resources for AVR microcontrollers, including hardware schematics, software libraries, and educational projects.


# 💻 How to Use Git and GitHub
To access the repository files and save them on your computer, there are two methods available:
1. **Using Git Bash and Cloning the Repository**
   - This method is more suitable for advanced users and those familiar with command-line tools.
   - By using this method, you can easily receive updates for the repository.

2. **Downloading the Repository as a ZIP file**
   - This method is simpler and suitable for users who are not comfortable with command-line tools.
   - Note that with this method, you will not automatically receive updates for the repository and will need to manually download any new updates.

## Clone using the URL.
First, open **Git Bash** :
-  Open the folder in **File Explorer** where you want the library to be stored.
-  **Right-click** inside the folder and select the option **"Open Git Bash here"** to open **Git Bash** in that directory.

![open Git Bash](Images/Step0.png)

> [!NOTE] 
> If you do not see the "Open Git Bash here" option, it means that Git is not installed on your system.  
> You can download and install Git from [this link](https://git-scm.com/downloads).  
> For a tutorial on how to install and use Git, check out [this video](https://youtu.be/BsykgHpmUt8).
  
-  Once **Git Bash** is open, run the following command to clone the repository:

 ```bash
git clone https://github.com/aKaReZa75/AVR_Timer0.git
```
- You can copy the above command by either:
- Clicking on the **Copy** button on the right of the command.
- Or select the command text manually and press **Ctrl + C** to copy.
- To paste the command into your **Git Bash** terminal, use **Shift + Insert**.

![Clone the Repository](Images/Step1.png)

- Then, press Enter to start the cloning operation and wait for the success message to appear.

![Open the Library File](Images/Step2.png)

> [!IMPORTANT]
> Please keep in mind that the numbers displayed in the image might vary when you perform the same actions.  
> This is because repositories are continuously being updated and expanded. Nevertheless, the overall process remains unchanged.

> [!NOTE]
> Advantage of Cloning the Repository:  
> - **Receiving Updates:** By cloning the repository, you can easily and automatically receive new updates.  
> - **Version Control:** Using Git allows you to track changes and revert to previous versions.  
> - **Team Collaboration:** If you are working on a project with a team, you can easily sync changes from team members and collaborate more efficiently.  

## Download Zip
If you prefer not to use Git Bash or the command line, you can download the repository directly from GitHub as a ZIP file.  
Follow these steps:  
1. Navigate to the GitHub repository page and Locate the Code button:
   - On the main page of the repository, you will see a green Code button near the top right corner.

2. Download the repository:
   - Click the Code button to open a dropdown menu.
   - Select Download ZIP from the menu.

  ![Download Zip](Images/Step7.png)  

3. Save the ZIP file:
   - Choose a location on your computer to save the ZIP file and click Save.

4. Extract the ZIP file:
   - Navigate to the folder where you saved the ZIP file.
   - Right-click on the ZIP file and select Extract All... (Windows) or use your preferred extraction tool.
   - Choose a destination folder and extract the contents.

5. Access the repository:
   - Once extracted, you can access the repository files in the destination folder.

> [!IMPORTANT]
> - No Updates: Keep in mind that downloading the repository as a ZIP file does not allow you to receive updates.    
>   If the repository is updated, you will need to download it again manually.  
> - Ease of Use: This method is simpler and suitable for users who are not comfortable with Git or command-line tools.

# 📝 How to Ask Questions
If you have any questions or issues, you can raise them through the **"Issues"** section of this repository. Here's how you can do it:  

1. Navigate to the **"Issues"** tab at the top of the repository page.  

  ![Issues](Images/Step3.png)

2. Click on the **"New Issue"** button.  
   
  ![New Issue](Images/Step4.png)

3. In the **Title** field, write a short summary of your issue or question.  

4. In the "Description" field, detail your question or issue as thoroughly as possible. You can use text formatting, attach files, and assign the issue to someone if needed. You can also use text formatting (like bullet points or code snippets) for better readability.  

5. Optionally, you can add **labels**, **type**, **projects**, or **milestones** to your issue for better categorization.  

6. Click on the **"Submit new issue"** button to post your question or issue.
   
  ![Submeet New Issue](Images/Step5.png)

I will review and respond to your issue as soon as possible. Your participation helps improve the repository for everyone!  

> [!TIP]
> - Before creating a new issue, please check the **"Closed"** section to see if your question has already been answered.  
>   ![Closed section](Images/Step6.png)  
> - Write your question clearly and respectfully to ensure a faster and better response.  
> - While the examples provided above are in English, feel free to ask your questions in **Persian (فارسی)** as well.  
> - There is no difference in how they will be handled!  

> [!NOTE]
> Pages and interfaces may change over time, but the steps to create an issue generally remain the same.

# 🤝 Contributing to the Repository
To contribute to this repository, please follow these steps:
1. **Fork the Repository**  
2. **Clone the Forked Repository**  
3. **Create a New Branch**  
4. **Make Your Changes**  
5. **Commit Your Changes**  
6. **Push Your Changes to Your Forked Repository**  
7. **Submit a Pull Request (PR)**  

> [!NOTE]
> Please ensure your pull request includes a clear description of the changes you’ve made.
> Once submitted, I will review your contribution and provide feedback if necessary.

# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# 📜 License
This project is licensed under the GPL-3.0 License. This license grants you the freedom to use, modify, and distribute the project as long as you:
- Credit the original authors: Give proper attribution to the original creators.
- Disclose source code: If you distribute a modified version, you must make the source code available under the same GPL license.
- Maintain the same license: When you distribute derivative works, they must be licensed under the GPL-3.0 too.
- Feel free to use it in your projects, but make sure to comply with the terms of this license.
  
# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
