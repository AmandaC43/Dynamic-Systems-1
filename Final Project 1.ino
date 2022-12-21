int interruptPin = 2;
int ledPin = 3;
int ldrPin = A6;
int triggerPin = 9;
int echoPin = 6;
int sensor = A2;

volatile byte state = 0;
volatile byte gesture = 0;

float sensorValue = 0.0;
float speedOfSound = 343.0;
float distanceCm = 0.0;
long int timeOfFlight = 0.0;

int dTargetArray[2];

void brightnessLED (int dutyCycle);
int measurement ();

void setup() {

  Serial.begin (9600);
  pinMode (interruptPin, INPUT);
  pinMode (ledPin, OUTPUT);
  pinMode (ldrPin, INPUT);
  pinMode (triggerPin, OUTPUT);
  pinMode (echoPin, INPUT);

  attachInterrupt (digitalPinToInterrupt (interruptPin), switchInt, RISING);
  
}

void loop() {

  dTargetArray[0] = measurement ();
  delay (30);
  dTargetArray[1] = measurement ();

 if (dTargetArray[1] < 30 and dTargetArray[0]-15 > dTargetArray[1]){

      gesture =! gesture;

     }

    

   if (gesture == 1 and state == 1){
  
      int sensorValue = analogRead (sensor);
      sensorValue = map (sensorValue, 0, 1023, 0, 255);


      brightnessLED (sensorValue);
      
     }

    else if (gesture == 1 and state == 0) {
      
      int LDRValue = analogRead (ldrPin);
      LDRValue = map (LDRValue, 700, 0, 0, 255);


      brightnessLED (LDRValue);

      
      }
   

  else {
    
    brightnessLED (0);
    
    }
   
}


void switchInt (){

  state =! state;

  int sensorValue = analogRead (A2);

  if (state == 1) {
    
    Serial.println ("Manual Control");
    Serial.println ("\n");
    
    }

   else {
    
    Serial.println ("Automatic Control");
    Serial.println ("\n");
    
    }
  
}

void brightnessLED (int dutyCycle) {
  
  analogWrite (ledPin, dutyCycle);
  
}

int measurement (){

    digitalWrite (triggerPin, LOW);
    delayMicroseconds (5);

    digitalWrite (triggerPin, HIGH);
    delayMicroseconds (10);
    digitalWrite (triggerPin, LOW);

    timeOfFlight = pulseIn(echoPin, HIGH);

    distanceCm = speedOfSound*timeOfFlight/(2*10000);

    return distanceCm;

}