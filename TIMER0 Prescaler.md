This document explains how to configure the clock source and prescaler for Timer0, including detailed descriptions of all clock select bits and their effects on timer resolution and overflow frequency.

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