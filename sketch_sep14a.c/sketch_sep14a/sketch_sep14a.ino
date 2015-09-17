const int analogInPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.println(sensorValue/10);      
}
