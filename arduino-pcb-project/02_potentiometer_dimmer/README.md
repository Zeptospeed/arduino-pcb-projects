# 02: Potentiometer dimmer and LED crossfade

## Goal
Turn a potentiometer to fade one LED up while another fades down.

## Circuit
- potentiometer wiper to A0
- LEDs on PWM pins 9 and 10, each with a series resistor
TODO: add photo and hand schematic.

## Concepts learned
- analogRead() returns 0 to 1023 (10-bit ADC)
- analogWrite() PWM output, 0 to 255, only on ~ pins
- map(value, inMin, inMax, outMin, outMax) needs the real input range
- Serial Monitor for debugging

## Problems and fixes
Experiment: map(potValue, 0, 1, ...) instead of 0 to 1023. The output jumped between extremes because the input range was wrong. Correct range gives a smooth crossfade.

## Code
TODO: add sketch file.
