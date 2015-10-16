const int analogInPin = A0;
const int vibePin1 = 8;
int sensorValue = 0;
int flexInitial;
int flexChange;
int purrCount = 0;
int purrThresh = 100;

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
  flexChange = abs(flexInitial - sensorValue);
  vibrate(flexChange);
  analogWrite(9, flexChange);
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);
  delay(100);
}

void vibrate(int change) {
  if (change > purrThresh) {
    purrCount++;
    Serial.print("purr count = ");
    Serial.println(purrCount);
  }
  
  if (purrCount > 100) {
    purrCount = 0;
    digitalWrite(vibePin1, HIGH);
    delay(2000);
    digitalWrite(vibePin1, LOW);
  }
}
