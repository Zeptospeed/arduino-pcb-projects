# 03: Automatic night light

## Goal
LED turns on when the room is dark, and a button keeps it on for 5 seconds.

## Circuit
- 5V to photoresistor to junction to 10 kOhm to GND (voltage divider)
- junction to A0
- LED on pin 3 through a series resistor
- button on pin 2 to GND (INPUT_PULLUP)
TODO: add photo and hand schematic.

## Calibration
- darkVal = 5, brightVal = 900 (raw analogRead values)

## Concepts learned
- voltage divider turns a changing resistance into a voltage the ADC can read
- calibrating thresholds from real readings
- hysteresis (two thresholds) to stop flicker
- non-blocking timing with millis()

## Problem and fix
My first version reset the timer variable every loop, so the 5-second timer never ended and the LED was only on while the button was held. Fix: start the timer when the button is pressed, keep a flag that the override is active, and check elapsed time outside the button branch.

## Code
night_light.ino (version after the fix)
