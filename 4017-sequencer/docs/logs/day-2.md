# Day 2 — CD4017 Sequencer

## Goal
Integrate the CD4017 decade counter with the NE555 timer to create a sequential LED system.

## What I Built
- Connected the NE555 output (pin 3) to the CD4017 clock input (pin 14)
- Powered the CD4017 (pin 16 → 5V, pin 8 → GND)
- Configured control pins:
  - Pin 13 → GND (enable counting)
  - Pin 15 → GND (disable reset)
- Connected multiple LEDs to outputs Q0, Q1, and Q2

## Observations
- The NE555 continued to generate a stable clock signal
- The CD4017 advanced outputs sequentially with each pulse
- Initially, the system appeared to behave incorrectly when observing only a single output (Q0)
- Adding more LEDs revealed the correct sequential behavior

## Issues Encountered
- Misinterpreted the circuit as non-functional due to observing only one output
- Rebuilt parts of the circuit unnecessarily
- Reset the NE555 circuit despite it working correctly

## Debugging Process
- Verified power connections and pin configuration
- Confirmed clock signal from NE555
- Added additional LEDs to visualize the sequence
- Identified that the issue was conceptual, not electrical

## Key Insight
The system was working correctly from the beginning.

The problem was not the hardware, but the interpretation of its behavior.

## Technical Insight
- The CD4017 activates one output at a time (Q0 → Q9)
- Observing only one output gives an incomplete view of the system
- Sequential logic requires observing multiple states to understand behavior

## Next Step
- Improve sequence visualization
- Optionally limit the cycle using the reset pin
