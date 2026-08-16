# Measurements

This file records measured values separately from nominal component values and theoretical predictions.

## 1. Supply Voltage

During the successful v0.1 functional test, the measured voltage across the supply rails was approximately:

```text
VCC ≈ 3.800 V
```

This value was measured while the rebuilt circuit was operating and the LED was blinking.

During the earlier troubleshooting session, the breadboard power arrangement also produced values around `4 V` or below instead of the intended approximately `5 V`.

### Interpretation

This is a confirmed limitation of the current test setup.

It should **not** be confused with the unresolved root cause of the first failed build.

The reason is straightforward:

```text
first build + low-voltage supply -> did not work
rebuilt circuit + same general low-voltage limitation -> worked
```

Therefore the low supply voltage remains a real problem to correct, but it does not by itself explain why the first assembly failed.

### Future Requirement

Final quantitative frequency characterization should be repeated with a stable, verified supply close to:

```text
VCC ≈ 5 V
```

The supply voltage should be recorded for every quantitative test.

## 2. Nominal Component Values

| Component | Nominal value |
|---|---:|
| R_A | 10 kΩ |
| LED resistor | 330 Ω |
| Timing capacitor | 10 µF |
| Decoupling capacitor | 100 nF |
| R_B | LDR, variable |

These are nominal values. Exact component measurements have not yet been recorded.

## 3. LDR Resistance Measurements

Pending.

Planned measurement conditions:

| Condition | Measured R_LDR | Notes |
|---|---:|---|
| LDR covered / dark | TBD | Keep geometry consistent |
| Normal room light | TBD | Record ambient condition |
| Strong direct light | TBD | Use same light source and distance |

The LDR should be measured with the circuit unpowered and isolated appropriately so that the multimeter measures the LDR rather than parallel circuit paths.

## 4. Predicted Frequency

After obtaining `R_LDR`, theoretical frequency will be calculated using:

```text
f_predicted ≈ 1.44 / ((R_A + 2R_LDR) C)
```

Planned table:

| Condition | R_LDR | Predicted period | Predicted frequency |
|---|---:|---:|---:|
| Dark | TBD | TBD | TBD |
| Room light | TBD | TBD | TBD |
| Strong light | TBD | TBD | TBD |

## 5. Measured Frequency

Pending.

The first successful v0.1 test was qualitative only. The LED visibly changed blink rate, but no calibrated period or frequency measurement was taken.

Planned table:

| Condition | Measured period | Measured frequency |
|---|---:|---:|
| Dark | TBD | TBD |
| Room light | TBD | TBD |
| Strong light | TBD | TBD |

## 6. Error Analysis

Once predicted and measured frequencies are available, percentage error will be calculated as:

```text
percentage error = |f_measured - f_predicted| / f_predicted × 100
```

No percentage error is reported yet because no quantitative frequency measurements have been completed.

## 7. Measurement Discipline

Future measurements should record:

- supply voltage at the time of the test
- LDR lighting condition
- distance from the light source where applicable
- measured LDR resistance
- timing capacitor value if measured
- observed oscillation period
- calculated frequency
- repeated trials if practical

The objective is to make the final comparison reproducible rather than relying only on visual impressions.

## 8. Measurement Lesson From the First Session

The first session produced an important distinction between measurement and diagnosis.

A suspicious voltage reading can identify a real weakness in the setup without proving that it caused a different failure.

For this project:

```text
measured fact:
supply is lower than intended

measured fact:
rebuilt circuit still oscillates under that supply

unresolved question:
why the first assembly did not oscillate
```

Keeping those statements separate prevents the documentation from turning a plausible suspicion into a false conclusion.
