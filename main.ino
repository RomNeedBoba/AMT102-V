// Pin Connections:

// Power:

// Connect the encoder's +5V pin to the Arduino's 5V pin.
// Connect the encoder's GND pin to the Arduino's GND pin.
// Signal Pins:

// Connect the encoder's A phase output pin to digital pin 2 on the Arduino.
// Connect the encoder's B phase output pin to digital pin 3 on the Arduino.

const int encoderAPin = 2;
const int encoderBPin = 3;

volatile long encoderValue = 0;
volatile bool lastA = false;

void setup() {
  pinMode(encoderAPin, INPUT_PULLUP);
  pinMode(encoderBPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderAPin), pulseAPin, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderBPin), pulseBPin, RISING);

  Serial.begin(9600);
}

void loop() {
  Serial.println(encoderValue);
  delay(100);
}

void pulseAPin() {
  bool b = digitalRead(encoderBPin);
  if (!lastA && b) {
    encoderValue++;
  } else if (lastA && !b) {
    encoderValue--;
  }
  lastA = !lastA;
}

void pulseBPin() {
  bool a = digitalRead(encoderAPin);
  if (!a && lastA) {
    encoderValue++;
  } else if (a && !lastA) {
    encoderValue--;
  }
}
