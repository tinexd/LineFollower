#define pin_sensor_r_3 20
#define pin_sensor_r_2 19
#define pin_sensor_r_1 18
#define pin_sensor_mitte 17
#define pin_sensor_l_1 16
#define pin_sensor_l_2 15
#define pin_sensor_l_3 14
#define pin_taster_1 12
#define pin_led 13
int sensor_r_3_wert, sensor_r_2_wert, sensor_r_1_wert, sensor_mitte_wert, sensor_l_1_wert, sensor_l_2_wert, sensor_l_3_wert;
int sensor_r_3_wert_weiss, sensor_r_2_wert_weiss, sensor_r_1_wert_weiss, sensor_mitte_wert_weiss, sensor_l_1_wert_weiss, sensor_l_2_wert_weiss, sensor_l_3_wert_weiss;
int sensor_r_3_wert_schwarz = 10000;
int sensor_r_2_wert_schwarz = 10000;
int sensor_r_1_wert_schwarz = 10000;
int sensor_mitte_wert_schwarz = 10000;
int sensor_l_1_wert_schwarz = 10000;
int sensor_l_2_wert_schwarz = 10000;
int sensor_l_3_wert_schwarz = 10000;



void setup() {
  Serial.begin(9600);
  Serial.println("test");
  pinMode(pin_sensor_r_3, INPUT);
  pinMode(pin_sensor_r_2, INPUT);
  pinMode(pin_sensor_r_1, INPUT);
  pinMode(pin_sensor_mitte, INPUT);
  pinMode(pin_sensor_l_1, INPUT);
  pinMode(pin_sensor_l_2, INPUT);
  pinMode(pin_sensor_l_3, INPUT);
  pinMode(pin_taster_1, INPUT_PULLUP);
  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, HIGH);
  while (digitalRead(pin_taster_1) == HIGH) {
    sensor_r_3_wert = analogRead(pin_sensor_r_3);
    sensor_r_2_wert = analogRead(pin_sensor_r_2);
    sensor_r_1_wert = analogRead(pin_sensor_r_1);
    sensor_mitte_wert = analogRead(pin_sensor_mitte);
    sensor_l_1_wert  = analogRead(pin_sensor_l_1);
    sensor_l_2_wert  = analogRead(pin_sensor_l_2);
    sensor_l_3_wert = analogRead(pin_sensor_l_3);


    if (sensor_r_3_wert < sensor_r_3_wert_schwarz)sensor_r_3_wert_schwarz = sensor_r_3_wert;
    if (sensor_r_3_wert > sensor_r_3_wert_weiss)sensor_r_3_wert_weiss = sensor_r_3_wert;

    if (sensor_r_2_wert < sensor_r_2_wert_schwarz)sensor_r_2_wert_schwarz = sensor_r_2_wert;
    if (sensor_r_2_wert > sensor_r_2_wert_weiss)sensor_r_2_wert_weiss = sensor_r_2_wert;

    if (sensor_r_1_wert < sensor_r_1_wert_schwarz)sensor_r_1_wert_schwarz = sensor_r_1_wert;
    if (sensor_r_1_wert > sensor_r_1_wert_weiss)sensor_r_1_wert_weiss = sensor_r_1_wert;

    if (sensor_mitte_wert < sensor_mitte_wert_schwarz)sensor_mitte_wert_schwarz = sensor_mitte_wert;
    if (sensor_mitte_wert > sensor_mitte_wert_weiss)sensor_mitte_wert_weiss = sensor_mitte_wert;

    if (sensor_l_1_wert < sensor_l_1_wert_schwarz)sensor_l_1_wert_schwarz = sensor_l_1_wert;
    if (sensor_l_1_wert > sensor_l_1_wert_weiss)sensor_l_1_wert_weiss = sensor_l_1_wert;

    if (sensor_l_2_wert < sensor_l_2_wert_schwarz)sensor_l_2_wert_schwarz = sensor_l_2_wert;
    if (sensor_l_2_wert > sensor_l_2_wert_weiss)sensor_l_2_wert_weiss = sensor_l_2_wert;

    if (sensor_l_3_wert < sensor_l_3_wert_schwarz)sensor_l_3_wert_schwarz = sensor_l_3_wert;
    if (sensor_l_3_wert > sensor_l_3_wert_weiss)sensor_l_3_wert_weiss = sensor_l_3_wert;

  }
  digitalWrite(pin_led, LOW);
}

void loop() {
  sensor_r_3_wert = map(analogRead(pin_sensor_r_3), sensor_r_3_wert_schwarz, sensor_r_3_wert_weiss, 1000, 0);
  sensor_r_2_wert = map(analogRead(pin_sensor_r_2), sensor_r_2_wert_schwarz, sensor_r_2_wert_weiss, 1000, 0);
  sensor_r_1_wert = map(analogRead(pin_sensor_r_1), sensor_r_1_wert_schwarz, sensor_r_1_wert_weiss, 1000, 0);
  sensor_mitte_wert = map(analogRead(pin_sensor_mitte), sensor_mitte_wert_schwarz, sensor_mitte_wert_weiss, 1000, 0);
  sensor_l_1_wert = map(analogRead(pin_sensor_l_1), sensor_l_1_wert_schwarz, sensor_l_1_wert_weiss, 1000, 0);
  sensor_l_2_wert = map(analogRead(pin_sensor_l_2), sensor_l_2_wert_schwarz, sensor_l_2_wert_weiss, 1000, 0);
  sensor_l_3_wert = map(analogRead(pin_sensor_l_3), sensor_l_3_wert_schwarz, sensor_l_3_wert_weiss, 1000, 0);
  if (sensor_r_3_wert < 0)sensor_r_3_wert = 0;
  if (sensor_r_3_wert > 1000)sensor_r_3_wert = 1000;
  if (sensor_r_2_wert < 0)sensor_r_2_wert = 0;
  if (sensor_r_2_wert > 1000)sensor_r_2_wert = 1000;
  if (sensor_r_1_wert < 0)sensor_r_1_wert = 0;
  if (sensor_r_1_wert > 1000)sensor_r_1_wert = 1000;
  if (sensor_mitte_wert < 0)sensor_mitte_wert = 0;
  if (sensor_mitte_wert > 1000)sensor_mitte_wert = 1000;
  if (sensor_l_1_wert < 0)sensor_l_1_wert = 0;
  if (sensor_l_1_wert > 1000)sensor_l_1_wert = 1000;
  if (sensor_l_2_wert < 0)sensor_l_2_wert = 0;
  if (sensor_l_2_wert > 1000)sensor_l_2_wert = 1000;
  if (sensor_l_3_wert < 0)sensor_l_3_wert = 0;
  if (sensor_l_3_wert > 1000)sensor_l_3_wert = 1000;


  delay(1000);
  /*
    Serial.print("r3: ");
    Serial.println(analogRead(pin_sensor_r_3));
    Serial.print("r2: ");
    Serial.println(analogRead(pin_sensor_r_2));
    Serial.print("r1: ");
    Serial.println(analogRead(pin_sensor_r_1));
    Serial.print("mitte: ");
    Serial.println(analogRead(pin_sensor_mitte));
    Serial.print("l1: ");
    Serial.println(analogRead(pin_sensor_l_1));
    Serial.print("l2: ");
    Serial.println(analogRead(pin_sensor_l_2));
    Serial.print("l3: ");
    Serial.println(analogRead(pin_sensor_l_3));
    Serial.println("*************************");
  */
  Serial.print("r3: ");
  Serial.println(sensor_r_3_wert);
  Serial.print("r2: ");
  Serial.println(sensor_r_2_wert);
  Serial.print("r1: ");
  Serial.println(sensor_r_1_wert);
  Serial.print("mitte: ");
  Serial.println(sensor_mitte_wert);
  Serial.print("l1: ");
  Serial.println(sensor_l_1_wert);
  Serial.print("l2: ");
  Serial.println(sensor_l_2_wert);
  Serial.print("l3: ");
  Serial.println(sensor_l_3_wert);
  Serial.println("*************************");

}
