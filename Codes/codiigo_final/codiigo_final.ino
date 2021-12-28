#include <Arduino.h>
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define RPM 60
#define numSamples 100
#define MICROSTEPS 32
#define SENSIBILIDADE 5

BasicStepperDriver stepper(MOTOR_STEPS, 4, 5);  //DIR pino 4, STEP pino 5


void setup() {
  stepper.begin(RPM, MICROSTEPS);
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(57200);
}

  int indice=0; //indice do vetor de amostras
  int amostra[numSamples]={0};  //vetor de amostras
  long media=0; //meddia da amostragem
  int posicao=0;//posicao do arco
  int delta=0;  //variacao na posição
  int k=0;      //contador genérico
  int offset=0; //correção de leitura, implementar depois
  int debug=1;


void loop() {

  //amostragem
  amostra[indice]=analogRead(A0);
  for(k=0;k<numSamples;k++)
    media+=amostra[k];
  media=media/numSamples;
  indice++;
  if(indice>numSamples){
    indice=0;
  }

  //mapeia posição para ser a intensidade do movimento
  media = map(media,20,800,0,100);   //anota nova
  delta = media-posicao;

  if (debug){  
    Serial.print(0);
    Serial.print(" ");
    Serial.print(100);
    Serial.print(" ");
    Serial.print(media);
    Serial.print(" ");
    Serial.println(posicao);
  }
  

  if ((delta<-SENSIBILIDADE) && (posicao>2) && (media<30)){      //se deslocamento negativo e dentro dos limites
    stepper.move(-60);
    posicao--;
  }
  if ((delta>SENSIBILIDADE) && (posicao<100)){      //se deslocamento positivo e dentro dos limites
    stepper.move(60);
    posicao++;
  }
  
  media=0;
}
