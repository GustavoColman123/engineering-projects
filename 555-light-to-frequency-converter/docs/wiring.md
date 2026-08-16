# Wiring Reference

This file records the v0.1 breadboard connections in a compact form.

## NE555 Orientation

When viewed from above with the notch facing upward:

```text
        notch
      +-------+
  1 --|       |-- 8
  2 --| NE555 |-- 7
  3 --|       |-- 6
  4 --|       |-- 5
      +-------+
```

## Power

```text
Pin 1 -> GND
Pin 8 -> VCC
Pin 4 -> VCC
```

## Timing Node

Pins 2 and 6 are connected together.

```text
Pin 2 --------+
              |
Pin 6 --------+
```

The positive terminal of the 10 µF timing capacitor connects to this node.

The negative terminal connects to GND.

```text
Pins 2/6 -> (+) 10 µF (-) -> GND
```

## Timing Resistance Network

```text
VCC -> 10 kΩ -> Pin 7 -> LDR -> Pins 2/6
```

Neither the 10 kΩ resistor nor the LDR has polarity.

## LED Output

```text
Pin 3 -> 330 Ω -> LED anode (+)
LED cathode (-) -> GND
```

The resistor may be physically placed on either side of the LED as long as both remain in series.

## Decoupling

A `100 nF` ceramic capacitor marked `104` is connected between VCC and GND.

```text
VCC -> 100 nF -> GND
```

The ceramic capacitor has no polarity.

## Pin 5

Pin 5 (CONTROL) is left unconnected in v0.1.

## Complete Text Schematic

```text
                    VCC
                     |
                  10 kΩ
                     |
                   Pin 7
                     |
                    LDR
                     |
                     +----------- Pin 2
                     |
                     +----------- Pin 6
                     |
                   (+) 10 µF
                   (-)
                     |
                    GND

Pin 8 ---------------------------- VCC
Pin 4 ---------------------------- VCC
Pin 1 ---------------------------- GND

Pin 3 ---- 330 Ω ---- LED -------- GND

VCC ------- 100 nF ---------------- GND
```

## Pre-Power Checklist

Before applying power:

- Verify pin 1 is connected to GND
- Verify pin 8 is connected to VCC
- Verify pin 4 is connected to VCC
- Verify pins 2 and 6 are actually on the same electrical node
- Verify the 10 µF capacitor positive terminal is connected to pins 2/6
- Verify the 10 µF capacitor negative terminal is connected to GND
- Verify no direct short exists between VCC and GND
- Verify the LED orientation
- Verify the supply voltage with a multimeter
