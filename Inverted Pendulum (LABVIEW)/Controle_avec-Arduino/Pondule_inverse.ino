#include <PID_v1.h>
#include <Encoder.h>
#define IN1 9
#define IN2 8
#define ENA 10
double LONGUEUR_PENDULE = 500;
double Deplacement = 0;
double pos=0;
double time1 =1;
// Broches de l'encodeur
const int pinEncodeurA = 2;
const int pinEncodeurB = 3;
int resolutionEncodeur = 1601;
 int ticks ;
Encoder encodeur(pinEncodeurA, pinEncodeurB);
int direction1; 
unsigned long lasttime = 0;
  //double Output = 0, Setpoint = 178.5165;
   //double Output = 0, Setpoint = 177.5;
   double Output = 0, Setpoint = 0;
double errsum, lasterr;
double kp1, ki1, kd1;



void setup() {
  Serial.begin(500000);
  /*pinMode(encpin1a, INPUT_PULLUP);
  pinMode(encpin1b, INPUT_PULLUP);
  pinMode(encpin2a, INPUT_PULLUP);
  pinMode(encpin2b, INPUT_PULLUP);
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder1, CHANGE);*/
   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(ENA, OUTPUT);
   //SetTunings0(37, 0.00002, 32); // Initial tuning 
  //SetTunings0(15.87, 27.35, 1.13); // Initial tuning
     //SetTunings0(39, 0.00007, 35);
   //SetTunings0(39, 0.00004, 32);
   //SetTunings0(40, 0.00004, 32);
   //SetTunings0(40, 0.000045, 32);
   //SetTunings0(43, 0.00005, 32);
    //SetTunings0(45, 0.00006, 32);
   // SetTunings0(40, 0.00006, 32);
    //SetTunings0(45, 0.00007, 32);
     //SetTunings0(45, 0.00008, 32);
     //SetTunings0(45, 0.00008, 0);
    // SetTunings0(45, 0.0001,28); REAL ONE    DERIVEE
      //SetTunings0(45, 0.0001,26);
       //SetTunings0(45, 0.0001,27.511);
      // SetTunings0(45, 0.0001,28); REAL ONE ARBI
       //SetTunings0(20, 0.0001,28); mauvais
      // SetTunings0(20, 0.0001,28);  mauvais
        SetTunings0(45, 0.0001,28);
      
       
       
}

void loop() {
   
   Compute();
    ticks = encodeur.read();
    pos = 360.0 * (float)ticks / resolutionEncodeur;

  //Serial.println(myStepper.currentPosition());
     Serial.println(pos);
   //Serial.print("\t");
   //Serial.println(Output);
   //Serial.println(ticks);
   if (Output > 0) {
    direction1 = 1;
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    if (355>Output > 190) {
      Output = 190;
    }/*else if(Output > 355) {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      }*/
      analogWrite(ENA, Output+65);
  }
  
  if (Output < 0) {
    direction1 = -1;
    //Output = -Output;
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
     if (355>abs(Output) > 190) {
        Output = 190;
  } 
  
    analogWrite(ENA, abs(Output)+65);
  }
  
  /*if (355>Output > 235) {
    Output = 235;
  }else if(Output > 355) {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      }*/

 
  
  
  }
  
  
 

  void  Compute() {
  double error = Setpoint - pos;
  errsum += error*time1 ;
  double dErr = (error - lasterr)/time1 ;

  Output = kp1 * error + ki1 * errsum + kd1 * dErr ;
  
/*Serial.print(kp1 * error);
  Serial.print("\t");
  Serial.print(kd1 * dErr);
  Serial.print("\t");
  Serial.println(ki1 * errsum);*/

  lasterr = error;
}

void SetTunings0(double Kp, double Ki, double Kd) {
  kp1 = Kp;
  ki1 = Ki;
  kd1 = Kd;
}
