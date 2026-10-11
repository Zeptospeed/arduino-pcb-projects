# Arduino to Custom PCB

Goal: learn Arduino and basic embedded C, prototype circuits on a breadboard, then design and fabricate my own PCB in Altium and document the whole process.

Hardware: Elegoo UNO R3 Super Starter Kit (ATmega328P).

## Progress log

| # | Project | Concepts | Status |
|---|---------|----------|--------|
| 01 | Button controlling an LED | digital input, pull-up resistor, digital output | done |
| 02 | Potentiometer dimmer / LED crossfade | analogRead, PWM, map(), Serial Monitor | done |
| 03 | Automatic night light | voltage divider, sensor threshold, hysteresis, millis() timer | done |
| 04 | Temperature-controlled fan | thermistor, NPN transistor driving a motor, flyback diode, hysteresis | core working, alarm in progress |
| 05 | PCB capstone (planned) | schematic capture, layout, design rules, fabrication | not started |

## Repo layout
Each folder has a README (what I built, calculations, problems and fixes) and the Arduino sketch. Photos and hand-drawn schematics go in each folder.
