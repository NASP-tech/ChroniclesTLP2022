/*ALGOBACK YOUTUBE CHANNEL*/
/*CODIGO PARA CARRO QUE EVITA OBSTACULOS */
//PINES DEL SENSOR DE COLOR
const int s0 = 1;
const int s1 = 2;
const int s2 = 3;
const int s3 = 4;
const int out = 10;
int rojo = 0;
int verde = 0;
int azul = 0;

const int tipo = 0;


int acumulador_color_Rojo = 0;
int acumulador_color_Verde = 0;
int acumulador_color_Azul = 0;
// Motor A
int in1 = 9;  // Pin que controla el sentido de giro
int in2 = 8;  // Pin que controla el sentido de giro

// Motor B
int enB = 5;   // Pin habilita motor B - PWM
int enA = 12;  // Pin habilita motor A - PWM
int in3 = 7;   // Pin que controla el sentido de giro
int in4 = 6;   // Pin que controla el sentido de giro

#define trigPin1 45  //DERECHA
#define echoPin1 44  // DERECHA
#define trigPin2 43  // IZQUIERDA
#define echoPin2 42  //IZQUIERDA
#define trigPin3 49  //FRONT
#define echoPin3 48  // FRONT
#define trigPin4 47  // BACK
#define echoPin4 46  //BACK


bool booleano = true;
long duration, distance, RightSensor, BackSensor, FrontSensor, LeftSensor;  //DECLARACION DE SENSORES Y SUS POCISIONES

void setup() {
  // Configura todos los pines como salida
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  SonarSensor(trigPin1, echoPin1);
  RightSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  LeftSensor = distance;
  SonarSensor(trigPin3, echoPin3);
  FrontSensor = distance;
  SonarSensor(trigPin4, echoPin4);
  BackSensor = distance;
}

void loop() {

  SonarSensor(trigPin1, echoPin1);
  RightSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  LeftSensor = distance;
  SonarSensor(trigPin3, echoPin3);
  FrontSensor = distance;
  SonarSensor(trigPin4, echoPin4);
  BackSensor = distance;

  //  Serial.print(RightSensor);

  distance = medirdistance();

  if (FrontSensor >= 25 && FrontSensor <= 250) {
    Adelante();
    delay(100);
  }

  else if (FrontSensor < 25) {
    Frenar();
    delay(150);
    // Serial.print("  FRENAR   ");
    Reversa();
    delay(250);
    // Serial.print("  REVERSA   ");
    Frenar();
    delay(250);
    // Serial.print("  FRENAR2   ");
    RightSensor = mirarDerecha();  // SEGUN LAS MEDIDAS DEL LABERINTO, GENERAR UN RANGO PARA QUE GIRE
    delay(250);
    LeftSensor = mirarIzquierda();  // DARLE A 255 LOS PINES  enA Y enB CUANDO SEA LA BATERIA
    delay(250);
  }

  //Serial.print(RightSensor);
  if (RightSensor >= LeftSensor) {
    GirarDerecha();
    // Frenar();
  }

  else if (LeftSensor >= RightSensor) {
    GirarIzquierda();
    //  Frenar();
  }
}

void SonarSensor(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  //delay (100);
}

int mirarDerecha() {
  SonarSensor(trigPin1, echoPin1);
  RightSensor = distance;
  // Serial.print(distance);
  // Serial.print(RightSensor);
  return RightSensor;
}

int mirarIzquierda() {
  SonarSensor(trigPin2, echoPin2);
  LeftSensor = distance;
  delay(50);

  return LeftSensor;
}

int medirdistance() {
  delay(10);
  int ditanciaCM = 0;
  if (ditanciaCM <= 0 || ditanciaCM >= 250) {
    ditanciaCM = 250;
  }
  return ditanciaCM;
}

void Frenar() {
  // Serial.print(FrontSensor);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 127);
  analogWrite(enA, 127);
}

void Adelante() {
  //SonarSensor(trigPin3, echoPin3);
  //Serial.print(FrontSensor);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 127);
  analogWrite(enA, 127);
  // delay(3000); // Giramos los motores por 3 segundos
  //controlVelocidad();
}


void Reversa() {
  // Serial.print(FrontSensor);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 127);
  analogWrite(enA, 127);
}

void GirarDerecha() {
  // Serial.print(FrontSensor);
  Serial.print("Derecha");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 127);
  analogWrite(enA, 127);
}

void GirarIzquierda() {
  //Serial.print(FrontSensor);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 127);
  analogWrite(enA, 127);
}

void controlVelocidad() {
  for (int velocidad = 0; velocidad < 160; velocidad += 2) {
    delay(3);
  }
}

void color() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
//1 rojo 2 verde  3 azul

int colores(int tipo) {  // mandar a llamar el tipo de color
  color();

  if (rojo < azul && verde > azul && rojo < 35) {
    Serial.println("   Rojo");
    acumulador_color_Rojo = acumulador_color_Rojo + 1;
    Serial.println(acumulador_color_Rojo);
  }

  else if (azul < rojo && azul < verde && verde < rojo) {
    Serial.println("   Azul");
    acumulador_color_Azul = acumulador_color_Azul + 1;
    Serial.println(acumulador_color_Azul);
  }

  else if (rojo > verde && azul > verde) {
    Serial.println("   Verde");
    acumulador_color_Verde = acumulador_color_Verde + 1;
    Serial.println(acumulador_color_Verde);
  }

  else {
    Serial.println("  ");
  }

  delay(900);

  return acumulador_color_Rojo;  // retoirnar el color segun el que quieren contar, provicional queda rojo pero declarar una variable para acumular el seleccionado
}