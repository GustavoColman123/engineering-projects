# Day 04 — Thermistor Integration

## Goal

Add a thermistor to Pico Resilience Monitor v0 and use it as a basic temperature-related input.

The goal was not to measure exact temperature in degrees Celsius yet, but to detect relative temperature changes and use them in the system's alert logic.

---

## Components Used

```text
Raspberry Pi Pico
Breadboard
NTC thermistor
10kΩ resistor
Jumper wires
Existing LEDs, button, buzzer, LDR, and LCD
```

---

## Thermistor Identification

The thermistor was identified from the kit as a small black resistive component with two legs.

Before integrating it into the circuit, its behavior was checked:

```text
Resistance changes when temperature changes.
```

This confirmed that it was suitable for use as a temperature-sensitive analog input.

---

## Wiring

The thermistor was connected as a voltage divider.

Final circuit:

```text
3V3 ── thermistor ── GP27_A1 ── 10kΩ ── GND
```

Detailed wiring:

```text
One side of the thermistor → 3.3V rail

Other side of the thermistor → central analog node

Central analog node → GP27_A1
Central analog node → one side of 10kΩ resistor

Other side of 10kΩ resistor → GND rail
```

The central node is the point read by the Pico ADC.

---

## ADC Pin Used

The thermistor uses:

```text
GP27_A1 / ADC1
```

This keeps it separate from the LDR, which uses:

```text
GP26_A0 / ADC0
```

Current analog input map:

```text
GP26_A0 → LDR light sensor
GP27_A1 → Thermistor temperature sensor
```

---

## Initial Reading Test

The thermistor was first tested using raw ADC values.

Expected behavior:

```text
If the thermistor reacts to heat, the ADC value should change when touched.
```

Observed behavior:

```text
When pressed with fingers, the ADC value increased.
When released, the value gradually decreased.
```

This confirmed that the thermistor was working in the circuit.

---

## Observed Values

Measured values during testing:

| Condition | Temp ADC |
|---|---|
| Resting temperature | ~1850 |
| Held between fingers | ~2360 |
| After release | returns near ~1860 |

The response was gradual, which is expected for a temperature-sensitive component.

---

## Direction of Change

With the current circuit:

```text
3V3 ── thermistor ── GP27_A1 ── 10kΩ ── GND
```

The observed behavior was:

```text
More heat → ADC value increases
Less heat → ADC value decreases gradually
```

This behavior was used directly in the firmware logic.

---

## Temperature Thresholds

Based on the observed values, a high-temperature threshold was added.

Thresholds:

```text
TEMP_HIGH enters above 2200
TEMP_HIGH exits below 2000
```

Firmware constants:

```c
#define TEMP_HIGH_ENTER_THRESHOLD 2200
#define TEMP_HIGH_EXIT_THRESHOLD 2000
```

---

## Why Hysteresis Was Added

A single threshold could cause unstable behavior if the value fluctuates near the boundary.

Instead of this:

```text
Temp ADC > 2200 → HIGH
Temp ADC <= 2200 → NORMAL
```

The system uses hysteresis:

```text
Enter TEMP_HIGH above 2200
Exit TEMP_HIGH below 2000
```

This prevents rapid switching near the threshold.

---

## Firmware Logic

Temperature is currently represented as a boolean state:

```c
bool current_temp_high;
```

The update function checks whether the system should enter or exit the high-temperature state.

Simplified behavior:

```text
If temperature is normal and Temp ADC rises above 2200:
    TEMP_HIGH becomes true

If temperature is high and Temp ADC falls below 2000:
    TEMP_HIGH becomes false
```

---

## Integration With Urban Heat Mode

The `URBAN_HEAT` mode now activates an alert if either condition is true:

```text
HIGH_LIGHT
or
TEMP_HIGH
```

Current alert logic:

```text
NORMAL:
    no alert

URBAN_HEAT:
    alert if HIGH_LIGHT or TEMP_HIGH

TYPHOON_ALERT:
    alert if LOW_LIGHT
```

This made `URBAN_HEAT` more meaningful because it no longer depends only on strong light.

---

## LCD Integration

The LCD displays the raw thermistor ADC value together with the light value.

Example:

```text
MODE:HEAT
L3600 T2360 ALRT
```

Where:

```text
L3600 = LDR ADC value
T2360 = thermistor ADC value
ALRT  = alert active
```

---

## Serial Debug Output

The serial output was updated to include temperature state.

Example:

```text
Mode: HEAT | Light ADC: 3600 | Light: HIGH | Temp ADC: 2360 | Temp: HIGH | Alert: ACTIVE
```

This made debugging easier because both the raw ADC value and the interpreted temperature state are visible.

---

## Result

By the end of this stage, the thermistor was successfully integrated.

Validated behavior:

```text
Thermistor ADC reading works
Touching the thermistor increases the ADC value
Releasing it makes the ADC value decrease gradually
High-temperature threshold works
Hysteresis works
URBAN_HEAT alert responds to high temperature
LCD displays temperature ADC value
Serial debug output includes temperature state
```

---

## Current Limitation

The thermistor is not yet converted to degrees Celsius.

The project currently uses raw ADC values for relative temperature classification.

To calculate approximate Celsius in the future, the following information would be needed:

```text
Nominal thermistor resistance
Beta coefficient
Reference temperature
Exact fixed resistor value
ADC reference voltage
```

A future version may implement the thermistor equation or the Steinhart-Hart approximation.

---

## Lessons Learned

Important lessons from this stage:

```text
A thermistor can be used as a simple analog temperature input.
The ADC value can be useful even before converting to Celsius.
Temperature sensors respond more slowly than light sensors.
Hysteresis is useful for temperature thresholds.
A mode becomes more meaningful when its alert logic matches its purpose.
```

---

## Final Status

The thermistor integration was completed successfully.

Status:

```text
Completed successfully.
```
