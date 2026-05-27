# Wiring — Pico Resilience Monitor v0

This document describes the wiring used in the v0.1 functional breadboard prototype.

The system uses a Raspberry Pi Pico, a push button, three LEDs, an active buzzer, an LDR, a thermistor, and a 16x2 I2C LCD.

---

## 1. Power Rails

The breadboard uses shared power rails for 3.3V and GND.

```text
Pico 3V3 → breadboard red rail
Pico GND → breadboard blue rail
```

All sensors and modules that require 3.3V are powered from the red rail.

All components share the same ground through the blue rail.

Important:

```text
Use 3V3, not 3V3_EN.
Do not use VBUS or VSYS for the sensor voltage dividers.
```

---

## 2. Button Wiring

The push button is connected between GP14 and GND.

```text
GP14 ── button ── GND
```

The firmware enables the internal pull-up resistor:

```c
gpio_pull_up(BUTTON_PIN);
```

Logic:

```text
Button released → GPIO reads 1
Button pressed  → GPIO reads 0
```

This allows the button to work without an external pull-up or pull-down resistor.

The button is used to cycle between system modes:

```text
NORMAL → URBAN_HEAT → TYPHOON_ALERT → NORMAL
```

---

## 3. LED Wiring

The system uses three LEDs, one for each mode.

Each LED must be connected through a current-limiting resistor.

```text
GP15 ── resistor ── Normal LED ── GND
GP16 ── resistor ── Urban Heat LED ── GND
GP17 ── resistor ── Typhoon Alert LED ── GND
```

LED polarity:

```text
Long leg  → GPIO side
Short leg → GND side
```

Recommended resistor:

```text
220Ω or 330Ω
```

The LEDs must not be connected directly to the 3.3V rail unless they are intended to stay permanently on.

---

## 4. Buzzer Wiring

The project uses an active buzzer as an alert output.

```text
GP18 ── buzzer positive
GND  ── buzzer negative
```

The buzzer is controlled as a digital output.

It produces short beeps when:

```text
The user changes mode
An alert condition is active
```

---

## 5. LDR Light Sensor Wiring

The LDR is connected as a voltage divider.

Final working circuit:

```text
3V3 ── LDR ── GP26_A0 ── 100kΩ ── GND
```

Detailed node description:

```text
One side of the LDR → 3.3V rail

Other side of the LDR → central analog node

Central analog node → GP26_A0
Central analog node → one side of 100kΩ resistor

Other side of 100kΩ resistor → GND rail
```

The central analog node is the point read by the Pico ADC.

Expected behavior:

```text
More light  → ADC value increases
Less light  → ADC value decreases
```

Current observed values:

```text
Low light / lamp off → approximately 250–320
Strong nearby lamp   → approximately 3600+
```

The 100kΩ resistor was chosen after debugging. A 10kΩ resistor produced compressed ADC readings and was not suitable for this LDR under the tested lighting conditions.

---

## 6. Thermistor Wiring

The thermistor is also connected as a voltage divider.

Working circuit:

```text
3V3 ── thermistor ── GP27_A1 ── 10kΩ ── GND
```

Detailed node description:

```text
One side of the thermistor → 3.3V rail

Other side of the thermistor → central analog node

Central analog node → GP27_A1
Central analog node → one side of 10kΩ resistor

Other side of 10kΩ resistor → GND rail
```

Expected behavior observed in this prototype:

```text
More heat → ADC value increases
Less heat → ADC value decreases gradually
```

Current observed values:

```text
Resting temperature      → approximately 1850
Held between fingers     → approximately 2360
After release            → returns near 1860
```

---

## 7. LCD I2C Wiring

The 16x2 LCD uses an I2C backpack.

Detected I2C address:

```text
0x27
```

Connection:

```text
LCD VCC → 3.3V rail
LCD GND → GND rail
LCD SDA → GP4
LCD SCL → GP5
```

Firmware configuration:

```text
I2C port: i2c0
SDA pin: GP4
SCL pin: GP5
Speed: 100 kHz
Address: 0x27
```

The LCD displays:

```text
Current system mode
Light ADC value
Temperature ADC value
Alert status
```

Example display:

```text
MODE:HEAT
L3600 T1850 ALRT
```

---

## 8. Complete Wiring Summary

```text
GP4  → LCD SDA
GP5  → LCD SCL

GP14 → Push button
GP15 → Normal mode LED
GP16 → Urban Heat mode LED
GP17 → Typhoon Alert mode LED
GP18 → Active buzzer

GP26_A0 → LDR voltage divider
GP27_A1 → Thermistor voltage divider

3V3 → Breadboard 3.3V rail
GND → Breadboard ground rail
```

---

## 9. System Wiring Diagram

High-level wiring structure:

```text
                  ┌────────────────────┐
                  │ Raspberry Pi Pico   │
                  │                    │
GP4  ─────────────┤ LCD SDA             │
GP5  ─────────────┤ LCD SCL             │
GP14 ─────────────┤ Button              │
GP15 ─────────────┤ Normal LED          │
GP16 ─────────────┤ Heat LED            │
GP17 ─────────────┤ Typhoon LED         │
GP18 ─────────────┤ Buzzer              │
GP26 ─────────────┤ LDR ADC             │
GP27 ─────────────┤ Thermistor ADC      │
3V3  ─────────────┤ 3.3V rail           │
GND  ─────────────┤ GND rail            │
                  └────────────────────┘
```

---

## 10. Physical Layout Notes

The LDR should be placed away from LEDs and the LCD backlight when possible.

Reason:

```text
Nearby LEDs can contaminate the light reading.
```

Recommended physical separation:

```text
LEDs and buzzer → one side of the breadboard
LDR             → away from LEDs and direct LCD backlight
Thermistor      → accessible for touch testing
LCD             → placed where it can be read easily
```

The current prototype is functional, but cable organization should be improved in a future version.

---

## 11. Known Wiring Lessons

Important wiring lessons learned during development:

```text
1. Breadboard rails must be connected to real Pico power pins.
2. The red rail is not automatically 3.3V.
3. The blue rail is not automatically GND.
4. 3V3_EN must not be used as a power output.
5. LEDs connected to the 3.3V rail stay permanently on.
6. Light sensors must be physically protected from onboard LEDs.
7. Voltage divider resistor values strongly affect ADC behavior.
8. Analog sensors should be tested separately before integration.
```

---

## 12. Current Wiring Status

The current wiring is considered stable for v0.1.

Validated working modules:

```text
Button input
Three LED outputs
Buzzer output
LDR ADC input
Thermistor ADC input
LCD I2C output
Shared 3.3V and GND rails
```

This wiring will be used as the reference layout for the v0.1 documentation.
