# System Design — Pico Resilience Monitor v0

This document explains the internal design of the Pico Resilience Monitor v0.1 functional prototype.

The goal of this project is to build a small embedded system that reads environmental sensor values, classifies them, displays the current system state, and activates alerts depending on the selected mode.

---

## 1. Design Goal

The main goal of this prototype is to practice embedded systems concepts using the Raspberry Pi Pico and the Pico SDK in C.

The project integrates:

```text
Digital input
Digital output
Analog input
I2C communication
State machines
Sensor classification
Threshold logic
Hysteresis
Visual and audible alerts
```

The system is inspired by environmental monitoring and infrastructure resilience. It is not intended to be a real weather station or a real typhoon detection system.

---

## 2. High-Level System Overview

The system has three main input sources:

```text
Push button
LDR light sensor
Thermistor temperature sensor
```

And four output systems:

```text
Mode LEDs
Active buzzer
LCD 1602 I2C display
USB serial debug output
```

High-level structure:

```text
              ┌──────────────────────┐
              │ Raspberry Pi Pico     │
              │                      │
Button ──────▶│ Digital input         │
LDR ─────────▶│ ADC0                  │
Thermistor ──▶│ ADC1                  │
              │                      │
              │ State machine         │
              │ Sensor classification │
              │ Alert logic           │
              │                      │
LEDs ◀────────│ Digital outputs       │
Buzzer ◀──────│ Digital output        │
LCD ◀─────────│ I2C output            │
Serial ◀──────│ USB debug output      │
              └──────────────────────┘
```

---

## 3. Main System Modes

The system has three operating modes:

```text
NORMAL
URBAN_HEAT
TYPHOON_ALERT
```

The modes are controlled by a push button.

Each button press advances the system to the next mode:

```text
NORMAL → URBAN_HEAT → TYPHOON_ALERT → NORMAL
```

This is implemented as a finite state machine.

---

## 4. Finite State Machine

The mode system is represented by an enum:

```c
typedef enum {
    MODE_NORMAL = 0,
    MODE_URBAN_HEAT = 1,
    MODE_TYPHOON_ALERT = 2
} SystemMode;
```

The transition logic is:

```c
current_mode = (SystemMode)((current_mode + 1) % 3);
```

This creates a cyclic state machine.

State transition diagram:

```text
        ┌──────────────┐
        │              │
        ▼              │
   ┌────────┐     ┌────────────┐     ┌───────────────┐
   │ NORMAL │ ──▶ │ URBAN_HEAT │ ──▶ │ TYPHOON_ALERT │
   └────────┘     └────────────┘     └───────────────┘
        ▲                                      │
        └──────────────────────────────────────┘
```

---

## 5. Button Input Design

The button is connected between GP14 and GND.

The Pico internal pull-up resistor is enabled:

```c
gpio_pull_up(BUTTON_PIN);
```

This means:

```text
Button released → GPIO reads 1
Button pressed  → GPIO reads 0
```

The firmware detects a falling edge:

```text
released → pressed
```

A debounce delay is used to avoid false multiple presses:

```c
sleep_ms(50);
```

After a valid press, the firmware waits until the button is released before accepting another press.

---

## 6. Sensor Inputs

The system uses two analog sensors.

### Light Sensor

The LDR is connected to:

```text
GP26_A0 / ADC0
```

Final circuit:

```text
3V3 ── LDR ── GP26_A0 ── 100kΩ ── GND
```

Behavior:

```text
More light  → ADC increases
Less light  → ADC decreases
```

### Temperature Sensor

The thermistor is connected to:

```text
GP27_A1 / ADC1
```

Circuit:

```text
3V3 ── thermistor ── GP27_A1 ── 10kΩ ── GND
```

Observed behavior:

```text
More heat → ADC increases
Less heat → ADC decreases gradually
```

---

## 7. ADC Reading Strategy

Each analog reading is averaged over multiple samples.

Function:

```c
uint16_t read_adc_average(uint adc_channel) {
    uint32_t sum = 0;

    adc_select_input(adc_channel);

    for (int i = 0; i < 16; i++) {
        sum += adc_read();
        sleep_ms(2);
    }

    return sum / 16;
}
```

Reason:

```text
ADC readings can fluctuate slightly.
Averaging reduces noise.
Averaging makes threshold classification more stable.
```

This is a simple moving sample average, not a continuous moving average filter.

---

## 8. Light Classification

The light sensor is classified into three levels:

```text
LIGHT_LOW
LIGHT_NORMAL
LIGHT_HIGH
```

Represented as:

```c
typedef enum {
    LIGHT_LOW = 0,
    LIGHT_NORMAL = 1,
    LIGHT_HIGH = 2
} LightLevel;
```

The classification uses hysteresis instead of simple thresholds.

Current thresholds:

```text
LOW enters below 700
LOW exits above 900

HIGH enters above 2500
HIGH exits below 2200
```

This avoids unstable behavior near threshold boundaries.

---

## 9. Temperature Classification

Temperature is currently classified only as:

```text
normal temperature
high temperature
```

This is represented by a boolean:

```c
bool current_temp_high;
```

Current thresholds:

```text
TEMP_HIGH enters above 2200
TEMP_HIGH exits below 2000
```

This also uses hysteresis.

The project currently uses raw ADC values rather than Celsius.

---

## 10. Alert Logic

Alert logic depends on the current mode.

| Mode | Alert Condition |
|---|---|
| NORMAL | No alert |
| URBAN_HEAT | HIGH_LIGHT or TEMP_HIGH |
| TYPHOON_ALERT | LOW_LIGHT |

In logical form:

```text
NORMAL:
    alert = false

URBAN_HEAT:
    alert = high_light OR high_temperature

TYPHOON_ALERT:
    alert = low_light
```

The implemented function is:

```c
bool is_alert_condition(SystemMode mode, LightLevel light_level, bool temp_high)
```

---

## 11. Output Behavior

### LEDs

Each mode has one LED.

```text
NORMAL        → Normal LED on
URBAN_HEAT    → Heat LED on
TYPHOON_ALERT → Typhoon LED on
```

If an alert is active, the corresponding mode LED blinks.

### Buzzer

The buzzer produces:

```text
A short beep when changing modes
Repeated short beeps when an alert is active
```

The alert beep interval is:

```text
1500 ms
```

### LCD

The LCD displays:

```text
Current mode
Light ADC value
Temperature ADC value
Alert status
```

Example:

```text
MODE:HEAT
L3600 T1850 ALRT
```

### Serial Debug

The USB serial output prints a more detailed debug line:

```text
Mode: HEAT | Light ADC: 3600 | Light: HIGH | Temp ADC: 1850 | Temp: NORM | Alert: ACTIVE
```

---

## 12. Timing Design

The firmware uses timing intervals based on milliseconds since boot.

Important intervals:

```text
LED blink interval: 300 ms
Buzzer alert interval: 1500 ms
LCD update interval: 500 ms
Serial print interval: 1000 ms
```

This avoids blocking the whole system with long delays during normal operation.

There are still small blocking delays in:

```text
Button debounce
ADC sample averaging
Buzzer beep
LCD communication
```

For v0.1, this is acceptable.

Future versions could use a more non-blocking architecture.

---

## 13. Current Firmware Architecture

The firmware is currently contained in a single file:

```text
firmware/blink.c
```

Main functional sections:

```text
GPIO pin definitions
ADC pin definitions
I2C LCD definitions
Timing constants
Enum types
LCD functions
Text helper functions
ADC reading functions
Light classification
Temperature classification
Output control
Alert logic
Main loop
```

This single-file structure is acceptable for v0.1, but it should be refactored later.

---

## 14. Main Loop Structure

The main loop follows this sequence:

```text
1. Read current time.
2. Read button state.
3. If button press is detected, change mode.
4. Read LDR ADC value.
5. Read thermistor ADC value.
6. Update light classification.
7. Update temperature classification.
8. Evaluate alert condition.
9. Update LEDs and buzzer.
10. Update LCD.
11. Print serial debug information.
12. Repeat.
```

Simplified flow:

```text
while true:
    handle button
    read sensors
    classify sensors
    evaluate alert
    update outputs
    update display
    print debug
```

---

## 15. Why Hysteresis Matters

Hysteresis is one of the most important design decisions in this project.

Without hysteresis, the system could rapidly switch states when a sensor value is near a threshold.

Example:

```text
699 → LOW
701 → NORMAL
698 → LOW
702 → NORMAL
```

With hysteresis, the system becomes more stable:

```text
Enter LOW below 700
Exit LOW only above 900
```

This is closer to how real threshold-based embedded systems are designed.

---

## 16. Current Design Limitations

The v0.1 design has several limitations:

```text
1. The firmware is still a single C file.
2. Temperature is not converted to Celsius.
3. Light is not converted to lux.
4. Thresholds are manually calibrated.
5. The breadboard wiring is functional but not physically optimized.
6. The alert scenarios are educational simulations.
7. The LCD text is compact and could be improved.
8. The system does not save logs to storage.
```

---

## 17. Future Design Improvements

Possible improvements for future versions:

```text
Refactor firmware into multiple files.
Add lcd.c / lcd.h.
Add sensors.c / sensors.h.
Add state_machine.c / state_machine.h.
Add config.h for thresholds and pin definitions.
Convert thermistor readings to approximate Celsius.
Add better filtering for sensor readings.
Improve LCD display layout.
Add a physical enclosure or cleaner breadboard layout.
Add data logging.
Add more formal calibration.
```

---

## 18. Design Summary

Pico Resilience Monitor v0.1 is a functional embedded systems prototype.

It demonstrates:

```text
Digital input
Digital output
ADC sensor acquisition
I2C communication
Finite state machine design
Threshold-based classification
Hysteresis
Alert outputs
LCD status display
Serial debugging
```

The current design is simple, but it is technically meaningful because each subsystem was built, tested, debugged, and integrated step by step.
