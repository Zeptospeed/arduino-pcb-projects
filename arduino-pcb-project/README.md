# Arduino to Custom PCB

Goal: learn Arduino and basic embedded C, prototype circuits on a breadboard, then design and fabricate my own PCB in Altium and document the process.

Hardware: Elegoo UNO R3 Super Starter Kit (ATmega328P).

## Progress log

| # | Project | Concepts | Status |
|---|---------|----------|--------|
| 01 | [Button-Controlled LEDs](01_button_led_control/) | Digital input/output, pull-up resistor | Done |
| 02 | [Dual-LED Light Dimmer](02_light_dimmer/) | Analog input, PWM, mapping | Done |
| 03 | [Automatic Night Light](03_automatic_night_light/) | Light sensing, hysteresis, millis() | Done |
| 04 | [Temperature-Controlled Fan](04_temperature_controlled_fan/) | Thermistor, transistor motor switching, hysteresis | Core working; improvements planned |
| 05 | [Ultrasonic Parking Assist System](05_parking_assist_system/) | Distance sensing, median filter, LCD, non-blocking buzzer | Working prototype; measurements/photos to add |
| 06 | PCB capstone (planned) | Schematic capture, PCB layout, fabrication | Not started |

## Repository layout
Each numbered project folder includes its Arduino sketch and a README explaining the circuit, concepts, and troubleshooting. Photos and schematics will be added where available.
