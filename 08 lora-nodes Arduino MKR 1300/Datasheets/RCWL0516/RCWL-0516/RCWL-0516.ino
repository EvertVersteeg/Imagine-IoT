const byte ledPin = 6;
const byte interruptPin = 1;
volatile byte state = LOW;

void setup() {
  Serial.begin(11500);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop() {
  digitalWrite(ledPin, state);
  delay(500);
}

void blink() {
  state = HIGH;
  Serial.println("duh");
  state= LOW;
}
