# 02: Potentiometer dimmer and LED crossfade

## Goal
Turn a potentiometer to fade the blue LED down as the red LED fades up.

## Circuit
- Potentiometer outer legs: 5V and GND; middle (wiper): A0
- Blue LED: PWM pin 9, through its own current-limiting resistor
- Red LED: PWM pin 10, through its own current-limiting resistor
- Both LED cathodes return to GND

## How it works
The 10-bit ADC reports `analogRead(A0)` from 0 to 1023. Two opposite mappings create crossfade brightness values between 0 and 255:
- Blue: `map(potValue, 0, 1023, 255, 0)`
- Red: `map(potValue, 0, 1023, 0, 255)`

`analogWrite()` sends PWM signals to the LEDs; the Serial Monitor prints the input reading.

## Concepts learned
- Potentiometer voltage divider and analog sensing
- ADC range (0–1023), PWM range (0–255)
- `map()`, `analogWrite()`, Serial Monitor debugging

## Problem and fix
An experiment used `map(potValue, 0, 1, ...)`, which caused the output to jump toward the extremes. Using the actual ADC input range of 0–1023 gives smooth fading.

## Code
[potentiometer_dimmer.ino](potentiometer_dimmer.ino)

## Optional documentation
Add a breadboard photo or circuit sketch when available.
