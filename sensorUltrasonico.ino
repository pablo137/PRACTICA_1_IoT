#define trigger 15
#define echo 16
float cm = 0;

int ports[3] = { 32, 33, 26 };  //Puertos del MCU

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ports[i], OUTPUT);
  }
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);  //Inicializamos el pin con 0
  Serial.begin(115200);
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);  //Se devolvera el tiempo entre el envio y la recepcion
}

void measureDistance(float cm) {
  if (cm >= 0 && cm < 50) {
    digitalWrite(ports[1], LOW);
    digitalWrite(ports[2], LOW);
    digitalWrite(ports[0], HIGH);
    delay(1000);
    digitalWrite(ports[0], LOW);
    delay(1000);
  } else if (cm > 50 & cm <= 150) {

    digitalWrite(ports[0], LOW);
    digitalWrite(ports[2], LOW);
    digitalWrite(ports[1], HIGH);
    delay(1000);
    digitalWrite(ports[1], LOW);
    delay(1000);
  }

  else if (cm > 150 && cm <= 300) {
    digitalWrite(ports[0], LOW);
    digitalWrite(ports[2], LOW);
    digitalWrite(ports[1], HIGH);
    delay(1000);
  }

  else if (cm > 300) {
    digitalWrite(ports[0], LOW);
    digitalWrite(ports[1], LOW);
    digitalWrite(ports[2], HIGH);
    delay(1000);
  }
}

void loop() {
  cm = 0.01723 * readUltrasonicDistance(trigger, echo);  //se calculara la distancia multiplicando la velocidad en la que el sonido recorre un centimetro por el tiempo de rebote obtenido.
  Serial.print("Distancia: ");
  measureDistance(cm);
  Serial.print(cm);
  Serial.println("cm");
}