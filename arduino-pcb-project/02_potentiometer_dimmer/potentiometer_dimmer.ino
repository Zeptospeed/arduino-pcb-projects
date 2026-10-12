int pot = A0;
int blue = 9;
int red = 10;

void setup() {
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(pot);

  int blueBrightness = map(potValue, 0, 1023, 255, 0);
  int redBrightness = map(potValue, 0, 1023, 0, 255);

  analogWrite(blue, blueBrightness);
  analogWrite(red, redBrightness);

  Serial.println(potValue);
  delay(10);
}
