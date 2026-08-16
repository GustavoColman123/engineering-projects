# Problems and Debugging

## 1. The Main Debugging Story — Two Hours, No Culprit, Then a Rebuild

### Problem

The first build did not produce the expected blinking output.

What followed was the most ironic part of the project: a very small circuit turned into roughly two hours of troubleshooting.

The working hypothesis kept moving between the oscillator wiring, breadboard contacts, NE555 placement, the power module, the external adapter, and the voltage measurements.

### Debugging Performed

The circuit was progressively isolated:

- supply rails were measured
- the NE555 was removed
- the breadboard power module was tested separately
- the external adapter was measured
- other breadboard power modules were compared
- connections were repeatedly checked
- the circuit was reduced and inspected step by step

Several low and inconsistent voltage readings were observed during this process.

Despite all of that work, no single failure mechanism could be demonstrated with confidence.

### The Irony

The sequence was effectively:

```text
build circuit
-> circuit does not work
-> spend roughly two hours looking for the culprit
-> fail to isolate one definitive culprit
-> clear the breadboard
-> rebuild the same intended circuit from zero
-> circuit works
```

This is important because the successful rebuild did **not** retroactively diagnose the first build.

It only proved that a clean implementation of the intended topology could work.

### Important Engineering Note

The exact root cause of the first failure was **not conclusively isolated**.

Possible contributors included:

- breadboard contact problems
- a wiring mistake
- an unstable connection
- component placement error
- unsuitable power delivery
- measurement/setup confusion during troubleshooting
- a combination of the above

Because the evidence did not isolate one cause, no single explanation is claimed as fact.

### Resolution

The project was completely restarted from zero.

The breadboard was cleared and the same intended circuit topology was rebuilt carefully.

After the rebuild, the oscillator worked immediately enough to show a clear LED blink and the expected response to the LDR.

---

## 2. The Power Supply Is Still a Real Problem — But It Was Not Proven to Be the Main Failure

### Observation

During the successful circuit test, the supply rails measured approximately:

```text
3.8 V
```

The breadboard power arrangement also repeatedly produced values around `4 V` or below during troubleshooting, despite the intended test target being approximately `5 V`.

### Why This Matters

The supply is still considered inadequate for final characterization.

A future test setup should provide a stable, verified supply close to the intended `5 V` value before quantitative frequency measurements are treated as final.

### Why It Is Not Listed as the Root Cause

The rebuilt circuit worked while the same general power limitation was still present.

Therefore the low supply voltage cannot, by itself, be claimed as the proven cause of the first non-working build.

This distinction matters:

```text
Known limitation:
current power system provides less voltage than intended

Unknown:
what specifically prevented the first assembly from oscillating
```

The power issue remains a separate engineering task, not a convenient explanation for an unresolved failure.

---

## 3. Debugging Became More Complex Than the Circuit

### Problem

The actual oscillator contains only a small number of parts, yet the debugging process expanded into the NE555, breadboard rails, multiple power modules, the adapter, wiring, contacts, and multimeter readings.

At one point, diagnosing the test setup became harder than understanding the circuit itself.

### Lesson

When a small prototype enters a state that is no longer trustworthy, simplify aggressively.

A clean rebuild can be more useful than continuing to patch an uncertain breadboard state.

However:

> A successful rebuild is a recovery method, not a root-cause analysis.

The project recovered, but the original failure remains intentionally unresolved in the record.

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

And for this project specifically:

```text
The first failure remains unresolved.
The rebuild is confirmed working.
The low-voltage power supply remains a separate known limitation.
```
