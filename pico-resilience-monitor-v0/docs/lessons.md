# Lessons Learned — Pico Resilience Monitor v0

This document records the main technical lessons learned during the development of Pico Resilience Monitor v0.1.

The purpose of this file is not only to describe what was built, but to explain what was understood through debugging, testing, and integration.

---

## 1. A Working Circuit Is Not the Same as a Correctly Designed Circuit

One of the clearest lessons from this project was that a component can work correctly and still produce bad results if the surrounding circuit is poorly dimensioned.

The LDR was not damaged. The Pico ADC was not damaged. The code was not reading the wrong pin.

The real issue was the voltage divider.

The first LDR divider used:

```text
3V3 ── LDR ── GP26_A0 ── 10kΩ ── GND
```

This produced compressed readings around:

```text
300–500
```

After testing and replacing the fixed resistor with 100kΩ, the same LDR produced a much more useful range:

```text
Low light: ~250–320
Strong nearby lamp: ~3600+
```

Lesson:

```text
Sensor circuits must be matched to the sensor's real resistance range.
```

---

## 2. Debugging Requires Isolation

When the LDR readings were unstable, the first instinct was to suspect many things at once:

```text
The LDR
The code
The ADC pin
The jumper wires
The breadboard
The resistor
The Pico
```

The problem became clearer only after isolating the ADC by replacing the LDR with a potentiometer.

The potentiometer test showed:

```text
Turning one direction increased the ADC value.
Turning the other direction decreased the ADC value.
```

This proved that:

```text
GP26_A0 worked.
The ADC worked.
The code worked.
The serial monitor worked.
```

Lesson:

```text
Do not debug the whole system at once. Replace uncertain parts with known-good parts.
```

---

## 3. Raw ADC Values Are Useful, But They Are Not Physical Units

The project currently uses raw ADC values.

For example:

```text
Light ADC: 3600
Temp ADC: 2360
```

These values are meaningful inside this specific prototype, but they are not lux or degrees Celsius.

Lesson:

```text
Raw ADC values are useful for control logic, but physical measurement requires calibration and mathematical modeling.
```

For v0.1, raw ADC thresholds are acceptable because the goal is relative classification, not scientific measurement.

---

## 4. Hysteresis Is Necessary for Stable Threshold Systems

Simple thresholds can make a system unstable.

Example:

```text
ADC = 699 → LOW
ADC = 701 → NORMAL
ADC = 698 → LOW
ADC = 702 → NORMAL
```

This causes rapid switching near the threshold.

The project uses hysteresis:

```text
LOW enters below 700
LOW exits above 900

HIGH enters above 2500
HIGH exits below 2200
```

For temperature:

```text
TEMP_HIGH enters above 2200
TEMP_HIGH exits below 2000
```

Lesson:

```text
Real threshold systems should usually use hysteresis to avoid unstable state changes.
```

---

## 5. Breadboard Power Rails Are Not Power Unless Connected

A breadboard red rail does not automatically mean 3.3V.

A breadboard blue rail does not automatically mean GND.

They only become power rails when connected to real power pins from the Pico.

Correct setup:

```text
Pico 3V3 → red rail
Pico GND → blue rail
```

Lesson:

```text
Breadboard rails are just metal strips. Their meaning depends on how they are wired.
```

---

## 6. 3V3_EN Is Not a 3.3V Output

A mistake during the project was trying to use `3V3_EN` as another 3.3V power source.

This caused the Pico to shut down or become unstable.

The reason is that `3V3_EN` is not a normal 3.3V output. It controls the Pico's 3.3V regulator enable line.

Lesson:

```text
Pin names must be understood electrically, not guessed from appearance.
```

Correct pin:

```text
3V3
```

Incorrect for powering sensors:

```text
3V3_EN
```

---

## 7. GPIO Numbers Are Not Physical Pin Numbers

The firmware uses GPIO numbers.

Example:

```c
#define LED_TYPHOON_PIN 17
```

This means:

```text
GPIO 17 / GP17
```

It does not mean physical pin number 17.

Lesson:

```text
Always distinguish between GPIO numbering and physical pin numbering.
```

This is especially important when wiring the Raspberry Pi Pico manually.

---

## 8. Sensor Placement Matters Physically

One LED was accidentally connected in a way that kept it permanently on. This light interfered with the LDR.

The problem was not code. The problem was physical contamination of the measurement.

Lesson:

```text
A sensor does not only measure the outside world. It measures whatever reaches it physically.
```

For light sensors, nearby LEDs and LCD backlights can affect readings.

Future layouts should place the LDR away from LEDs and possibly shield it from internal circuit light.

---

## 9. A Finite State Machine Makes Behavior Easier to Control

The project uses three modes:

```text
NORMAL
URBAN_HEAT
TYPHOON_ALERT
```

The button cycles through them:

```text
NORMAL → URBAN_HEAT → TYPHOON_ALERT → NORMAL
```

This makes the system behavior predictable and organized.

Lesson:

```text
A finite state machine is useful when a system has clear operating modes.
```

Instead of writing random conditions everywhere, the system first determines its mode, then applies the correct alert logic for that mode.

---

## 10. Debouncing Is Required for Mechanical Buttons

A push button does not produce a perfectly clean signal. It can bounce between pressed and released states for a short time.

The project uses a simple debounce delay:

```c
sleep_ms(50);
```

It also waits until the button is released before accepting the next press.

Lesson:

```text
Mechanical inputs need debouncing if they control digital logic.
```

Without debounce, one physical button press may be interpreted as multiple presses.

---

## 11. I2C Devices Should Be Scanned Before Writing Drivers

Before trying to display text on the LCD, an I2C scanner was used.

The scanner found the LCD at:

```text
0x27
```

This confirmed that:

```text
The LCD was powered.
SDA and SCL were connected correctly.
The I2C bus worked.
The address was known.
```

Lesson:

```text
Before debugging a display driver, first confirm that the device is visible on the bus.
```

---

## 12. Small Prototypes Can Still Have Real Engineering Value

This project is not large, but it includes many real embedded systems concepts:

```text
GPIO input
GPIO output
ADC reading
I2C communication
State machines
Sensor thresholds
Hysteresis
Debugging with substitution
Power distribution
Physical sensor interference
```

Lesson:

```text
A small project becomes valuable when it is built carefully, tested honestly, and documented rigorously.
```

---

## 13. Documentation Should Include Failures

The most useful parts of this project were not only the final working circuit.

Important failures included:

```text
LDR readings compressed with 10kΩ
Confusion around 3V3_EN
LED light interfering with LDR readings
Uncertainty about GPIO vs physical pins
Need for hysteresis
```

Lesson:

```text
Good engineering documentation records the path to the solution, not only the final result.
```

This makes the project more credible and more useful for future learning.

---

## 14. Current Personal Takeaway

The most important technical takeaway from this prototype is:

```text
Do not trust assumptions. Test them.
```

The LDR issue looked like a sensor problem, but it was actually a voltage divider design problem.

The ADC looked suspicious, but the potentiometer proved it was working.

The final result came from testing each part separately and then integrating them again.

---

## 15. Summary

Main lessons learned:

```text
1. Voltage dividers must be designed around real sensor behavior.
2. ADC debugging should be isolated with known-good inputs.
3. Raw ADC values are useful but not calibrated units.
4. Hysteresis prevents unstable threshold switching.
5. Breadboard rails must be explicitly powered.
6. 3V3_EN is not a power output.
7. GPIO numbers are not physical pin numbers.
8. Physical layout affects sensor readings.
9. State machines simplify system behavior.
10. Mechanical buttons require debouncing.
11. I2C devices should be scanned before integration.
12. Failures should be documented, not hidden.
```

Pico Resilience Monitor v0.1 is a small prototype, but it produced real lessons in embedded systems design, debugging, and documentation.
