# 04: Temperature-Controlled Fan

## Goal
Use a thermistor to switch a small fan on when warm and off after cooling. Separate thresholds provide hysteresis to prevent rapid on/off switching.

## Circuit
- 5V → thermistor → A0 junction → 10 kOhm resistor → GND
- Arduino D5 → 1 kOhm resistor → base of the 2N2222A transistor
- Emitter to GND; collector to motor negative; motor positive to an appropriately rated 3–6 V supply
- 1N4007 flyback diode across motor, striped cathode toward motor positive
- If using a separate motor supply, its negative terminal and Arduino GND share a common reference

**Power caution:** GPIO must not power the motor directly. Motor supply capacity and transistor suitability require checking actual startup/stall current, and the 2N2222A pinout must be verified for the specific part.

## Calibration
Recorded raw ADC observations: room temperature approximately **495**, warmed by hand approximately **597**. The firmware switches the fan ON above **550** and OFF below **520**. These values are not calibrated Celsius temperatures.

## Calculation
Estimated base current with a 5 V drive, 1 kOhm resistor and assumed 0.7 V base-emitter drop:

I_base ≈ (5 - 0.7) / 1000 = 0.0043 A = 4.3 mA

This does **not** establish the motor's running or startup current. The transistor's allowable current depends on its specific datasheet and thermal conditions. Actual motor current and its power source still need to be documented before making a driver-capability claim.

## Concepts learned
- Thermistor voltage divider and ADC thresholds
- Transistor low-side motor switching
- Flyback diode protection for an inductive load
- Hysteresis with a persistent state variable

## Problems and fixes
- Arduino power LED dimmed and components became warm. The likely cause was a misplaced breadboard jumper creating a short between the 5V and GND rails. I disconnected power, checked the breadboard connections, and corrected the wiring before testing again. This is the most likely explanation based on the symptoms, rather than a verified diagnosis.
- The analog reading was stuck near 1023 because the voltage divider was not connected correctly, likely leaving A0 too close to the 5V rail. After checking the thermistor, junction and 10 kOhm resistor connections, the readings changed normally when the thermistor was warmed.
- Code initially compared the pin constant A0 rather than analogRead(sensor); use the measured value.

## Possible improvements
- Average 10 readings to reduce noise
- Put fan output control into a setFan() function
- Add a separate high-temperature buzzer/LED alarm
- Measure and document motor current and add a real wiring photo/schematic

These upgrades are not yet implemented in the committed sketch.

## Code
[temperature_controlled_fan.ino](temperature_controlled_fan.ino)
