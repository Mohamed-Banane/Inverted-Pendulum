// Include the AccelStepper Library
#include <Encoder.h>
// Define pin connections
#define IN1 9
#define IN2 8
#define ENA 10

double LONGUEUR_PENDULE = 500;
double Deplacement = 0;
// Broches de l'encodeur
const int pinEncodeurA = 2;
const int pinEncodeurB = 3;
int resolutionEncodeur = 1600;
float pos;
Encoder encodeur(pinEncodeurA, pinEncodeurB);

// Constantes du PID
float correction = 0;
float positionCible = 0;

void setup() {
  Serial.begin(500000);
  // set the maximum speed, acceleration factor,
  // initial speed
  pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(ENA, OUTPUT);
}

void loop() {
  // Vérifier si des données sont disponibles sur le port série
  if (Serial.available() > 0) {
    Deplacement = Serial.parseInt();
  }
  // Change direction once the motor reaches target position
  if ( Deplacement > 0) {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    if (355> Deplacement > 190) {
     Deplacement = 190;
    }/*else if(Output > 355) {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      }*/
      analogWrite(ENA,  Deplacement+65);
  }
  
  if ( Deplacement < 0) {
    //Output = -Output;
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
     if (355 > abs( Deplacement) > 190) {
         Deplacement = 190;
  } 
  
    analogWrite(ENA, abs(Deplacement)+65);
  }
  int ticks = encodeur.read();
  pos = 360.0 * (float)ticks / resolutionEncodeur;

  //Serial.println(myStepper.currentPosition());
  Serial.println(pos);
}

