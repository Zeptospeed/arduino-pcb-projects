# 03: Automatic night light

## Goal
Automatically switch an LED on in darkness and allow a temporary button override.

## Circuit
- 5V → photoresistor → A0 junction → 10 kOhm resistor → GND
- LED on digital pin 3 through a series current-limiting resistor
- Button between pin 2 and GND (INPUT_PULLUP)

## Calibration and operation
- Earlier ADC test endpoints: darkVal = 5, brightVal = 900
- Current sketch: turn on below **480**, turn off above **580**
- Between those thresholds the previous light state is retained, preventing flicker
- Button override duration: **5000 ms** using millis()

The current sketch refreshes the override start time while the button is held, so its five-second countdown effectively begins when the button is released. Detecting a new press rather than a held button would change this behavior.

## Concepts learned
- Light-dependent resistor voltage divider and analogRead()
- Hysteresis with separate ON/OFF thresholds
- Pull-up button inputs and elapsed-time checks with millis()

## Problem and fix
An earlier attempt reset the timer each loop and the override did not expire correctly. The current sketch stores the timer and active flag outside loop() and checks elapsed time instead of blocking with delay().

## Code
[night_light.ino](night_light.ino)

## Optional documentation
Add a photo and a wiring schematic when available.
