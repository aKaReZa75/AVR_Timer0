  This file shows how to calculate the output PWM frequency for Timer0 in both Fast PWM and Phase Correct PWM modes, using OCR0A as TOP and different prescaler settings.

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