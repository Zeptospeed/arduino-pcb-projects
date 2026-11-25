# 05: Automotive parking assist

## Goal
Build a prototype parking-assist system that measures the distance to nearby objects and communicates risk through a 16x2 LCD, three colored LEDs, and a buzzer. This is a learning prototype, **not** a safety-rated vehicle parking system.

## Hardware
- ELEGOO Arduino UNO R3 / ATmega328P
- HC-SR04 ultrasonic distance sensor
- 16x2 parallel LCD1602 and a 10 kOhm contrast potentiometer
- Green, yellow, and red LEDs with individual 220 Ohm current-limiting resistors
- Passive buzzer, breadboard, jumper wires and USB power
- LCD backlight through an appropriate current-limiting resistor (220 Ohm in this build)

## Wiring
| Component | Arduino UNO connection |
|---|---|
| HC-SR04 VCC / GND | 5V / GND |
| HC-SR04 TRIG / ECHO | D2 / D8 |
| Green / yellow / red LED anodes (through 220 Ohm resistors) | D9 / D10 / D11 |
| All LED cathodes | GND |
| Passive buzzer + / - | D6 / GND |
| LCD VSS / VDD / RW | GND / 5V / GND |
| LCD RS / E | D12 / D13 |
| LCD D4 / D5 / D6 / D7 | D3 / D4 / D5 / D7 |
| LCD VO | Middle leg of 10 kOhm contrast potentiometer; outer legs to 5V and GND |
| LCD backlight A / K | 5V through 220 Ohm resistor / GND |

LCD D0–D3 are unused (4-bit mode). Verify component pin labels before connecting power.

## Warning behavior
| Distance | LCD status | Indicator | Buzzer |
|---|---|---|---|
| More than 100 cm | SAFE | Green | Off |
| 50–100 cm | CAUTION | Yellow | 300 ms on / 700 ms off |
| 20–less than 50 cm | DANGER | Red | 150 ms on / 150 ms off |
| Less than 20 cm | STOP | Red | Continuous |
| No valid echoes in five attempts | UNKNOWN | All off | Off |

No echo is treated as **unknown**, not as a distance of zero.

## Implementation
- The ultrasonic sensor is triggered with a 10 us pulse; echo pulse duration is converted to centimeters using `distance_cm = duration_us * 0.0343 / 2`.
- A sensor attempt is scheduled approximately every 60 ms via `millis()`.
- Five attempts form a batch. Timeout measurements are excluded; the valid values are selection-sorted and the middle reading is selected. For even valid counts, the upper middle value is used.
- If every attempt times out, the function returns `-1` for no signal.
- Buzzer timing uses a separate `millis()` clock and resets when the warning status changes.
- `pulseIn(..., 30000)` can still block up to about 30 ms. This is not a fully interrupt-driven sensor implementation.

## Concepts learned
- Digital sensors and pulse timing
- Time-of-flight distance calculation
- Filtering readings with arrays and selection sort
- Handling missing measurements instead of treating them as 0 cm
- Non-blocking buzzer timing using `millis()`
- Integrating an LCD, LEDs and sound into one embedded system

## Testing and limitations
The prototype was tested on hardware with working distance, LCD, LED, and buzzer behavior. Repeatable measurements were observed with a flat target around 15 cm; readings near the sensor's approximate 2 cm minimum were less reliable.

Before relying on the results quantitatively, record measurements against a ruler at several known distances (for example 10, 20, 30, 50, and 100 cm). The median filter reduces isolated spikes but does not guarantee a correct measurement. Reflective surfaces, object angle, missing echoes, and sensor range remain limitations.

## Problems and fixes
- Occasional large outliers: added a median filter over batches of five readings.
- Missing echo returned a zero duration and could trigger a false STOP: ignore timeouts and display UNKNOWN when all five measurements fail.
- Blocking buzzer delays slowed updates: replaced delay-based beeping with a state machine driven by `millis()`.

## Still to do
- Add a prototype photo, a wiring schematic, and a short demonstration video.
- Add a measured accuracy table and response-time observations.
- Test additional edge cases and compare filtering with raw measurements.

## Code
[parking_assist.ino](parking_assist.ino)
