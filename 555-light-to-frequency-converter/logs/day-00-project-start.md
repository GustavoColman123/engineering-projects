# Day 00 — Project Start

Date: 2026-08-15

## Goal

Build a simple but meaningful electronics project without a microcontroller and document it as an engineering exercise.

The selected idea was a light-to-frequency converter using an NE555 timer and an LDR.

## Initial Design

The intended v0.1 circuit used:

```text
NE555 astable oscillator
R_A = 10 kΩ
R_B = LDR
C = 10 µF
LED output with 330 Ω resistor
100 nF supply decoupling capacitor
```

The expected behavior was:

```text
more light -> lower LDR resistance -> faster blinking
less light -> higher LDR resistance -> slower blinking
```

## Build Process

The circuit was assembled incrementally:

1. NE555 placed across the breadboard center gap
2. power and reset connections prepared
3. pins 2 and 6 connected together
4. 10 kΩ resistor connected from VCC to pin 7
5. LDR connected from pin 7 to the pins 2/6 timing node
6. 10 µF electrolytic capacitor connected from the timing node to GND
7. LED output connected to pin 3 through a 330 Ω resistor
8. 100 nF ceramic capacitor used for supply decoupling

Solid-core AWG 22 wire was used for some short breadboard connections.

## First Attempt

The first assembled circuit did not produce the expected output.

Supply measurements also appeared unexpectedly low and inconsistent during troubleshooting.

The debugging process expanded to include:

- breadboard supply rails
- NE555 removal
- multiple breadboard power modules
- the external DC adapter
- direct voltage measurements

The evidence did not establish one definitive root cause.

## Reset

Instead of continuing to modify an uncertain breadboard state, the circuit was completely restarted from zero.

This was treated as a clean rebuild rather than an attempt to preserve the first assembly.

## Successful Result

After rebuilding the circuit, the LED began blinking clearly.

The response to the LDR matched the expected direction:

```text
LDR exposed to more light -> LED blink rate increased
LDR covered -> LED blink rate decreased
```

This confirmed the core light-to-frequency concept.

## Supply Observation

While the successful circuit was operating, the measured rail voltage was approximately:

```text
VCC ≈ 3.8 V
```

The circuit therefore works as a proof of concept, but the current power arrangement will not be used as the final basis for precision characterization.

## End-of-Day Status

```text
[PASS] NE555 oscillator functional
[PASS] LED output functional
[PASS] LDR changes oscillation rate
[PASS] qualitative model confirmed
[PENDING] stable regulated test supply
[PENDING] LDR resistance measurements
[PENDING] theoretical frequency calculations with measured values
[PENDING] measured frequency comparison
[PENDING] Xournal++ mathematical/visual documentation
[PENDING] photographic evidence in repository
```

## Next Session

The next session will focus on the mathematical and experimental side of the project:

1. create Xournal++ visual notes
2. derive the timing equations
3. measure the LDR in several lighting conditions
4. calculate predicted frequencies
5. prepare the project for measured-vs-theoretical comparison
