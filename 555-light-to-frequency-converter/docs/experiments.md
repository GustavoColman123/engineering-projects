# Experiments

## Experiment 0 — Qualitative Light Response

### Objective

Verify that changing the amount of light reaching the LDR changes the oscillation frequency of the NE555 circuit.

### Setup

The circuit was assembled on a breadboard using:

- NE555 timer
- 10 kΩ fixed resistor
- LDR as the variable timing resistance
- 10 µF timing capacitor
- LED output with 330 Ω current-limiting resistor
- 100 nF supply decoupling capacitor

### Procedure

1. Power the completed circuit.
2. Observe the LED under normal ambient light.
3. Cover the LDR to reduce the incident light.
4. Observe the change in LED blink rate.
5. Expose the LDR to more light and observe the response again.

### Observation

The LED blinked clearly while the circuit was operating.

When the LDR was covered, the LED blink rate became noticeably slower.

When more light reached the LDR, the blink rate increased.

### Result

```text
PASS — qualitative light-to-frequency conversion confirmed.
```

The observed direction of change agrees with the expected model:

```text
more light -> lower LDR resistance -> higher frequency
less light -> higher LDR resistance -> lower frequency
```

### Limitation

No calibrated frequency measurement was performed during this test.

The measured supply rail was approximately `3.8 V`, so this run is treated as a functional proof of concept rather than final quantitative characterization.

---

## Experiment 1 — LDR Resistance Characterization

Status: `PENDING`

### Objective

Measure the LDR resistance under repeatable lighting conditions.

### Planned Conditions

- covered / dark
- normal room light
- strong direct light

### Planned Output

Record:

```text
R_dark
R_room
R_bright
```

These values will become inputs to the theoretical frequency model.

---

## Experiment 2 — Theoretical Frequency Prediction

Status: `PENDING`

### Objective

Use measured LDR resistance values to calculate expected oscillation frequency.

Equation:

```text
f ≈ 1.44 / ((R_A + 2R_LDR) C)
```

With:

```text
R_A = 10 kΩ
C = 10 µF
```

### Planned Output

A prediction table for dark, ambient, and bright conditions.

---

## Experiment 3 — Measured Frequency

Status: `PENDING`

### Objective

Measure actual oscillation period/frequency under the same lighting conditions used for the LDR characterization.

### Requirement

Use a stable, known power supply before treating the results as final.

### Planned Comparison

```text
predicted frequency
vs
measured frequency
```

Then calculate percentage error and discuss possible non-ideal effects.
