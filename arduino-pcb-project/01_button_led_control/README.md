# 01: Button-Controlled LEDs

## Goal
Press a button to control two LEDs using digital input and output.

## Circuit
- Button: digital pin 7 to GND, with INPUT_PULLUP
- LED 1: output pin 8; LED 2: output pin 13
- Each external LED uses its own series current-limiting resistor (e.g., 220 Ohm) and connects back to GND

## Behavior
The input normally reads HIGH because of the internal pull-up. Pressing the button connects it to GND, producing LOW. The sketch turns both LEDs on only while the button is pressed.

## Concepts learned
- pinMode(), digitalRead(), digitalWrite()
- Digital HIGH/LOW and internal pull-up resistors
- LED polarity and current-limiting resistors

## Problems and fixes
A pull-up button has inverted logic: pressed means LOW, rather than HIGH. The sketch correctly checks digitalRead(button) == LOW.

## Code
[button_led_control.ino](button_led_control.ino)

## Optional documentation
Add a hardware photo or circuit sketch when available.
