# Xournal++ Engineering Notes

This directory will contain the handwritten and visual documentation for the project.

The workflow follows the same idea used in NucleOS:

```text
Xournal++ = visual engineering notebook
Markdown   = structured technical documentation
GitHub     = public engineering record
```

## File Rule

Important Xournal++ pages should be stored in both forms:

```text
.xopp = editable source
.pdf  = readable export for GitHub
```

## Planned Structure

```text
xournal/
├── README.md
├── notes/
├── diagrams/
├── experiments/
└── exported-pdfs/
```

The folders will be created naturally when the first `.xopp` and PDF files are added.

## Planned Pages

### 01 — NE555 Astable Concept

Visual explanation of:

- pins 2, 6, and 7
- timing capacitor
- charging and discharging paths
- output state changes

### 02 — Capacitor Thresholds

Hand-drawn capacitor voltage waveform showing the approximate lower and upper switching thresholds.

### 03 — High-Time Derivation

Derive:

```text
t_H ≈ 0.693 (R_A + R_B) C
```

and show where the `ln(2)` term comes from.

### 04 — Low-Time Derivation

Derive:

```text
t_L ≈ 0.693 R_B C
```

### 05 — Period and Frequency

Combine the equations to obtain:

```text
T ≈ 0.693 (R_A + 2R_B) C
```

and:

```text
f ≈ 1.44 / ((R_A + 2R_B) C)
```

### 06 — LDR Substitution

Replace:

```text
R_B = R_LDR
```

and explain visually:

```text
light ↑ -> resistance ↓ -> period ↓ -> frequency ↑
```

### 07 — Real Measurements

Insert measured LDR resistance values for:

- dark
- room light
- bright light

Then calculate predicted frequencies by hand.

### 08 — Predicted vs Measured

Compare calculated and experimental values.

### 09 — Error Analysis

Calculate percentage error and annotate likely sources of non-ideal behavior.

## Status

```text
Structure prepared.
Xournal++ pages pending next session.
```
