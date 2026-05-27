# Day 02 — LDR Debugging

## Goal

Add an LDR light sensor to Pico Resilience Monitor v0 and read its value through the Raspberry Pi Pico ADC.

The objective was to detect changes in ambient light and later use those readings for alert logic.

---

## Components Used

```text
Raspberry Pi Pico
Breadboard
LDR photoresistor
Fixed resistor
Jumper wires
Existing digital base from Day 01
```

---

## Initial Plan

The LDR was connected as a voltage divider using GP26_A0 / ADC0.

Initial circuit:

```text
3V3 ── LDR ── GP26_A0 ── 10kΩ ── GND
```

Expected behavior:

```text
More light  → ADC value increases
Less light  → ADC value decreases
```

---

## Initial Problem

The readings were unstable and compressed.

Observed ADC values stayed around:

```text
300–500
```

The value did not react clearly when the LDR was covered or illuminated.

This made the sensor unusable for reliable light classification.

---

## Possible Causes Considered

Several possible causes were considered:

```text
LDR placed incorrectly
Wrong ADC pin
Bad jumper connection
Wrong breadboard row
Incorrect GND connection
Incorrect 3.3V connection
Damaged LDR
Wrong ADC channel in code
Bad resistor value
```

---

## ADC Isolation Test

To verify whether the Pico ADC was working, the LDR was removed and replaced with a potentiometer connected to GP26_A0.

The potentiometer test worked correctly.

Observed behavior:

```text
Turning the potentiometer one way increased the ADC value.
Turning it the other way decreased the ADC value.
```

This confirmed that:

```text
GP26_A0 was working.
The ADC was working.
The firmware was reading the correct channel.
The serial monitor was working.
```

Therefore, the problem was not the Pico or the code.

---

## LDR Validation

The LDR was tested separately with a multimeter.

The resistance changed between light and darkness, confirming that the LDR itself was functional.

This narrowed the problem down to the voltage divider design.

---

## Final Diagnosis

The 10kΩ resistor was not appropriate for the resistance range of the LDR under the tested lighting conditions.

With the 10kΩ resistor, the voltage at GP26_A0 stayed too low and too compressed.

The circuit was technically connected, but not well dimensioned.

---

## Solution

The fixed resistor was changed from:

```text
10kΩ
```

to:

```text
100kΩ
```

Final working circuit:

```text
3V3 ── LDR ── GP26_A0 ── 100kΩ ── GND
```

---

## Result

After changing to 100kΩ, the ADC response improved significantly.

Observed values:

```text
Lamp off / low light: approximately 250–320
Strong nearby lamp: approximately 3600+
```

This created a useful measurement range for the project.

---

## Light Classification

After the LDR produced stable readings, light was classified into three states:

```text
LOW_LIGHT
NORMAL_LIGHT
HIGH_LIGHT
```

Initial thresholds were later improved with hysteresis.

Final hysteresis thresholds:

```text
LOW_LIGHT enters below 700
LOW_LIGHT exits above 900

HIGH_LIGHT enters above 2500
HIGH_LIGHT exits below 2200
```

---

## Important Mistake: 3V3_EN

During the process, there was confusion between:

```text
3V3
```

and:

```text
3V3_EN
```

The `3V3_EN` pin was mistakenly considered as a possible replacement for the 3.3V power pin.

This caused the system to shut down or behave unstably.

Final rule:

```text
Use 3V3 as the power source.
Do not use 3V3_EN as a power output.
```

---

## Important Mistake: LED Interference

A blue LED was accidentally connected in a way that made it stay permanently on.

This interfered with the LDR readings because the light sensor was detecting light from the circuit itself.

The LED was removed from the 3.3V rail and connected correctly as a GPIO-controlled output.

Final rule:

```text
LEDs used as indicators must be connected to GPIO pins, not directly to the 3.3V rail.
```

---

## Lessons Learned

The main lessons from this debugging session were:

```text
A working sensor still needs a correctly designed surrounding circuit.
ADC problems should be isolated using known-good analog sources.
A potentiometer is useful for testing ADC behavior.
The value of the voltage divider resistor strongly affects ADC range.
3V3_EN is not a normal power output.
Nearby LEDs can contaminate light sensor readings.
```

---

## Final Status

The LDR circuit was successfully validated with a 100kΩ resistor.

The light sensor became stable enough to use in the project’s alert logic.

Status:

```text
Completed successfully after debugging.
```
