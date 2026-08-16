# Problems and Debugging

## 1. First Assembly Did Not Oscillate

### Problem

The first build did not produce the expected blinking output.

At the same time, supply-voltage measurements became inconsistent and significantly lower than the intended value.

### Debugging Performed

The circuit was progressively isolated:

- supply rails were measured
- the NE555 was removed
- the breadboard power module was tested separately
- the external adapter was measured
- other breadboard power modules were compared

Several low and inconsistent voltage readings were observed during this process.

### Important Engineering Note

The exact root cause was **not conclusively isolated**.

Possible contributors included:

- breadboard contact problems
- a wiring mistake
- unstable or unsuitable power delivery
- measurement/setup error during troubleshooting
- a combination of the above

Because the evidence did not isolate one cause, no single explanation is claimed as fact.

### Resolution

The project was completely restarted from zero.

The breadboard was cleared and the same intended circuit topology was rebuilt carefully.

After the rebuild, the oscillator worked and the LED responded correctly to the LDR.

---

## 2. Power Supply Does Not Match the Intended Test Voltage

### Problem

During the successful circuit test, the supply rails measured approximately:

```text
3.8 V
```

This is lower than the intended `5 V` test supply.

### Effect

The circuit still produced a clear oscillating output and responded to changes in light, so the proof of concept was successful.

However, this power arrangement is not considered suitable for final quantitative characterization.

### Current Decision

Do not treat measurements from the current supply as final frequency-performance data.

A stable, known supply should be used before theoretical-vs-experimental error calculations are finalized.

---

## 3. Debugging Became More Complex Than the Circuit

### Problem

The initial debugging path involved the NE555, breadboard rails, power modules, external adapter, and multimeter measurements simultaneously.

This created too many possible failure points at once.

### Lesson

When a small circuit behaves unexpectedly, simplify the system aggressively.

A complete rebuild can be more reliable than continuing to modify a state that is no longer understood.

The successful second build demonstrated the value of returning to a known baseline.

---

## 4. Missing 10 nF Control-Pin Capacitor

### Situation

A `10 nF` (`103`) capacitor was not available during the build.

A `100 nF` (`104`) capacitor was available and was used for supply decoupling between VCC and GND.

Pin 5 (CONTROL) was left unconnected in v0.1.

### Result

The circuit still produced the expected qualitative oscillation and light response.

This configuration is documented explicitly so the physical prototype can be reproduced accurately.

---

## Debugging Principle Adopted

For future revisions:

```text
verify supply
-> verify IC orientation
-> verify fixed power pins
-> verify timing node
-> verify timing network
-> verify output
-> change only one variable at a time
```

Most importantly:

> Do not invent a root cause just because the circuit works after rebuilding it.

A failure is only diagnosed when evidence isolates the cause.
