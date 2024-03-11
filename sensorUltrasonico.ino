class UltrasonicSensor {
private:
  int triggerPin;
  int echoPin;

public:
  UltrasonicSensor(int triggerPin, int echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
  }

  void setup() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(triggerPin, LOW);
  }

  float readDistance() {
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    unsigned long duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.0343 / 2;  // Calcula la distancia en centímetros
    return distance;
  }
};

class LEDController {
private:
  int ledPins[3];

public:
  LEDController(int pin1, int pin2, int pin3) {
    ledPins[0] = pin1;
    ledPins[1] = pin2;
    ledPins[2] = pin3;
  }

  void setup() {
    for (int i = 0; i < 3; i++) {
      pinMode(ledPins[i], OUTPUT);
    }
  }

  void setLED(int index, bool state) {
    digitalWrite(ledPins[index], state ? HIGH : LOW);
  }
};

const int triggerPin = 15;
const int echoPin = 16;

const int ledPins[3] = {32, 33, 23};  // Pines de los LEDs

UltrasonicSensor ultrasonicSensor(triggerPin, echoPin);
LEDController ledController(ledPins[0], ledPins[1], ledPins[2]);

void setup() {
  Serial.begin(115200);
  ultrasonicSensor.setup();
  ledController.setup();
}

void measureDistance(float cm) {
  ledController.setLED(0, false);
  ledController.setLED(1, false);
  ledController.setLED(2, false);

  if (cm >= 0 && cm < 50) {
    ledController.setLED(0, true);
    delay(1000);
    ledController.setLED(0, false);
  } else if (cm >= 50 && cm <= 150) {
    ledController.setLED(1, true);
    delay(1000);
    ledController.setLED(1, false);
  } else if (cm > 150 && cm <= 300) {
    ledController.setLED(1, true);
  } else if (cm > 300) {
    ledController.setLED(2, true);
  }
}

void loop() {
  float distance = ultrasonicSensor.readDistance();
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println("cm");
  measureDistance(distance);
  delay(1000);
}