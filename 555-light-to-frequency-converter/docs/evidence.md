# Evidence — 555 Light-to-Frequency Converter

This document collects visual evidence of the v0.1 functional breadboard prototype.

The purpose of this page is to show the physical circuit and the qualitative light-to-frequency behavior observed during testing.

---

## 1. Normal Ambient-Light State

![Normal ambient-light state](../hardware/photos/01-normal-ambient-light.jpg)

Full view of the assembled breadboard prototype under normal room lighting.

Visible hardware includes the NE555 timer, LDR, timing capacitor, resistors, LED, jumper wiring, and breadboard power module.

This image serves as the main physical reference for the v0.1 build.

---

## 2. LED Blink State

![LED illuminated during oscillator cycle](../hardware/photos/02-led-blink-state.jpg)

The output LED captured while illuminated during the oscillator cycle.

The circuit is operating as an astable oscillator. The LED repeatedly turns on and off as the NE555 output changes state.

A still photograph cannot show frequency directly, but this image documents that the output stage is active while the circuit is operating.

---

## 3. LDR Covered — Slow Response

![LDR covered during test](../hardware/photos/03-ldr-covered-response.jpg)

The LDR is deliberately covered to reduce the amount of incident light.

Observed behavior during the test:

```text
LDR covered
-> LDR resistance increases
-> timing interval increases
-> oscillation frequency decreases
-> LED blinks more slowly
```

This qualitative response is the central experimental result of v0.1.

The opposite behavior was observed when the LDR received more light: the LED blink rate increased.

---

## Evidence Summary

The three photographs document:

```text
Physical v0.1 breadboard assembly
Active LED oscillator output
Manual LDR light-response test
```

The experiment qualitatively confirms the expected relationship:

```text
more light -> faster blinking
less light -> slower blinking
```

No quantitative frequency values are claimed from these photographs. Controlled LDR resistance and frequency measurements are planned for the next characterization stage.

---

## Current Evidence Status

```text
v0.1 — Functional breadboard proof of concept
Qualitative light-to-frequency response confirmed
```

The prototype is not yet the final characterized version. The operating supply measured approximately 3.8 V during the first successful session, so later quantitative measurements will be repeated with a stable known supply.
