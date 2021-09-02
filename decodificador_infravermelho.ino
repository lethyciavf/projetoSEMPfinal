#include <IRremote.h>

int RECV_PIN = 11;
const int IRQ = 8; //saida que coloca IRQ em zero para acionar
const int A = 9; //saida A para comando pino 9
const int B = 10; //saida B para comando pino 10

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(IRQ,OUTPUT);
  irrecv.enableIRIn(); //Inicia o receptor
}

void loop() {

  digitalWrite(IRQ,HIGH); //Seta para 1 pois ja houve um pulso na IRQ
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    
    if (results.value==0xFF817E){
      //ABRE CORTINA
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(IRQ,LOW);
      }

    else if (results.value==0xFFC13E){
      //FECHA CORTINA
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(IRQ,LOW);
      }

    else if (results.value==0xFF837C){
      //ACENDE DISPLAY
      digitalWrite(A,LOW);
      digitalWrite(B,HIGH);
      digitalWrite(IRQ,LOW);
      }
       
    else{
      //NADA ACONTECE
      digitalWrite(A,HIGH);
      digitalWrite(B,HIGH); 
      digitalWrite(IRQ,HIGH);
      }
    delay(250);  
    irrecv.resume(); //Recebe o proximo valor
  } 
  delay(1000);
}

