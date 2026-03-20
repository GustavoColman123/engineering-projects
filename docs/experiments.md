# Experiments

Experiment 1 — R2 Variation

### Setup
R2 values tested: 100kΩ and 220kΩ  
Other components remained unchanged:
- R1 = 1kΩ
- Capacitor = 10µF
- Supply = 5V

### Observation
- With 100kΩ, the LED blinked quickly and was difficult to count
- With 220kΩ, the LED stayed ON for approximately 2 seconds and OFF for approximately 2 seconds

### Explanation
Increasing R2 reduces the current flowing into the capacitor, which increases the time required for it to charge.

This results in a longer oscillation period and slower blinking.

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
