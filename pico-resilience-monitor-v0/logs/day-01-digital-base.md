# Day 01 — Digital Base

## Goal

Build and validate the digital foundation of Pico Resilience Monitor v0.

The objective of this stage was to test the basic input/output structure before adding analog sensors or the LCD.

---

## Components Used

```text
Raspberry Pi Pico
Breadboard
Push button
3 LEDs
3 current-limiting resistors
Active buzzer
Jumper wires
```

---

## Initial LED Test

The first step was to test the three LEDs independently.

Pin assignment:

```text
GP15 → LED 1 / Normal mode
GP16 → LED 2 / Urban Heat mode
GP17 → LED 3 / Typhoon Alert mode
```

Each LED was connected through a resistor:

```text
GPIO → resistor → LED → GND
```

Expected result:

```text
LED 1 turns on
LED 2 turns on
LED 3 turns on
All LEDs turn off
Sequence repeats
```

Result:

```text
All three LEDs worked correctly.
```

---

## Button Integration

After validating the LEDs, a push button was added.

Button wiring:

```text
GP14 ── button ── GND
```

The Pico internal pull-up resistor was used:

```c
gpio_pull_up(BUTTON_PIN);
```

Button logic:

```text
Button released → GPIO reads 1
Button pressed  → GPIO reads 0
```

---

## Debounce

A simple debounce delay was added:

```c
sleep_ms(50);
```

The firmware also waits until the button is released before accepting another press.

This avoids multiple mode changes from a single physical press.

---

## Mode Switching

The button cycles through three modes:

```text
NORMAL → URBAN_HEAT → TYPHOON_ALERT → NORMAL
```

Each mode turns on a different LED.

Mode behavior:

```text
NORMAL        → LED 1 on
URBAN_HEAT    → LED 2 on
TYPHOON_ALERT → LED 3 on
```

This created the first finite state machine of the project.

---

## Buzzer Integration

An active buzzer was added on GP18.

Wiring:

```text
GP18 → buzzer positive
GND  → buzzer negative
```

The buzzer produces a short beep when changing modes.

This confirmed that the project had both:

```text
Visual output through LEDs
Audible output through buzzer
```

---

## Result

By the end of this stage, the project had a stable digital base:

```text
3 LEDs working
Button input working
Debounce working
Finite state machine working
Buzzer output working
```

---

## Important Notes

At this stage, no analog sensors were used yet.

The goal was to confirm that the digital structure was reliable before adding more complexity.

This proved to be important later, because when sensor problems appeared, the digital base was already known to be stable.

---

## Status

```text
Completed successfully.
```
