/* Line FolloWer with 7 pair of ir led transmitter and receiver
   µC is an Arduino Pro Mini
   PD Settings: KP 2.8 
                KD 14.0 
                SPEED_BASIC 70 
*/

// Pins
#define SENSOR_R3 20 // = A6
#define SENSOR_R2 19 // = A5
#define SENSOR_R1 18 // = A4
#define SENSOR_M 17 // = A3
#define SENSOR_L1 16 // = A2
#define SENSOR_L2 15 // = A1
#define SENSOR_L3 14 // = A0
#define BUTTON 12
#define LED 13
#define MOTOR_R_PWM 11 // rechtes Rad
#define MOTOR_L_PWM 10 // linkes Rad
#define MOTOR_R_A 8 // rechtes Rad
#define MOTOR_R_B 9
#define MOTOR_L_A 7 // linkes Rad
#define MOTOR_L_B 6


// PD Parameter
#define W 45  // Sensoren sind auf einer Breite von 90 mm verteilt -> 45 mm sind die Mitte und somit der Führungswert
#define KP 2.8 // 2.8
#define KD 14.0 // 14.0
#define SPEED_BASIC 70 // 70
#define SPEED_MAX 255 // positiver Wert ist vorwärts
#define SPEED_MIN -255 // negativer Wert ist rückwärts
#define SENSOR_VALUE_MAX 1000

long value_r3, value_r2, value_r1, value_m, value_l1, value_l2, value_l3;
long value_r3_white, value_r2_white, value_r1_white, value_m_white, value_l1_white, value_l2_white, value_l3_white;
long value_r3_black = SENSOR_VALUE_MAX; // damit Minimalwert mit findMin-Funktion ermittelt werden kann, muss vorest maximalen Wert zugewiesen werden
long value_r2_black = SENSOR_VALUE_MAX;
long value_r1_black = SENSOR_VALUE_MAX;
long value_m_black = SENSOR_VALUE_MAX;
long value_l1_black = SENSOR_VALUE_MAX;
long value_l2_black = SENSOR_VALUE_MAX;
long value_l3_black = SENSOR_VALUE_MAX;



void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_R3, INPUT);
  pinMode(SENSOR_R2, INPUT);
  pinMode(SENSOR_R1, INPUT);
  pinMode(SENSOR_M, INPUT);
  pinMode(SENSOR_L1, INPUT);
  pinMode(SENSOR_L2, INPUT);
  pinMode(SENSOR_L3, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(MOTOR_R_PWM, OUTPUT);
  pinMode(MOTOR_R_A, OUTPUT);
  pinMode(MOTOR_R_B, OUTPUT);
  pinMode(MOTOR_L_PWM, OUTPUT);
  pinMode(MOTOR_L_A, OUTPUT);
  pinMode(MOTOR_L_B, OUTPUT);

  digitalWrite(LED, HIGH);
  while (digitalRead(BUTTON) == HIGH) {  // zu Beginn die Sensoren kalibrienen indem der Line Follower über den dunkelsten und hellsten Bereich geschoben wird
    value_r3_black = findMin(SENSOR_R3, value_r3_black);  // black -> min Wert (0)
    value_r3_white = findMax(SENSOR_R3, value_r3_white);  // white -> max Wert (1023)
    value_r2_black = findMin(SENSOR_R2, value_r2_black);
    value_r2_white = findMax(SENSOR_R2, value_r2_white);
    value_r1_black = findMin(SENSOR_R1, value_r1_black);
    value_r1_white = findMax(SENSOR_R1, value_r1_white);
    value_m_black = findMin(SENSOR_M, value_m_black);
    value_m_white = findMax(SENSOR_M, value_m_white);
    value_l1_black = findMin(SENSOR_L1, value_l1_black);
    value_l1_white = findMax(SENSOR_L1, value_l1_white);
    value_l2_black = findMin(SENSOR_L2, value_l2_black);
    value_l2_white = findMax(SENSOR_L2, value_l2_white);
    value_l3_black = findMin(SENSOR_L3, value_l3_black);
    value_l3_white = findMax(SENSOR_L3, value_l3_white);
  };
  digitalWrite(LED, LOW);
}

void loop() {

  // Sensoren auslesen und Werte normieren, da unterschiedliche Werte bei gleicher helligkeit des Messobjektes
  value_r3 = scaleValue(SENSOR_R3, value_r3_black, value_r3_white, SENSOR_VALUE_MAX);
  value_r2 = scaleValue(SENSOR_R2, value_r2_black, value_r2_white, SENSOR_VALUE_MAX);
  value_r1 = scaleValue(SENSOR_R1, value_r1_black, value_r1_white, SENSOR_VALUE_MAX);
  value_m = scaleValue(SENSOR_M, value_m_black, value_m_white, SENSOR_VALUE_MAX);
  value_l3 = scaleValue(SENSOR_L3, value_l3_black, value_l3_white, SENSOR_VALUE_MAX);
  value_l2 = scaleValue(SENSOR_L2, value_l2_black, value_l2_white, SENSOR_VALUE_MAX);
  value_l1 = scaleValue(SENSOR_L1, value_l1_black, value_l1_white, SENSOR_VALUE_MAX);

  // mit gewichtetem Durchschnitt die Position des Line Followers über dem Streifen ermitteln
  float a = value_r3 * 0.0 + value_r2 * 15.0 + value_r1 * 30.0 + value_m * 45.0 + value_l1 * 60.0 + value_l2 * 75.0 + value_l3 * 90.0;
  float b = value_r3 + value_r2 + value_r1 + value_m + value_l1 + value_l2 + value_l3;
  float x =  a / b;

  // Stellwert berechnen
  int y = calulateOutput(W, x, KP, KD);

  // PWM-Werte für die Motoren ermitteln
  int speed_right = SPEED_BASIC + y;   // standard Geschwindigkeit um Stellwert verändern
  int speed_left = SPEED_BASIC - y;

  if (speed_right < SPEED_MIN)speed_right = SPEED_MIN;
  if (speed_right > SPEED_MAX)speed_right = SPEED_MAX;
  if (speed_left < SPEED_MIN)speed_left = SPEED_MIN;
  if (speed_left > SPEED_MAX)speed_left = SPEED_MAX;

  if (speed_right >= 0) {           // vorwärts -> Richtung steckt in Vorzeichen
    digitalWrite(MOTOR_R_A, HIGH);  
    digitalWrite(MOTOR_R_B, LOW);
  }
  else {                            // rückwärts
    digitalWrite(MOTOR_R_A, LOW);
    digitalWrite(MOTOR_R_B, HIGH);
  }

  if (speed_left >= 0) {           // vorwärts
    digitalWrite(MOTOR_L_A, HIGH);
    digitalWrite(MOTOR_L_B, LOW);
  }
  else {                            // rückwärts
    digitalWrite(MOTOR_L_A, LOW);
    digitalWrite(MOTOR_L_B, HIGH);
  }
  int pwm_right = abs(speed_right); // PWM-Wert muss positiv sein -> Betrag bilden
  int pwm_left = abs(speed_left);


  // fahren
  analogWrite(MOTOR_R_PWM, pwm_right);
  analogWrite(MOTOR_L_PWM, pwm_left);

}

int findMax(int sensor, int value_max) {          
  int value = analogRead(sensor);
  if (value > value_max)value_max = value;
  return value_max;
}

int findMin(int sensor, int value_min) {
  int value = analogRead(sensor);
  if (value < value_min)value_min = value;
  return value_min;
}

int scaleValue(int sensor, int value_black, int value_white, int sensor_value_max) {            // Sensorwerte einlesen und normieren -> normieren weil Sensoren bei selber Helligkeit nicht den gleichen Wert ausgeben
  int value = map(analogRead(sensor), value_black, value_white, sensor_value_max, 0);
  if (value < 0)value = 0;
  else if (value > sensor_value_max)value = sensor_value_max;
  return value;
}

int calulateOutput(float w, float x, float kp, float kd) {            // Stellwert berechnen
  static float e_old = 0;
  float e = w - x;
  int y = kp * e + kd * (e - e_old) + 0.5; // von float zu int umwandeln mit +0.5 wird richtig gerundet, da Nachkommastellen bei Zuweisung in int-Variable abgeschnitten werden
  e_old = e;
  return y;  
}
