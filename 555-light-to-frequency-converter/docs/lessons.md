# Lessons Learned

## 1. A simple circuit can still require disciplined debugging

The final circuit is small, but the first build produced confusing behavior.

The difficulty was not the number of components. It was the number of possible failure points introduced by power delivery, breadboard contacts, wiring, component orientation, and measurement setup.

## 2. Rebuilding from a known state can be better than endless patching

After the first assembly became difficult to reason about, the circuit was removed and rebuilt from zero.

The rebuilt circuit worked.

This does not prove what the original fault was, but it restored a controlled state and allowed the project to continue.

## 3. Nominal values and measured values are different things

The intended supply was approximately 5 V, but the successful operating circuit measured approximately 3.8 V across the rails.

Engineering documentation should record what was actually measured, not only what a module or component is supposed to provide.

## 4. Qualitative validation should come before precision measurement

Before spending time calculating exact frequencies, it was useful to answer the simpler question:

```text
Does the oscillator respond to light in the predicted direction?
```

It did.

That establishes the basic concept before deeper characterization.

## 5. The LDR turns a basic oscillator into a sensor system

The earlier NE555 blinking project used fixed timing components.

Replacing one timing resistance with an LDR creates a direct physical chain:

```text
light -> resistance -> RC timing -> frequency -> LED blink rate
```

This is a useful example of how a physical quantity can be converted into an electrical signal without a microcontroller.

## 6. Mathematics should describe the real circuit

The equation is not being added only as theory after the fact.

The goal is to measure the real LDR resistance, substitute those values into the model, predict the oscillator frequency, and compare those predictions with experimental results.

This turns the mathematical work into part of the engineering process.

## 7. Uncertainty should be documented honestly

The original failure was not conclusively diagnosed.

Instead of assigning a convenient explanation, the documentation records the observations, the debugging actions, the successful rebuild, and the remaining uncertainty.

That is more useful than a false diagnosis.

## 8. Documentation is part of the project

The project is not complete simply because the LED blinks.

A useful engineering record should preserve:

- circuit topology
- component values
- measurements
- equations
- experiments
- failures
- unresolved questions
- visual notes
- future improvements

The next stage will add handwritten Xournal++ derivations and quantitative measurements.
