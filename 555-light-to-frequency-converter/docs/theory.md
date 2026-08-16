# Theory and Mathematical Model

## 1. NE555 Astable Operation

In astable mode, the NE555 repeatedly charges and discharges the timing capacitor.

The capacitor voltage moves between two internal threshold levels. This creates a continuous oscillation at the output.

For the conventional astable configuration:

```text
R_A = resistor from VCC to pin 7
R_B = resistor from pin 7 to pins 2/6
C   = timing capacitor from pins 2/6 to GND
```

In this project:

```text
R_A = 10 kΩ
R_B = R_LDR
C   = 10 µF
```

## 2. Charge Time

During the charging interval, the capacitor charges through both `R_A` and `R_B`.

The approximate high-state time is:

```text
t_H ≈ 0.693 (R_A + R_B) C
```

The constant `0.693` is approximately `ln(2)`.

## 3. Discharge Time

During the discharge interval, the internal discharge transistor at pin 7 provides the discharge path through `R_B`.

The approximate low-state time is:

```text
t_L ≈ 0.693 R_B C
```

## 4. Oscillation Period

The total period is:

```text
T = t_H + t_L
```

Substituting the two expressions:

```text
T ≈ 0.693 (R_A + R_B) C + 0.693 R_B C
```

Therefore:

```text
T ≈ 0.693 (R_A + 2R_B) C
```

## 5. Frequency

Frequency is the reciprocal of period:

```text
f = 1 / T
```

so:

```text
f ≈ 1 / [0.693 (R_A + 2R_B) C]
```

Since:

```text
1 / 0.693 ≈ 1.44
```

we obtain the common approximation:

```text
f ≈ 1.44 / ((R_A + 2R_B) C)
```

## 6. Light-to-Frequency Model

The key design choice is:

```text
R_B = R_LDR
```

Therefore the oscillator becomes a function of LDR resistance:

```text
f(R_LDR) ≈ 1.44 / ((R_A + 2R_LDR) C)
```

For the current component values:

```text
R_A = 10,000 Ω
C   = 10 × 10^-6 F
```

so:

```text
f(R_LDR) ≈ 1.44 / [(10,000 + 2R_LDR)(10 × 10^-6)]
```

This equation will be used later with measured LDR resistance values.

## 7. Expected Direction of Change

An LDR generally decreases in resistance when exposed to more light.

Therefore:

```text
more light
-> R_LDR decreases
-> denominator decreases
-> period decreases
-> frequency increases
```

and:

```text
less light
-> R_LDR increases
-> denominator increases
-> period increases
-> frequency decreases
```

This qualitative prediction was confirmed by the v0.1 breadboard test.

## 8. Duty Cycle

For the conventional astable circuit, the approximate duty cycle is:

```text
D ≈ (R_A + R_B) / (R_A + 2R_B)
```

Because the LDR changes `R_B`, the duty cycle is also expected to change somewhat with illumination.

The v0.1 experiment focuses on frequency rather than precision duty-cycle measurement.

## 9. Important Non-Ideal Effects

The simple model is useful, but the real circuit will not match it perfectly.

Possible sources of difference include:

- LDR nonlinearity
- LDR variation with temperature
- Resistor tolerance
- Electrolytic capacitor tolerance
- Capacitor leakage
- Breadboard contact resistance
- Supply-voltage instability
- Internal NE555 non-ideal behavior
- Measurement uncertainty

These effects will become relevant when theoretical and measured frequency are compared.

## 10. Planned Xournal++ Derivation

The handwritten/visual derivation will be created separately in Xournal++.

Planned pages:

1. NE555 charge/discharge concept
2. Capacitor voltage thresholds
3. Derivation of `t_H`
4. Derivation of `t_L`
5. Derivation of `T` and `f`
6. Substitution of `R_LDR`
7. Predicted values from measured LDR resistance
8. Predicted vs measured comparison
9. Percentage-error analysis

The `.xopp` source files and PDF exports will be stored under the project `xournal/` directory.
