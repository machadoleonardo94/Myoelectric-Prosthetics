const int stepPin = 4; 
const int dirPin = 3; 
const int timer=4000;
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,HIGH);
}
void loop() {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(timer);
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(timer);
}
