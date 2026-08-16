# 555 Light-to-Frequency Converter

A light-sensitive oscillator built around an NE555 timer in astable mode.

This project uses an LDR as part of the timing network so that changes in light level produce changes in oscillation frequency. The output is visualized with an LED.

No microcontroller, firmware, or software is required for the circuit itself.

## Objective

The goals of this project are to:

- Build a light-dependent oscillator using discrete electronic components
- Understand the NE555 astable timing network
- Relate LDR resistance to oscillator frequency
- Develop a mathematical model before quantitative testing
- Compare theoretical predictions with real measurements
- Practice controlled breadboard debugging
- Document uncertainty and failed attempts instead of hiding them

## Current Status

```text
v0.1 functional breadboard prototype completed.
Qualitative light-to-frequency behavior confirmed.
Quantitative characterization is pending.
```

Observed behavior:

- With more light on the LDR, the LED blinks faster
- When the LDR is covered, the LED blinks more slowly
- The LED output is clearly visible and the circuit responds immediately to large light changes

The prototype was measured at approximately `3.8 V` across the supply rails while operating. This is not considered the final characterization supply. A stable regulated supply close to the intended `5 V` will be used for later quantitative measurements.

## The Debugging Story

The most memorable part of v0.1 was not the final circuit. It was getting there.

The first assembly did not work.

Roughly two hours were then spent checking wiring, breadboard contacts, the NE555, supply rails, multiple breadboard power modules, the external adapter, and voltage measurements.

No single culprit was conclusively isolated.

Eventually the entire breadboard was cleared and the circuit was rebuilt from zero using the same intended topology.

It worked.

The sequence was essentially:

```text
build
-> does not work
-> troubleshoot for roughly two hours
-> no definitive root cause found
-> rebuild from zero
-> works
```

This is intentionally documented rather than cleaned up into a fictional neat diagnosis.

A successful rebuild is evidence that the intended circuit can work. It is **not** proof of why the first build failed.

### Separate Power-Supply Limitation

The power setup still remains imperfect.

The intended test supply is approximately `5 V`, but the successful prototype measured approximately `3.8 V`, and values around `4 V` or below were repeatedly observed during troubleshooting.

However, the rebuilt circuit worked while that limitation was still present.

Therefore:

```text
first-build root cause: unresolved
low-voltage supply: confirmed separate limitation
```

The next hardware improvement is not to redesign the oscillator, but to obtain or prepare a stable, verified supply near `5 V` for final characterization.

## Hardware

- NE555 timer IC
- LDR photoresistor
- 10 kΩ resistor (`R_A`)
- 330 Ω LED current-limiting resistor
- 10 µF electrolytic timing capacitor
- 100 nF ceramic decoupling capacitor (`104`)
- LED
- Breadboard
- Solid-core AWG 22 wire / jumper wires
- Breadboard power module
- Multimeter

## Circuit Configuration

The NE555 is configured in astable mode.

Main connections:

```text
Pin 1 (GND)       -> GND
Pin 2 (TRIGGER)   -> timing node
Pin 3 (OUTPUT)    -> 330 Ω -> LED -> GND
Pin 4 (RESET)     -> VCC
Pin 5 (CONTROL)   -> not connected in v0.1
Pin 6 (THRESHOLD) -> timing node
Pin 7 (DISCHARGE) -> 10 kΩ to VCC and LDR to timing node
Pin 8 (VCC)       -> VCC
```

Timing network:

```text
VCC
 |
10 kΩ  (R_A)
 |
Pin 7
 |
LDR    (R_B)
 |
+------ Pin 2
|
+------ Pin 6
|
10 µF
|
GND
```

A 100 nF ceramic capacitor is connected across VCC and GND for local supply decoupling.

## Working Principle

For the standard NE555 astable configuration, the approximate oscillation frequency is:

```text
f ≈ 1.44 / ((R_A + 2R_B) C)
```

In this project:

```text
R_B = R_LDR
```

so the model becomes:

```text
f(R_LDR) ≈ 1.44 / ((R_A + 2R_LDR) C)
```

Qualitatively:

```text
more light
   -> lower LDR resistance
   -> shorter timing interval
   -> higher oscillation frequency
   -> faster LED blinking
```

and:

```text
less light
   -> higher LDR resistance
   -> longer timing interval
   -> lower oscillation frequency
   -> slower LED blinking
```

## Visual Evidence

The following photographs show the three main states used to validate the v0.1 prototype.

### 1. Normal Ambient-Light State

The complete circuit is assembled and powered under normal room lighting. The NE555, LDR, timing capacitor, resistors, LED, jumper wiring, and power module are all visible. This image serves as the main physical reference for the working breadboard prototype.

![Normal ambient-light state](./hardware/photos/01-normal-ambient-light.jpg)

### 2. Oscillator Output — LED Active

The LED is captured while illuminated during one of the NE555 output cycles. In operation, the output repeatedly changes state, causing the LED to turn on and off. A still image cannot represent the frequency itself, but it provides visual evidence that the oscillator output stage is active.

![LED illuminated during oscillator cycle](./hardware/photos/02-led-blink-state.jpg)

### 3. LDR Covered — Lower Oscillation Frequency

The LDR is deliberately covered to reduce the incident light. As the illumination decreases, the LDR resistance increases. Because the LDR is part of the NE555 timing network, the capacitor takes longer to complete each timing cycle and the oscillator frequency decreases. The observed result is a visibly slower LED blink rate.

```text
less light
-> higher LDR resistance
-> longer timing interval
-> lower oscillation frequency
-> slower blinking
```

![LDR covered during slow-blink test](./hardware/photos/03-ldr-covered-response.jpg)

The opposite behavior was observed when more light reached the LDR: its resistance decreased and the LED blink rate increased.

For the complete annotated evidence record, see [Photo evidence](./docs/evidence.md).

## Documentation

- [System design](./docs/design.md)
- [Wiring reference](./docs/wiring.md)
- [Theory and mathematical model](./docs/theory.md)
- [Measurements](./docs/measurements.md)
- [Experiments](./docs/experiments.md)
- [Problems and debugging](./docs/problems.md)
- [Lessons learned](./docs/lessons.md)
- [Photo evidence](./docs/evidence.md)
- [Day 0 build log](./logs/day-00-project-start.md)
- [Xournal++ plan](./xournal/README.md)

## Next Steps

1. Obtain or prepare a stable, verified supply near `5 V`
2. Measure the LDR resistance under controlled light conditions
3. Calculate predicted frequencies from the measured resistance values
4. Record the mathematical derivation in Xournal++
5. Export the Xournal++ pages to PDF for GitHub
6. Measure real oscillation periods/frequencies
7. Compare theoretical and experimental results
8. Calculate percentage error and discuss possible causes

## Engineering Note

The first assembly failed, the exact cause was not conclusively isolated, and a clean rebuild worked.

That unresolved failure is part of the project rather than something to hide.

The low-voltage power supply remains a known issue, but because the rebuilt circuit worked under the same general limitation, it is not presented as the proven cause of the original failure.

The project therefore preserves three separate statements:

```text
1. The first assembly failed.
2. The rebuild worked.
3. The supply still needs improvement.
```

That separation is intentional and is part of the engineering record.
