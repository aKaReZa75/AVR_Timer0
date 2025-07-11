  This document explains Compare Output Modes and how they affect the OC0A and OC0B pins in different timer modes, with practical configuration examples for normal, inverting, and non-inverting outputs.

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
#### Compare Output Mode — Normal Operation
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
#### Compare Output Mode — Toggle
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
#### Compare Output Mode — Non-Inverting
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
#### Compare Output Mode — Inverting
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