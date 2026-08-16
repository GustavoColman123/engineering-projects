# System Design

## 1. Design Goal

The circuit converts a change in light level into a change in oscillation frequency.

The design intentionally avoids microcontrollers. The complete sensing and timing behavior is produced by the LDR, the RC timing network, and the internal comparators and discharge transistor of the NE555.

## 2. Functional Architecture

```text
Light
  |
  v
LDR resistance
  |
  v
RC timing network
  |
  v
NE555 astable oscillator
  |
  v
Square-wave output
  |
  v
LED blink rate
```

The LED is not the sensor. It is only a visible indicator of the oscillator output frequency.

## 3. Main Timing Components

```text
R_A = 10 kΩ
R_B = LDR
C   = 10 µF
```

The LDR occupies the `R_B` position of the conventional NE555 astable network.

This was chosen because changes in `R_B` directly affect both the charge/discharge timing and therefore the oscillation period.

## 4. Circuit Topology

```text
                  VCC
                   |
                R_A = 10 kΩ
                   |
              Pin 7 DISCHARGE
                   |
                  LDR
                   |
                   +---------- Pin 2 TRIGGER
                   |
                   +---------- Pin 6 THRESHOLD
                   |
                 + | 10 µF
                ---
                 - |
                   |
                  GND
```

Output stage:

```text
Pin 3 OUTPUT
     |
   330 Ω
     |
    LED
     |
    GND
```

Power connections:

```text
Pin 8 VCC   -> VCC
Pin 4 RESET -> VCC
Pin 1 GND   -> GND
```

A `100 nF` ceramic capacitor is connected directly between VCC and GND as local decoupling.

Pin 5 (CONTROL) is left unconnected in the current v0.1 prototype because a dedicated control-pin bypass capacitor was not available during the build.

## 5. Pin Map

| Pin | Name | v0.1 connection |
|---|---|---|
| 1 | GND | Ground rail |
| 2 | TRIGGER | Connected to pin 6 and timing capacitor positive terminal |
| 3 | OUTPUT | 330 Ω resistor, LED, then GND |
| 4 | RESET | VCC |
| 5 | CONTROL | Unconnected |
| 6 | THRESHOLD | Connected to pin 2 and timing capacitor positive terminal |
| 7 | DISCHARGE | Between 10 kΩ resistor and LDR |
| 8 | VCC | Positive supply rail |

## 6. Design Choices

### 10 kΩ for R_A

A moderate fixed resistance was selected so the LDR remains the dominant variable in the timing network while still maintaining a defined charging path from VCC.

### 10 µF timing capacitor

A relatively large timing capacitor intentionally keeps the oscillator in a low-frequency range where changes can be observed directly as LED blinking.

This makes the first version easy to validate without an oscilloscope or frequency counter.

### LDR as R_B

The LDR allows the oscillator to respond continuously to light without software.

As illumination increases, LDR resistance generally decreases. The expected result is a shorter oscillation period and therefore a higher output frequency.

### LED output

The LED gives immediate qualitative feedback:

- slow blinking = lower frequency
- fast blinking = higher frequency

This is sufficient for the v0.1 proof of concept.

## 7. Current Power Limitation

The working prototype measured approximately `3.8 V` across the supply rails while operating.

The circuit is therefore considered a functional proof of concept, not yet a controlled quantitative test platform.

Before final frequency measurements, the power source should be replaced or corrected so that the supply is stable and known.

## 8. Version Plan

### v0.1

- Breadboard prototype
- LDR-controlled blink rate
- Qualitative behavior confirmed

### v0.2

- Stable regulated supply
- LDR resistance measurements
- Predicted frequency table
- Measured period/frequency
- Error analysis

### Possible later extension

- Add a potentiometer for manual sensitivity/range adjustment
- Add buzzer output to hear frequency changes
- Build a permanent perfboard or PCB version
