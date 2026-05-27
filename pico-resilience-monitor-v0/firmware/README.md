# Firmware — Pico Resilience Monitor v0

This folder contains the firmware for the Pico Resilience Monitor v0.1 functional prototype.

The firmware is written in C using the Raspberry Pi Pico SDK.

---

## Files

```text
firmware/
├── blink.c
└── CMakeLists.txt
```

## Main Firmware File

```text
blink.c
```

Despite the name, this file no longer contains only a simple blink program.

It currently implements the full v0.1 prototype logic:

```text
Button input
Mode switching
LED indicators
Buzzer alerts
LDR ADC reading
Thermistor ADC reading
LCD I2C output
Light hysteresis
Temperature hysteresis
Mode-specific alert logic
USB serial debugging
```

The file is still named `blink.c` because the project started from a basic Pico blink-style setup.

A future cleanup may rename it to:

```text
main.c
```

---

## Required Pico SDK Libraries

The firmware uses:

```text
pico_stdlib
hardware_adc
hardware_i2c
```

These are linked in `CMakeLists.txt`:

```cmake
target_link_libraries(blink
    pico_stdlib
    hardware_adc
    hardware_i2c
)
```

---

## USB Serial Output

USB serial output is enabled in `CMakeLists.txt`:

```cmake
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)
```

This allows the firmware to print debug information through USB.

Example output:

```text
Mode: HEAT | Light ADC: 3600 | Light: HIGH | Temp ADC: 2360 | Temp: HIGH | Alert: ACTIVE
```

---

## Pin Summary

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
```

Power:

```text
3V3 → Breadboard 3.3V rail
GND → Breadboard ground rail
```

---

## Build Instructions

From the firmware folder:

```bash
cd firmware
mkdir build
cd build
cmake ..
make -j4
```

This should generate:

```text
blink.uf2
```

---

## Flashing the Raspberry Pi Pico

1. Disconnect the Pico from USB.
2. Hold the `BOOTSEL` button.
3. Connect the Pico to USB while holding `BOOTSEL`.
4. Release `BOOTSEL`.
5. The Pico should appear as a USB drive named:

```text
RPI-RP2
```

Copy the UF2 file:

```bash
cp blink.uf2 /media/$USER/RPI-RP2/
sync
```

After copying, the Pico should reboot automatically and start running the firmware.

---

## Opening the Serial Monitor

After flashing the firmware, the Pico should appear as a serial device.

Check:

```bash
ls /dev/ttyACM*
```

Open the serial monitor:

```bash
screen /dev/ttyACM0 115200
```

To exit `screen`:

```text
Ctrl + A
K
Y
```

---

## Expected LCD Output

The LCD displays compact system information.

Example without alert:

```text
MODE:NORMAL
L0310 T1850 OK
```

Example with alert:

```text
MODE:HEAT
L3600 T2360 ALRT
```

Where:

```text
Lxxxx = LDR ADC value
Txxxx = thermistor ADC value
OK    = no active alert
ALRT  = alert active
```

---

## System Modes

The button cycles through three modes:

```text
NORMAL → URBAN_HEAT → TYPHOON_ALERT → NORMAL
```

Mode behavior:

| Mode | Alert Condition |
|---|---|
| NORMAL | No alert |
| URBAN_HEAT | High light or high temperature |
| TYPHOON_ALERT | Low light |

---

## Current Thresholds

Light hysteresis:

```text
LOW enters below 700
LOW exits above 900

HIGH enters above 2500
HIGH exits below 2200
```

Temperature hysteresis:

```text
TEMP_HIGH enters above 2200
TEMP_HIGH exits below 2000
```

---

## Current Limitations

The firmware currently uses raw ADC values.

It does not yet convert:

```text
Light ADC → lux
Thermistor ADC → degrees Celsius
```

The code is also still contained in a single C file.

Future versions should refactor the firmware into separate modules:

```text
main.c
lcd.c / lcd.h
sensors.c / sensors.h
alerts.c / alerts.h
config.h
```

---

## Current Status

```text
v0.1 — Functional breadboard prototype
```

The firmware is stable enough for documentation and demonstration.
