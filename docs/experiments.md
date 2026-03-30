# Experiments

Experiment 1 — R2 Variation

### Setup
R2 values tested: 100kΩ, 220kΩ, 470kΩ
Other components remained unchanged:
- R1 = 1kΩ
- Capacitor = 10µF
- Supply = 5V

### Observation
- With 100kΩ, the LED blinked quickly and was difficult to count
- With 220kΩ, the LED stayed ON for approximately 2 seconds and OFF for approximately 2 seconds
- With 470kΩ, the LED stayed ON for approximately 4 seconds and OFF for approximately 4 seconds

### Explanation
Increasing R2 increases the charging time of the capacitor.

This results in a longer oscillation period and slower LED blinking.

Experimental results confirmed this behavior:
- 100kΩ → fast blinking
- 220kΩ → ~2 seconds ON / ~2 seconds OFF

This demonstrates the direct relationship between resistance and timing in the 555 timer.
This experiment also helped establish the foundation for understanding the effect of capacitance in the next experiment.
The system is predictable and not random; changes in resistance directly affect timing behavior.

### Problems Encountered

#### 1. Circuit stopped working after changing components
- After modifying R2, the circuit failed to operate correctly

#### Cause (estimated)
- Incorrect placement of components on the breadboard
- Possible misalignment of pins

#### Solution
- Rebuilt the circuit step by step
- Verified each connection carefully

#### 2. Multiple debugging cycles required
- The circuit had to be rebuilt several times

#### Cause
- Changing multiple things unintentionally during testing

#### Solution
- Focused on changing only one variable at a time

### Lessons Learned

- Changing a single component can break the entire circuit
- Always verify connections after modifications
- Breadboard alignment is critical
- Debugging requires patience and structured thinking


## Experiment 2 — Capacitor Variation

### Setup
Capacitor values tested:
- 10µF
- 100µF

Other components remained unchanged:
- R1 = 1kΩ
- R2 = 220kΩ
- Supply = 5V

### Observation
- With 10µF, the LED blinked approximately every 4–5 seconds (ON + OFF cycle)
- With 100µF, the LED stayed ON for ~40 seconds and OFF for ~40 seconds (~80 seconds total cycle)

### Explanation
Increasing the capacitance significantly increases the time required for the capacitor to charge and discharge.

This results in a much longer oscillation period.

Experimental results confirmed:
- 10µF → fast cycle (~5 seconds)
- 100µF → very slow cycle (~80 seconds)

This demonstrates that capacitance has a strong impact on timing behavior.

### Insight
The oscillation period is influenced by both resistance and capacitance.

This reinforces the idea that:
Time ∝ R × C

### Problems Encountered

#### 1. Circuit appeared to be not working
- After changing to a 100µF capacitor, the LED took a long time to respond

#### Cause (estimated)
- Misinterpretation: the circuit was working, but the timing was much longer than expected

#### Solution
- Waited and observed carefully
- Measured the actual timing using a timer
