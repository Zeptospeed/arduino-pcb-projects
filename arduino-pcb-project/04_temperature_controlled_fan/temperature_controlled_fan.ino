// Project 04: thermistor controls a transistor-driven fan with hysteresis

int sensor = A0;
int fan = 5;

int fan_on = 550;     // turn on above this reading
int fan_off = 520;    // turn off below this reading
int fan_state = 0;    // 0 = off, 1 = on

void setup() {
  Serial.begin(9600);
  pinMode(fan, OUTPUT);
}

void loop() {
  int sensorVal = analogRead(sensor);

  if (fan_state == 0) {
    if (sensorVal > fan_on) {
      fan_state = 1;
    }
  } else {
    if (sensorVal < fan_off) {
      fan_state = 0;
    }
  }

  if (fan_state == 1) {
    digitalWrite(fan, HIGH);
  } else {
    digitalWrite(fan, LOW);
  }

  Serial.print(sensorVal);
  Serial.print("  Fan: ");
  Serial.println(fan_state);

  delay(200);
}
