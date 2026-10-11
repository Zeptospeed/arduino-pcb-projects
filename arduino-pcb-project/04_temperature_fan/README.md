# 04: Temperature-controlled fan

## Goal
A thermistor measures temperature. The fan turns on when it gets warm and off when it cools. Planned: buzzer and LED alarm at a higher temperature.

## Circuit
- Thermistor divider: 5V to thermistor to junction to 10 kOhm to GND, junction to A0
- Fan: pin 5 to 1 kOhm to base of NPN transistor (2N2222A), emitter to GND, collector to motor, motor other side to 5V
- 1N4007 diode across the motor, stripe toward 5V (flyback protection)
TODO: add photo and hand schematic.

## Calibration
- room temperature reading: 495
- hand temperature reading: 597
- fan on above 550, fan off below 520

## Calculations
- Transistor base current: (5 V - 0.7 V) / 1 kOhm = 4.3 mA
- TODO: add the measured or estimated motor current and the transistor's rating

## Concepts learned
- an Arduino pin can't drive a motor directly, so a transistor switches it
- why the flyback diode is needed across an inductive load
- hysteresis with a state variable so the fan doesn't flicker
- verified transistor pinout (E-B-C, flat face toward me) with an LED test circuit

## Problems and fixes
- Arduino ON light dimmed and parts got warm: a wiring short. TODO: write what the actual cause was.
- analogRead stuck at 1023: divider wiring fault. TODO: write what the actual cause was.
- Bug in my code: compared the pin name (A0) instead of the reading.

## Still to do
- average 10 readings with a for loop
- move fan control into a setFan() function
- buzzer and LED alarm at a third threshold

## Code
temperature_fan.ino
