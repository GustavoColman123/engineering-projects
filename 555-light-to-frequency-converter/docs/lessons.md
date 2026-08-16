# Lessons Learned

## 1. A simple circuit can still produce a long debugging session

The final circuit is small, but the first build turned into roughly two hours of troubleshooting.

That contrast is one of the most useful lessons from the project:

```text
small circuit != trivial debugging
```

The difficulty came from the number of possible failure points around the circuit: breadboard contacts, wiring, component placement, power delivery, and measurement setup.

## 2. The strangest outcome can still be the correct engineering record

The actual sequence was:

```text
build
-> does not work
-> investigate for roughly two hours
-> no definitive culprit found
-> rebuild from zero
-> works
```

It would be tempting to rewrite that story later and assign a neat cause to the original failure.

That would be inaccurate.

The correct record is that the first build failed, the root cause was not isolated, and the clean rebuild restored operation.

## 3. Rebuilding from a known state can be better than endless patching

After the first assembly became difficult to reason about, the circuit was removed and rebuilt from zero.

The rebuilt circuit worked.

This made the rebuild an effective recovery strategy, even though it was not a diagnosis.

The distinction is important:

```text
recovery: achieved
root cause: unresolved
```

## 4. A known problem does not automatically explain every failure

The power system remains a real limitation.

The intended test supply was approximately `5 V`, while the successful operating circuit measured approximately `3.8 V`, and values around `4 V` or below were repeatedly observed during troubleshooting.

However, the circuit still worked after the rebuild while that power limitation remained.

Therefore the low supply voltage is documented as a separate known issue, not as the proven cause of the first failed assembly.

This is a useful general lesson:

> Correlation during debugging is not the same as demonstrated causation.

## 5. Nominal values and measured values are different things

A module may be configured or labeled for a target voltage, but the relevant engineering quantity is the voltage actually measured at the circuit.

For this prototype:

```text
intended supply: ~5 V
measured successful-session supply: ~3.8 V
```

Future quantitative characterization should use a stable, verified supply near the intended value.

## 6. Qualitative validation should come before precision measurement

Before spending time calculating exact frequencies, it was useful to answer the simpler question:

```text
Does the oscillator respond to light in the predicted direction?
```

It did.

That establishes the basic concept before deeper characterization.

## 7. The LDR turns a basic oscillator into a sensor system

The earlier NE555 blinking project used fixed timing components.

Replacing one timing resistance with an LDR creates a direct physical chain:

```text
light -> resistance -> RC timing -> frequency -> LED blink rate
```

This is a useful example of how a physical quantity can be converted into an electrical signal without a microcontroller.

## 8. Mathematics should describe the real circuit

The equation is not being added only as theory after the fact.

The goal is to measure the real LDR resistance, substitute those values into the model, predict the oscillator frequency, and compare those predictions with experimental results.

This turns the mathematical work into part of the engineering process.

## 9. Uncertainty should be documented honestly

The original failure was not conclusively diagnosed.

Instead of assigning a convenient explanation, the documentation records:

- what failed
- what was tested
- what remained uncertain
- what changed after the rebuild
- what problems still exist independently

That is more useful than a false diagnosis.

## 10. Documentation is part of the project

The project is not complete simply because the LED blinks.

A useful engineering record should preserve:

- circuit topology
- component values
- measurements
- equations
- experiments
- failures
- unresolved questions
- visual evidence
- future improvements

In this project, even the messy debugging story is part of the result.

The next stage will add handwritten Xournal++ derivations and quantitative measurements using a better-verified supply.
