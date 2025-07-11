  This file covers all interrupt-related features of Timer0 such as overflow, compare match A/B interrupts, and explains how to enable and clear them properly using TIMSK0 and TIFR0 registers.


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