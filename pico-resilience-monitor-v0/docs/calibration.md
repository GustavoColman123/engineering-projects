# Calibration — Pico Resilience Monitor v0

This document records the calibration values used in the v0.1 functional prototype.

The system currently uses raw ADC values instead of calibrated physical units such as lux or degrees Celsius. The goal of this version is to classify environmental conditions reliably enough for an educational embedded systems prototype.

---

## 1. ADC Range

The Raspberry Pi Pico ADC produces values from:

```text
0 to 4095
```

This corresponds approximately to:

```text
0V to 3.3V
```

The approximate conversion is:

```text
Voltage = ADC value × 3.3 / 4095
```

In this project, raw ADC values are used directly for classification.

---

## 2. Light Sensor Calibration

The light sensor is an LDR connected to GP26_A0 / ADC0.

Final working circuit:

```text
3V3 ── LDR ── GP26_A0 ── 100kΩ ── GND
```

Expected behavior:

```text
More light  → ADC value increases
Less light  → ADC value decreases
```

---

## 3. LDR Calibration Observations

Observed values during testing:

| Condition | Observed ADC Value |
|---|---|
| Low light / lamp off | ~250–320 |
| Strong nearby lamp | ~3600+ |

These values were observed at night, using a nearby lamp as the strong light source.

Further testing is still needed under:

```text
Normal room lighting
Daylight without direct sun
Direct sunlight
```

---

## 4. LDR Resistor Selection

The LDR was first tested with a 10kΩ fixed resistor.

Initial circuit:

```text
3V3 ── LDR ── GP26_A0 ── 10kΩ ── GND
```

Problem:

```text
ADC values stayed compressed around 300–500.
The sensor did not react clearly to light changes.
```

Diagnostic result:

```text
The ADC and GP26_A0 were tested with a potentiometer and worked correctly.
```

Conclusion:

```text
The issue was not the Pico or the code.
The voltage divider was not properly dimensioned for the LDR's resistance range.
```

Final solution:

```text
The fixed resistor was changed from 10kΩ to 100kΩ.
```

Final working circuit:

```text
3V3 ── LDR ── GP26_A0 ── 100kΩ ── GND
```

Result:

```text
Low light: approximately 250–320
Strong nearby lamp: approximately 3600+
```

This produced a much wider and more useful ADC range.

---

## 5. Light Classification

The system classifies light into three categories:

```text
LOW_LIGHT
NORMAL_LIGHT
HIGH_LIGHT
```

The current threshold logic uses hysteresis.

---

## 6. Light Hysteresis Thresholds

Current thresholds:

```text
LOW light enters below 700
LOW light exits above 900

HIGH light enters above 2500
HIGH light exits below 2200
```

In firmware:

```c
#define LOW_ENTER_THRESHOLD 700
#define LOW_EXIT_THRESHOLD 900

#define HIGH_ENTER_THRESHOLD 2500
#define HIGH_EXIT_THRESHOLD 2200
```

---

## 7. Why Hysteresis Is Used

Without hysteresis, the system may rapidly switch states when the ADC value is near a threshold.

Example problem:

```text
ADC = 695 → LOW_LIGHT
ADC = 705 → NORMAL_LIGHT
ADC = 698 → LOW_LIGHT
ADC = 702 → NORMAL_LIGHT
```

This creates unstable behavior.

Hysteresis creates separate thresholds for entering and exiting a state.

Example:

```text
Enter LOW_LIGHT below 700
Exit LOW_LIGHT only after rising above 900
```

This makes the system more stable.

---

## 8. Temperature Sensor Calibration

The temperature sensor is an NTC thermistor connected to GP27_A1 / ADC1.

Working circuit:

```text
3V3 ── thermistor ── GP27_A1 ── 10kΩ ── GND
```

Observed behavior:

```text
More heat → ADC value increases
Less heat → ADC value decreases gradually
```

---

## 9. Thermistor Calibration Observations

Observed values:

| Condition | Observed ADC Value |
|---|---|
| Resting temperature | ~1850 |
| Held between fingers | ~2360 |
| After release | returns near ~1860 |

The thermistor response was slower than the LDR response, which is expected because temperature changes take time.

---

## 10. Temperature Alert Thresholds

The current prototype does not convert the thermistor reading to degrees Celsius.

Instead, it uses raw ADC thresholds.

Current thresholds:

```text
TEMP_HIGH enters above 2200
TEMP_HIGH exits below 2000
```

In firmware:

```c
#define TEMP_HIGH_ENTER_THRESHOLD 2200
#define TEMP_HIGH_EXIT_THRESHOLD 2000
```

---

## 11. Temperature Hysteresis

Temperature also uses hysteresis.

Reason:

```text
Thermistor readings can fluctuate slightly.
The sensor changes gradually.
A single threshold could cause unstable alert behavior.
```

Current behavior:

```text
If Temp ADC rises above 2200 → temperature is considered HIGH.
If Temp ADC falls below 2000 → temperature returns to NORMAL.
```

This prevents rapid switching near the threshold.

---

## 12. Alert Logic

The system has three modes:

```text
NORMAL
URBAN_HEAT
TYPHOON_ALERT
```

Current alert behavior:

| Mode | Alert Condition |
|---|---|
| NORMAL | No alert |
| URBAN_HEAT | HIGH_LIGHT or TEMP_HIGH |
| TYPHOON_ALERT | LOW_LIGHT |

In firmware logic:

```text
URBAN_HEAT + HIGH_LIGHT → Alert active
URBAN_HEAT + TEMP_HIGH  → Alert active
TYPHOON_ALERT + LOW_LIGHT → Alert active
```

---

## 13. Current Calibration Status

The current calibration is good enough for the v0.1 functional prototype.

Validated behavior:

```text
LDR detects strong light changes.
Thermistor detects heat from fingers.
Hysteresis stabilizes threshold behavior.
LCD displays raw light and temperature values.
Buzzer and LED alerts respond correctly to mode-specific conditions.
```

---

## 14. Current Limitations

The current calibration has several limitations:

```text
1. Light values are raw ADC values, not lux.
2. Temperature values are raw ADC values, not degrees Celsius.
3. LDR calibration was done at night using a nearby lamp.
4. Sunlight and daytime room lighting still need to be measured.
5. The thermistor model is not yet mathematically calibrated.
```

---

## 15. Future Calibration Work

Future versions should include additional measurements:

```text
Room light during the day
Room light at night
Direct sunlight
Indirect sunlight
Different lamp distances
Ambient temperature over time
Thermistor response with known temperatures
```

Possible future improvements:

```text
Convert thermistor ADC values to approximate Celsius.
Add a calibration table.
Add moving average or exponential smoothing.
Add separate calibration constants in a config header.
Improve physical isolation of the LDR from onboard LEDs and LCD backlight.
```

---

## 16. Summary

The most important calibration result was the LDR voltage divider correction.

Changing the fixed resistor from 10kΩ to 100kΩ transformed the LDR reading from an unstable and compressed range into a useful sensor signal.

Current working sensor summary:

```text
LDR:
3V3 ── LDR ── GP26_A0 ── 100kΩ ── GND

Thermistor:
3V3 ── thermistor ── GP27_A1 ── 10kΩ ── GND
```

Current threshold summary:

```text
LOW_LIGHT enters below 700
LOW_LIGHT exits above 900

HIGH_LIGHT enters above 2500
HIGH_LIGHT exits below 2200

TEMP_HIGH enters above 2200
TEMP_HIGH exits below 2000
```

This calibration is provisional but stable enough for v0.1.
