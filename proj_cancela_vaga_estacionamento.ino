/*Maria Eduarda Fiori - 3044432
	Projeto cancela para estacionamento e detecção de vagas
    *	led vermelho aceso para cancela fechada
    *	sensor de distancia detecta o carro, cancela abre e led verde acende
    *	após a entrada do carro, cancela fecha e led vermelho acende
    *	led_vermelho_vaga para a vaga que está ocupada e led_verde_vaga para a que não está ocupada
    *	o carro se direciona para a vaga que não está ocupada
    *	após estacionar o sensor ldr detecta e acende o led_vermelho_vaga
*/

#include <Servo.h>; 	//biblioteca servomotor
Servo servoMotor; 	//declaracao servo

int ledVerde = 8; 	//declaracao led_verde cancela
int ledVermelho = 9; 	//declaracao led_vermelho cancela
int servo; 		// servomotor - cancela
int ledVagaVerde = 10; 	// led_verde_vaga
int ledVagaVermelho = 11; 	// led_vermelho_vaga

//declaracao sensor de presenca
#define echoPin 13
#define trigPin 6
#define ldr A0 	// declaracao ldr 

unsigned int duracao=0; 	//variavel para duracao de tempo em que a cancela fecha
unsigned int distancia=0;	// variavel de distancia para o sensor

void setup()
{ 
  //definicao dos pinos dos leds
  pinMode(ledVerde,OUTPUT);
  pinMode(ledVermelho,OUTPUT);
  pinMode(ledVagaVerde,OUTPUT);
  pinMode(ledVagaVermelho,OUTPUT);
  
  //definicao pinos servomotor 
  servoMotor.attach(0);
  servoMotor.write(0);
  
  //definicao pinos sensor de presenca
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  
  digitalWrite(ledVermelho, HIGH); 	//ledVermelho cancela comeca aceso
  
  //definicao pinos ldr
  pinMode(ldr, INPUT);
  pinMode(2, INPUT);
  pinMode(3,OUTPUT);
}

void loop()
{
  digitalWrite(3, LOW);
  int read = digitalRead(2);
  if(read == HIGH)
  {
    digitalWrite(3,HIGH);
  }
  
  int valor = analogRead(ldr);		//criacao da variavel de luz para o ldr
  int luz = map(valor, 0, 1023, 100, 0);
  digitalWrite(ledVagaVerde, HIGH); 	// led_verde_vaga aceso
  
  if(luz<=50){  	//se o sensor conseguir captar a luz maior ou igual 50%, a vaga está disponível para estacionar
  	digitalWrite(ledVagaVerde, HIGH); 	//vaga disponivel = led_verde_vaga aceso
    digitalWrite(ledVagaVermelho, LOW);		
  }	else{	// caso o sensor não conseguir captar a condição anterior, a vaga estara indisponivel
  	digitalWrite(ledVagaVerde, LOW);	//led_verde_vaga apaga
    digitalWrite(ledVagaVermelho, HIGH);	//led_vermelho_vaga acende
  }
  
  
  //ativar sensor de distancia
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);	
  digitalWrite(trigPin, LOW);
  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao*0.017;
  
  if(distancia<=65){	//se a distancia for menor ou igual a 65cm, a cancela abre e o led_vermelho apaga e o led_verde acend
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
    servoMotor.write(90);
    digitalWrite(ledVerde, HIGH);
  }else{ 	//caso não, a cancela fecha e o led_vermelho acende
    delay(6000);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    servoMotor.write(0);
  }
  
}