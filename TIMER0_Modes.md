  This document provides a detailed overview of all waveform generation modes of Timer0, including Normal, CTC, Fast PWM, and Phase Correct PWM, with register configurations and practical examples.

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

# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
