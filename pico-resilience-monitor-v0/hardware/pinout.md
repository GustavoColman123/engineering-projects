# Pinout — Pico Resilience Monitor v0

This document describes the pin mapping used in the v0.1 functional breadboard prototype.

## Raspberry Pi Pico Pin Assignment

| Function | Component | Pico GPIO | Notes |
|---|---|---|---|
| Mode input | Push button | GP14 | Digital input with internal pull-up |
| Normal mode indicator | LED 1 | GP15 | Digital output |
| Urban heat indicator | LED 2 | GP16 | Digital output |
| Typhoon alert indicator | LED 3 | GP17 | Digital output |
| Alert sound | Active buzzer | GP18 | Digital output |
| Light sensing | LDR voltage divider | GP26_A0 / ADC0 | Analog input |
| Temperature sensing | Thermistor voltage divider | GP27_A1 / ADC1 | Analog input |
| LCD data | LCD SDA | GP4 | I2C0 SDA |
| LCD clock | LCD SCL | GP5 | I2C0 SCL |
| Power rail | Breadboard 3.3V rail | 3V3 | Do not use 3V3_EN |
| Ground rail | Breadboard GND rail | GND | Common ground |

## Important Note About Pin Naming

The firmware uses GPIO numbers, not physical pin numbers.

For example:

```text
#define LED_TYPHOON_PIN 17
```

This means GPIO 17 / GP17, not physical pin number 17.

## Power Distribution

The breadboard uses two main rails:

```text
3V3 from Pico → red power rail
GND from Pico → blue ground rail
```

The 3.3V rail powers:

```text
LCD VCC
LDR voltage divider
Thermistor voltage divider
```

The GND rail is shared by:

```text
LEDs
button
buzzer
LCD
LDR voltage divider
thermistor voltage divider
```

## Warning About 3V3_EN

The `3V3_EN` pin must not be used as a power source.

It is not a normal 3.3V output. It controls the Pico's 3.3V regulator enable line. Using it incorrectly can shut down the board or cause unstable behavior.

Correct power pin:

```text
3V3
```

Incorrect for this project:

```text
3V3_EN
VBUS
VSYS
```

## LED Connections

Each LED is connected through a current-limiting resistor.

```text
GP15 ── resistor ── LED normal ── GND
GP16 ── resistor ── LED heat ── GND
GP17 ── resistor ── LED typhoon ── GND
```

LED polarity:

```text
Long leg  → GPIO side through resistor
Short leg → GND
```

## Button Connection

The push button is connected using the Pico's internal pull-up resistor.

```text
GP14 ── button ── GND
```

Firmware behavior:

```text
Button released → GPIO reads 1
Button pressed  → GPIO reads 0
```

## Buzzer Connection

The active buzzer is connected as a digital output.

```text
GP18 ── buzzer positive
GND  ── buzzer negative
```

## LDR Voltage Divider

Final working circuit:

```text
3V3 ── LDR ── GP26_A0 ── 100kΩ ── GND
```

Reason for using 100kΩ:

The initial 10kΩ resistor produced compressed ADC readings around 300–500. Replacing it with 100kΩ expanded the useful range to approximately 250–3600+ under the tested lighting conditions.

Expected behavior:

```text
More light  → ADC value increases
Less light  → ADC value decreases
```

## Thermistor Voltage Divider

Working circuit:

```text
3V3 ── thermistor ── GP27_A1 ── 10kΩ ── GND
```

Expected behavior:

```text
More heat → ADC value increases
Less heat → ADC value decreases gradually
```

## LCD I2C Connection

The LCD 1602 I2C backpack was detected at address:

```text
0x27
```

Connection:

```text
LCD VCC → 3V3 rail
LCD GND → GND rail
LCD SDA → GP4
LCD SCL → GP5
```

I2C configuration:

```text
I2C port: i2c0
SDA: GP4
SCL: GP5
Speed: 100 kHz
```

## Current Stable Pin Map

```text
GP4  → LCD SDA
GP5  → LCD SCL
GP14 → Button
GP15 → Normal LED
GP16 → Urban Heat LED
GP17 → Typhoon Alert LED
GP18 → Buzzer
GP26 → LDR / ADC0
GP27 → Thermistor / ADC1
3V3  → Breadboard 3.3V rail
GND  → Breadboard ground rail
```
