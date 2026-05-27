# Pico Resilience Monitor v0

**Status:** v0.1 — Functional breadboard prototype  
**Platform:** Raspberry Pi Pico / RP2040  
**Language:** C with Pico SDK  

## Overview

Pico Resilience Monitor v0 is an educational embedded systems project built with a Raspberry Pi Pico. It monitors basic environmental conditions using a light sensor and a thermistor, then displays system status through LEDs, a buzzer, and a 16x2 I2C LCD.

The project is indirectly inspired by Taiwan’s focus on resilient infrastructure, environmental monitoring, and applied embedded systems. It is not a real meteorological device, but a learning prototype for sensor acquisition, state machines, threshold logic, and alert behavior.

## Current Features

- Digital input using a push button
- Three system modes controlled by a finite state machine
- LED indicators for each mode
- Buzzer alert output
- LDR light sensing through ADC
- Thermistor temperature sensing through ADC
- 16x2 LCD display over I2C
- Hysteresis for stable light classification
- Hysteresis for stable temperature alerting
- Serial debugging over USB

## System Modes

The system has three main modes:

| Mode | Purpose | Alert Condition |
|---|---|---|
| NORMAL | Stable monitoring mode | No alert |
| URBAN_HEAT | Simulates urban heat risk | High light or high temperature |
| TYPHOON_ALERT | Simulates low-visibility alert mode | Low light |

## Hardware Used

- Raspberry Pi Pico
- Breadboard
- Push button
- 3 LEDs
- 3 current-limiting resistors
- Active buzzer
- LDR photoresistor
- 100kΩ resistor for LDR voltage divider
- NTC thermistor
- 10kΩ resistor for thermistor voltage divider
- LCD 1602 with I2C backpack
- Jumper wires

## Pinout Summary

| Component | Pico Pin |
|---|---|
| Button | GP14 |
| Normal LED | GP15 |
| Urban Heat LED | GP16 |
| Typhoon Alert LED | GP17 |
| Buzzer | GP18 |
| LDR | GP26_A0 / ADC0 |
| Thermistor | GP27_A1 / ADC1 |
| LCD SDA | GP4 |
| LCD SCL | GP5 |
| LCD VCC | 3V3 |
| LCD GND | GND |

## Sensor Circuits

### LDR Voltage Divider

The LDR originally produced unstable and compressed ADC readings with a 10kΩ resistor. After debugging, the fixed resistor was changed to 100kΩ, which produced a useful measurement range.

Final LDR circuit:

```text
3V3 ── LDR ── GP26_A0 ── 100kΩ ── GND
```

Observed behavior:

```text
More light  → ADC value increases
Less light  → ADC value decreases
```

### Thermistor Voltage Divider

The thermistor is connected using a 10kΩ resistor.

```text
3V3 ── thermistor ── GP27_A1 ── 10kΩ ── GND
```

Observed behavior:

```text
More heat → Temp ADC increases
Less heat → Temp ADC decreases gradually
```

## Calibration Notes

Initial observed values:

### LDR

| Condition | ADC Range |
|---|---|
| Low light / lamp off | ~250–320 |
| Strong nearby lamp | ~3600+ |

### Thermistor

| Condition | ADC Value |
|---|---|
| Resting temperature | ~1850 |
| Held between fingers | ~2360 |
| After release | returns near ~1860 |

Current threshold logic:

```text
LOW light enters below 700
LOW light exits above 900

HIGH light enters above 2500
HIGH light exits below 2200

HIGH temperature enters above 2200
HIGH temperature exits below 2000
```

## Important Debugging Result

The most important hardware issue was the LDR voltage divider.

At first, the LDR was connected with a 10kΩ resistor, but the ADC value stayed around 300–500 and barely reacted to light changes. The Pico, ADC, and GP26 were tested using a potentiometer, which confirmed that the microcontroller and code were working correctly.

The final diagnosis was that the 10kΩ resistor was not appropriate for the LDR’s resistance range under the available lighting conditions. Replacing it with a 100kΩ resistor solved the issue and produced a wide ADC response.

## Current Version

### v0.1 — Functional Prototype

This version successfully integrates:

- Button-controlled mode switching
- LEDs for mode indication
- Buzzer alerts
- LDR light sensing
- Thermistor temperature sensing
- LCD status display
- Hysteresis-based alert stability

## Limitations

This project does not measure calibrated lux or real temperature in degrees Celsius yet. The values are raw ADC readings used for relative environmental classification.

It is also not a real typhoon detection system. The Typhoon Alert mode is an educational simulation of low-light / low-visibility alert behavior.

## Next Steps

- Improve physical cable organization
- Add photos and wiring diagrams
- Convert thermistor ADC values to approximate temperature
- Refactor firmware into multiple source files
- Document calibration experiments
- Improve enclosure or mounting layout
