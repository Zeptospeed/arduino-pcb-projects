// Project 03: automatic night light with button override

int led = 3;
int button = 2;
int sensor = A0;

int turn_on_below = 480;   // dark: LED on
int turn_off_above = 580;  // bright: LED off (must be higher than turn_on_below)
unsigned long override_ms = 5000;

int is_dark = 0;
int override_active = 0;
unsigned long override_start = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(sensor);
  unsigned long now = millis();

  // hysteresis: two thresholds
  if (is_dark == 0) {
    if (light < turn_on_below) {
      is_dark = 1;
    }
  } else {
    if (light > turn_off_above) {
      is_dark = 0;
    }
  }

  // button starts (or restarts) the override timer
  if (digitalRead(button) == LOW) {
    override_active = 1;
    override_start = now;
  }
  if (override_active == 1 && now - override_start >= override_ms) {
    override_active = 0;
  }

  if (is_dark == 1 || override_active == 1) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  Serial.println(light);
}
