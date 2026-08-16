# Engineering Projects

This repository contains my hands-on experiments and small projects in electronics, embedded systems, and hardware.

The purpose of this repository is to document my learning process through real circuits, firmware, debugging, mistakes, and improvements.

Each project is treated as a small engineering exercise, not just as a final result.

---

## Repository Structure

Each folder represents an individual project.

A project may include:

* Objective
* Circuit explanation
* System design
* Firmware or source code
* Problems encountered
* Lessons learned
* Logs and documentation
* Photos or diagrams

The goal is to make each project understandable, reproducible, and useful for future learning.

---

## Projects

### [555 Light-to-Frequency Converter](./555-light-to-frequency-converter/)

A light-sensitive oscillator built around an NE555 timer in astable mode.

An LDR replaces one of the fixed timing resistances, converting changes in illumination into changes in oscillator frequency without a microcontroller.

Main concepts used:

* NE555 astable oscillator behavior
* LDR photoresistor response
* RC timing networks
* Light-to-frequency conversion
* Capacitor charge/discharge timing
* Mathematical modeling of oscillator frequency
* Qualitative experimental validation
* Breadboard debugging and measurement discipline

Important technical result:

```text
The rebuilt v0.1 circuit produced a clear blinking output.
More light on the LDR increased the blink rate.
Covering the LDR reduced the blink rate.
```

Current limitation:

```text
The working prototype measured approximately 3.8 V across the supply rails.
Quantitative characterization is deferred until a stable, known supply is available.
```

Status:

```text
v0.1 functional breadboard proof of concept completed.
Mathematical and quantitative characterization in progress.
```

Documentation:

* [Project README](./555-light-to-frequency-converter/README.md)
* [System design](./555-light-to-frequency-converter/docs/design.md)
* [Wiring](./555-light-to-frequency-converter/docs/wiring.md)
* [Theory and mathematical model](./555-light-to-frequency-converter/docs/theory.md)
* [Measurements](./555-light-to-frequency-converter/docs/measurements.md)
* [Experiments](./555-light-to-frequency-converter/docs/experiments.md)
* [Problems and debugging](./555-light-to-frequency-converter/docs/problems.md)
* [Lessons learned](./555-light-to-frequency-converter/docs/lessons.md)
* [Day 0 log](./555-light-to-frequency-converter/logs/day-00-project-start.md)
* [Xournal++ plan](./555-light-to-frequency-converter/xournal/README.md)

---

### [Pico Resilience Monitor v0](./pico-resilience-monitor-v0/)

A Raspberry Pi Pico environmental monitoring prototype built with C and the Pico SDK.

This project uses a light sensor, thermistor, LCD1602 I2C display, push button, LEDs, and buzzer to simulate a small embedded monitoring and alert system.

The system has three modes:

* `NORMAL`
* `URBAN_HEAT`
* `TYPHOON_ALERT`

The project is indirectly inspired by resilient infrastructure, environmental monitoring, and applied embedded systems.

Main concepts used:

* GPIO input with internal pull-up resistor
* GPIO output for LEDs and buzzer
* ADC reading with the Raspberry Pi Pico
* LDR light sensing through a voltage divider
* Thermistor temperature sensing through a voltage divider
* I2C communication with an LCD1602 display
* Finite state machine in C
* Button debounce logic
* Sensor classification using thresholds
* Hysteresis for stable alert behavior
* Serial debugging over USB
* Hardware debugging and calibration

Important technical result:

```text
The LDR circuit initially produced compressed ADC readings with a 10kΩ resistor.
After testing the ADC with a potentiometer, the issue was diagnosed as a voltage divider problem.
Replacing the resistor with 100kΩ produced a much wider and more useful ADC range.
```

Status:

```text
v0.1 functional breadboard prototype completed and documented.
```

Documentation:

* [Project README](./pico-resilience-monitor-v0/README.md)
* [System design](./pico-resilience-monitor-v0/docs/design.md)
* [Wiring](./pico-resilience-monitor-v0/docs/wiring.md)
* [Calibration](./pico-resilience-monitor-v0/docs/calibration.md)
* [Problems and debugging](./pico-resilience-monitor-v0/docs/problems.md)
* [Lessons learned](./pico-resilience-monitor-v0/docs/lessons.md)
* [Photo evidence](./pico-resilience-monitor-v0/docs/evidence.md)
* [Firmware notes](./pico-resilience-monitor-v0/firmware/README.md)

---

### [Embedded Desk Terminal v0](./embedded-desk-terminal-v0/)

My first documented Raspberry Pi Pico project.

This project is a small embedded system built with a Raspberry Pi Pico, an LCD1602 I2C display, a push button, an LED, and an SG90 micro servo.

The firmware is written in C using the Raspberry Pi Pico SDK.

Main concepts used:

* GPIO output for LED control
* GPIO input with internal pull-up resistor
* I2C communication with an LCD1602 display
* PWM control for an SG90 servo
* Button debounce logic
* Finite state machine in C
* Breadboard prototyping before soldering

Status:

```text
Functional breadboard prototype completed.
```

---

### [4017 LED Sequencer](./4017-sequencer/)

A sequential LED circuit using the CD4017 decade counter.

The CD4017 is driven by a clock signal generated by a NE555 timer configured in astable mode.

Main concepts used:

* Sequential digital outputs
* Clock pulses
* CD4017 decade counter behavior
* NE555 timer in astable mode
* LED output sequencing
* Basic timing and digital logic

Status:

```text
Functional circuit completed and documented.
```

---

### [NE555 LED Blinking Circuit](./ne555-led-blink/)

My first electronics project using the NE555 timer.

This project explores how the NE555 can generate a blinking signal for an LED using resistors and a capacitor.

Main concepts used:

* NE555 timer basics
* Astable oscillator behavior
* Resistor-capacitor timing
* LED current limiting
* Breadboard prototyping
* Basic circuit debugging

Status:

```text
Completed.
```

---

## Learning Goals

This repository is part of my long-term learning path in electronics, embedded systems, and computer engineering.

The main goals are:

* Build real circuits instead of only studying theory
* Understand how components behave in practice
* Learn how to debug hardware and software problems
* Improve technical documentation
* Develop projects that can be reviewed later
* Build a foundation for more advanced embedded and robotics projects

---

## Tools and Technologies

Tools and components used across the projects include:

* Breadboards
* Raspberry Pi Pico
* Raspberry Pi Pico SDK
* C
* CMake
* Git and GitHub
* Xournal++
* NE555 timer
* CD4017 decade counter
* LCD1602 I2C display
* SG90 micro servo
* LEDs
* Active buzzer
* Push buttons
* LDR photoresistor
* NTC thermistor
* Resistors and capacitors
* Multimeter
* USB serial debugging

---

## Documentation Philosophy

The purpose of this repository is not only to show working projects.

It is also meant to show the process:

* What was attempted
* What worked
* What failed
* What was misunderstood
* How problems were solved
* What was learned from each project

Mistakes and debugging notes are included because they are part of real engineering work.

---

## Current Status

This repository currently contains beginner-level electronics and embedded systems projects.

The projects are small, but they are documented seriously and are intended to build a foundation for future work in:

* Embedded systems
* Robotics
* Hardware design
* Low-level programming
* Digital logic
* Computer engineering fundamentals

Current documented projects:

```text
555 Light-to-Frequency Converter
Pico Resilience Monitor v0
Embedded Desk Terminal v0
4017 LED Sequencer
NE555 LED Blinking Circuit
```
