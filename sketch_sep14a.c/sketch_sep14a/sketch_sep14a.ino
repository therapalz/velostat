const int analogInPin = A0;
const int vibePin1 = 8;
int sensorValue = 0;
int flexInitial;
int flexChange;
int purrCount = 0;
int purrCountGoal = 35;
int purrThresh = 10;

int steadyReading;
int steadyCount = 0;
int steadyThresh = 3;
int steadyCountGoal = 100;
boolean isSteady = false;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  flexInitial = analogRead(analogInPin);
  Serial.print("INITIAL FLEX VALUE: ");
  Serial.println(flexInitial);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);
  if (isSteady == false) {
    isSteady = sensorIsSteady(sensorValue);
    return;
  }
  flexChange = abs(flexInitial - sensorValue);
  
  vibrate(flexChange);
  analogWrite(9, flexChange);
  delay(100);
}

void vibrate(int change) {
  if (change > purrThresh) {
    purrCount++;
    Serial.print("purr count = ");
    Serial.println(purrCount);
  }
  
  if (purrCount > purrCountGoal) {
    purrCount = 0;
    resetSteady();
    for (int i = 0; i < random(3, 6); i++) {
      pulse();
    }
  }
}

void pulse() {
  delay(1000);
  digitalWrite(vibePin1, HIGH);
  delay(3000);
  digitalWrite(vibePin1, LOW);
}

void resetSteady() {
  steadyCount = 0;
  isSteady = false;
}

boolean sensorIsSteady(int sensor) {
  int diff = abs(sensor - flexInitial);
  if (diff > 10) {
    Serial.print("UPDATED FLEX INITIAL: ");
    Serial.println(flexInitial);
    flexInitial = sensor;
  }
  else if (diff < steadyThresh) {
    steadyCount++;
  }
  if (steadyCount >= steadyCountGoal) {
    Serial.println("SENSOR IS STEADY");
    return true;
  } else {
    return false;
  }
}
