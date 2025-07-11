  This document helps calculate the overflow time and compare match intervals in Normal and CTC modes based on prescaler and system clock, with practical examples and formulas.

## Normal Mode

The time period for **Timer/Counter 0** to overflow or for a compare match can be calculated as:

```
T = (N * 256) / f_clk
```

Where:
- `N` is the prescaler value.
- `256` is the maximum value the timer can count to before overflowing (in **Normal mode**).
- `f_clk` is the system clock frequency.

### **Example Calculation for Time**

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

### **Example Calculation for Time in CTC Mode**

For a **16 MHz** clock, a **prescaler of 64**, and **OCR0A = 249**, the time period would be:

```
T = (64 * (249 + 1)) / 16,000,000 = (64 * 250) / 16,000,000 = 16,000 / 16,000,000 = 1 ms
```

In **CTC mode**, the timer counts from 0 to **OCR0A** before resetting, which is useful for generating precise periodic interrupts.

> [!TIP]
In Normal mode, we are typically looking for the Overflow interrupt (OVF). However, in CTC mode, we are looking for the Compare Match interrupt to trigger the event when the timer matches the value in OCR0A.


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