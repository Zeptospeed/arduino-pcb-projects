#include <LiquidCrystal.h>

// Arduino UNO parking assist: HC-SR04, warning LEDs, buzzer, LCD1602.
const int trigPin = 2;
const int echoPin = 8;
const int greenLED = 9;
const int yellowLED = 10;
const int redLED = 11;
const int buzzerPin = 6;

LiquidCrystal lcd(12, 13, 3, 4, 5, 7);

// Five-attempt sampling; preserve state between loop() calls.
double readings[5];
int sampleCount = 0;
int validCount = 0;
unsigned long prevSensorMillis = 0;
double filteredDistance = -1;

// Buzzer state for millis()-based on/off timing.
unsigned long prevBuzzerMillis = 0;
bool buzzerOn = false;

// 0 UNKNOWN, 1 SAFE, 2 CAUTION, 3 DANGER, 4 STOP.
int currentStatus = 0;
int previousStatus = -1;

double readDistance();

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  double distance = readDistance();
  unsigned long currentMillis = millis();

  if (distance == -1) {
    currentStatus = 0;
  } else if (distance > 100) {
    currentStatus = 1;
  } else if (distance >= 50) {
    currentStatus = 2;
  } else if (distance >= 20) {
    currentStatus = 3;
  } else {
    currentStatus = 4;
  }

  // Restart the beep cycle whenever the warning zone changes.
  if (currentStatus != previousStatus) {
    noTone(buzzerPin);
    buzzerOn = false;
    prevBuzzerMillis = currentMillis;
    previousStatus = currentStatus;
  }

  if (currentStatus == 0) {
    lcd.setCursor(0, 0);
    lcd.print("NO SIGNAL       ");
    lcd.setCursor(0, 1);
    lcd.print("STATUS: UNKNOWN ");

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("DIST: ");
    lcd.print(distance, 1);
    // Pad within 16 LCD columns (the HC-SR04 typically reports <= 400 cm).
    lcd.print(" cm");
    int digits = (distance >= 100) ? 3 : ((distance >= 10) ? 2 : 1);
    int used = 6 + digits + 2 + 3; // "DIST: " + decimal value + " cm"
    for (int i = used; i < 16; i++) lcd.print(' ');

    if (currentStatus == 1) {
      lcd.setCursor(0, 1);
      lcd.print("STATUS: SAFE    ");
      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
    } else if (currentStatus == 2) {
      lcd.setCursor(0, 1);
      lcd.print("STATUS: CAUTION ");
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, LOW);
    } else if (currentStatus == 3) {
      lcd.setCursor(0, 1);
      lcd.print("STATUS: DANGER  ");
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("STATUS: STOP    ");
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
    }
  }

  // Buzzer control continues between distance samples.
  if (currentStatus == 0 || currentStatus == 1) {
    noTone(buzzerPin);
    buzzerOn = false;
  } else if (currentStatus == 4) {
    if (!buzzerOn) tone(buzzerPin, 500);
    buzzerOn = true;
  } else {
    unsigned long onTime = (currentStatus == 2) ? 300 : 150;
    unsigned long offTime = (currentStatus == 2) ? 700 : 150;

    if (buzzerOn) {
      if (currentMillis - prevBuzzerMillis >= onTime) {
        noTone(buzzerPin);
        buzzerOn = false;
        prevBuzzerMillis = currentMillis;
      }
    } else if (currentMillis - prevBuzzerMillis >= offTime) {
      tone(buzzerPin, 500);
      buzzerOn = true;
      prevBuzzerMillis = currentMillis;
    }
  }
}

double readDistance() {
  unsigned long now = millis();

  // One attempt per interval, instead of five in a blocking delay loop.
  if (now - prevSensorMillis >= 60) {
    prevSensorMillis = now;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // pulseIn still blocks for up to 30 ms on a missing echo.
    unsigned long duration = pulseIn(echoPin, HIGH, 30000);
    if (duration > 0) {
      readings[validCount] = (duration * 0.0343) / 2.0;
      validCount++;
    }
    sampleCount++;
  }

  if (sampleCount == 5) {
    if (validCount == 0) {
      filteredDistance = -1;
    } else {
      // Selection sort the valid measurements to reject isolated outliers.
      for (int i = 0; i < validCount - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < validCount; j++) {
          if (readings[j] < readings[minIndex]) minIndex = j;
        }
        double temp = readings[i];
        readings[i] = readings[minIndex];
        readings[minIndex] = temp;
      }
      filteredDistance = readings[validCount / 2];
    }
    sampleCount = 0;
    validCount = 0;
  }

  return filteredDistance;
}
