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

## First Attempt — The Circuit Does Not Work

The first assembled circuit did not produce the expected output.

At the same time, supply measurements appeared unexpectedly low and inconsistent.

What began as a small NE555 experiment turned into roughly two hours of troubleshooting.

The debugging process expanded to include:

- breadboard supply rails
- NE555 removal
- multiple breadboard power modules
- the external DC adapter
- direct voltage measurements
- repeated wiring and contact checks

The power supply became an obvious suspect because several readings were around `4 V` or below instead of the intended approximately `5 V`.

However, the evidence never established one definitive root cause for the non-working first build.

## The Debugging Irony

The session can be summarized almost absurdly as:

```text
build the circuit
-> it does not work
-> spend roughly two hours searching for the fault
-> fail to identify one definitive culprit
-> remove everything
-> rebuild from zero
-> it works
```

That sequence is intentionally preserved in the project history.

The successful rebuild is evidence that the intended circuit topology works. It is **not** evidence that a specific suspected fault caused the first failure.

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

## Supply Observation — Still Unresolved as a Separate Issue

While the successful circuit was operating, the measured rail voltage was approximately:

```text
VCC ≈ 3.8 V
```

This is still lower than the intended approximately `5 V` supply.

The important distinction is that the rebuilt circuit operated while this low-voltage condition was still present.

Therefore:

```text
first-build root cause: unresolved
low-voltage supply: confirmed separate limitation
```

The current power arrangement is sufficient for the v0.1 qualitative proof of concept, but it should be replaced or corrected before final quantitative characterization.

A future setup should provide a stable, verified supply close to `5 V`.

## End-of-Day Status

```text
[PASS] NE555 oscillator functional after clean rebuild
[PASS] LED output functional
[PASS] LDR changes oscillation rate
[PASS] qualitative model confirmed
[PASS] photographic evidence added to repository
[UNRESOLVED] exact cause of first failed build
[KNOWN LIMITATION] supply remains around 4 V or below instead of intended ~5 V
[PENDING] stable regulated test supply
[PENDING] LDR resistance measurements
[PENDING] theoretical frequency calculations with measured values
[PENDING] measured frequency comparison
[PENDING] Xournal++ mathematical/visual documentation
```

## Main Lesson From Day 00

The circuit itself was simpler than the debugging session.

The most valuable result was not merely that the LED eventually blinked, but that the project produced a clear example of the difference between:

```text
finding a way to recover a system
and
actually proving why it failed
```

The rebuild recovered the system.

The original fault was never proven.

## Next Session

The next session will focus on the mathematical and experimental side of the project:

1. create Xournal++ visual notes
2. derive the timing equations
3. measure the LDR in several lighting conditions
4. calculate predicted frequencies
5. obtain or prepare a stable verified supply near 5 V
6. prepare the project for measured-vs-theoretical comparison
