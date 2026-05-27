# Day 03 — LCD I2C Integration

## Goal

Integrate a 16x2 LCD with I2C backpack into Pico Resilience Monitor v0.

The goal was to make the project usable without depending only on the USB serial monitor.

---

## Components Used

```text
Raspberry Pi Pico
16x2 LCD with I2C backpack
Breadboard
Jumper wires
Existing digital base
Existing LDR circuit
```

---

## Reason for Adding the LCD

Before adding the LCD, the system printed information through USB serial:

```text
Mode: HEAT | Light ADC: 3600 | Light: HIGH | Alert: ACTIVE
```

This was useful for debugging, but the project still depended on a computer terminal.

The LCD makes the prototype more independent by showing:

```text
Current mode
Light ADC value
Temperature ADC value
Alert status
```

---

## LCD Wiring

The LCD I2C backpack was connected to I2C0.

Final wiring:

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
```

---

## Important Power Decision

The LCD was powered from the 3.3V rail.

This was done to avoid exposing the Pico I2C pins to 5V logic levels.

Important rule:

```text
Use 3.3V for the LCD I2C module in this prototype.
Do not connect SDA/SCL to 5V pull-ups.
```

---

## I2C Scanner Test

Before writing text to the LCD, an I2C scanner was used.

This was done to confirm:

```text
The LCD was powered correctly.
SDA and SCL were connected correctly.
The I2C bus was working.
The LCD address was known.
```

The scanner detected the LCD at:

```text
0x27
```

This confirmed that the LCD was visible on the I2C bus.

---

## First LCD Text Test

After detecting the address, a simple LCD test program was loaded.

Expected display:

```text
Pico Monitor
LCD OK 0x27
```

Result:

```text
The LCD displayed the text correctly.
```

This confirmed that the LCD initialization sequence and I2C communication were working.

---

## LCD Contrast

The LCD module includes a small contrast potentiometer on the I2C backpack.

If the LCD backlight turns on but text is not visible, the contrast potentiometer must be adjusted.

In this prototype, the text became visible and readable after the LCD was initialized correctly.

---

## Integration With Main System

After the LCD test succeeded, the display was integrated into the main firmware.

The LCD shows compact system information:

```text
MODE:NORMAL
L0310 T1850 OK
```

Or when an alert is active:

```text
MODE:HEAT
L3600 T2360 ALRT
```

---

## Display Format

Line 1 shows the current mode:

```text
MODE:NORMAL
MODE:HEAT
MODE:TYPHOON
```

Line 2 shows sensor values and alert status:

```text
Lxxxx Txxxx OK
Lxxxx Txxxx ALRT
```

Where:

```text
Lxxxx = raw LDR ADC value
Txxxx = raw thermistor ADC value
OK    = no active alert
ALRT  = alert active
```

---

## LCD Update Timing

The LCD is not updated continuously on every loop iteration.

It is updated at a fixed interval:

```text
500 ms
```

This reduces unnecessary I2C traffic and keeps the display readable.

Firmware constant:

```c
#define LCD_UPDATE_INTERVAL_MS 500
```

---

## Issue: 3.3V Rail Already Used

When adding the LCD, the 3.3V pin was already used by the LDR circuit.

The solution was to create a shared breadboard power rail:

```text
Pico 3V3 → red rail
Pico GND → blue rail
```

Then both the LCD and sensors could use the same stable 3.3V source.

Final shared power usage:

```text
LCD VCC → 3.3V rail
LDR divider → 3.3V rail
Thermistor divider → 3.3V rail
```

---

## Result

By the end of this stage, the LCD was fully integrated.

Validated features:

```text
LCD powered correctly
I2C scanner detected address 0x27
LCD displayed test text
LCD displayed live system status
LCD updated during normal operation
System no longer depended only on serial output
```

---

## Lessons Learned

Important lessons from this stage:

```text
I2C devices should be scanned before writing display code.
The detected address must be used in firmware.
LCD contrast can affect whether text is visible.
A shared 3.3V rail is necessary when multiple modules need power.
The LCD makes the prototype more usable as a standalone embedded system.
```

---

## Final Status

The LCD integration was completed successfully.

Status:

```text
Completed successfully.
```
