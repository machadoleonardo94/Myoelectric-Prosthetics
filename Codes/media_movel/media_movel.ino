#define numSamples 125
#include <Servo.h>

Servo myservo;

void setup() {
  pinMode(A0, INPUT);
  myservo.attach(9);
  Serial.begin(19200);
}

  int posicao=0;
  long media=0;
  int k=0;
  int offset=0;
  int amostra[numSamples]={0};


void loop() {

  amostra[posicao]=analogRead(A0);
  for(k=0;k<numSamples;k++)
    media+=amostra[k];
  media=media/numSamples;

Serial.print(0);  // To freeze the lower limit
Serial.print(" ");
Serial.print(800);  // To freeze the upper limit
Serial.print(" ");
Serial.println(media);  // To send all three 'data' points to the plotter

  posicao++;
  if(posicao>numSamples)
    posicao=0;
  myservo.write(media/3);
  media=0;
}
