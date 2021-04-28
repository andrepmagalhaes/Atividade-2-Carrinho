#include <Ultrasonic.h>

int trigPin = 9;      
int echoPin = 10;
Ultrasonic ultrasonic(trigPin, echoPin);
 

int fwdRight = 4;       //0 to activate
int revRight = 5;      
int revLeft = 6;      
int fwdLeft = 7;
int distances[5]; //0 - front; 1 - shortleft; 2 - longleft; 3 -shortright; 4 - longright;
int distancesAux[5];
int distancesSum;
//int distShortLeft = 0;
//int distLongLeft = 0;
//int distShortRight = 0;
//int distLongRight = 0;
//int distFront = 0;
bool sprint = false;

void setup() {
  
  Serial.begin(9600);
  pinMode(revRight, OUTPUT);      // set Motor pins as output
  pinMode(fwdRight, OUTPUT);
  pinMode(fwdLeft, OUTPUT);
  pinMode(revLeft, OUTPUT);
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);

  for(int i = 0; i<5 ; i++)
  {
    distances[i] = 0;
  }
  
  stopCar();
  delay(5000);
  
}

void loop() {
  if(sprint==false)
  {
    forward();
    delay(3500);
    stopCar();
    sprint=true;
  }
  else
  {
  distancesSum = 0;
  probe();
  for(int i = 0 ; i < 5 ; i++)
  {
    distances[i] = (distances[i] >= 160) ? 0 : distances[i];
    distancesSum = distancesSum + distances[i];
  }
  
  if(distancesSum <= 125)
  {
    backwards();
    delay(300);
    stopCar();
    delay(300);
  }
  else
  {
    for(int i = 0; i < 5 ; i++)
    {
      distancesAux[i] = distances[i];
    }
    
    qsort(distancesAux, 5, sizeof(int), cmpfunc);
    
    if(distancesAux[4] == distances[0])//forward
    {
      forward();
      delay(900);
      stopCar();
      delay(300);
    }else if(distancesAux[4] == distances[1])//shortLeft
    {
      turnLeft();
      delay(150);
      stopCar();
      delay(300);
      forward();
      delay(900);
      stopCar();
      delay(300);
    }
    else if(distancesAux[4] == distances[2]) //longLeft
    {
      turnLeft();
      delay(150);
      stopCar();
      delay(300);

      turnLeft();
      delay(150);
      stopCar();
      delay(300);
      
      forward();
      delay(900);
      stopCar();
      delay(300);
    }
    else if(distancesAux[4] == distances[3])
    {
      turnRight();
      delay(150);
      stopCar();
      delay(300);
      forward();
      delay(900);
      stopCar();
      delay(300);
    }
    else
    {
      turnRight();
      delay(150);
      stopCar();
      delay(300);

      turnRight();
      delay(150);
      stopCar();
      delay(300);
      
      forward();
      delay(900);
      stopCar();
      delay(300);
    }
  }
  }
  
  
}

void stopCar()
{
  digitalWrite(revRight, 1);
  digitalWrite(revLeft, 1);
  digitalWrite(fwdRight, 1);
  digitalWrite(fwdLeft, 1);
}
void turnRight()
{
  digitalWrite(fwdLeft, 0);
  digitalWrite(revRight, 0);
}
void turnLeft()
{
  digitalWrite(fwdRight, 0);
  digitalWrite(revLeft, 0);
}
void forward()
{
  digitalWrite(fwdRight, 0);
  digitalWrite(fwdLeft, 0);
}
void backwards()
{
  digitalWrite(revRight, 0);
  digitalWrite(revLeft, 0);
}
void probe()
{
  delay(1000);
  distances[0] = ultrasonic.read(CM);
  
  turnLeft();
  delay(150);
  stopCar();
  delay(1000);
  distances[1] = ultrasonic.read(CM);
  
  turnLeft();
  delay(150);
  stopCar();
  delay(1000);
  distances[2] = ultrasonic.read(CM);
  
  turnRight();
  delay(150);
  stopCar();
  delay(300);
  turnRight();
  delay(150);
  stopCar();
  delay(300);
  
  turnRight();
  delay(150);
  stopCar();
  delay(1000);
  distances[3] = ultrasonic.read(CM);

  turnRight();
  delay(150);
  stopCar();
  delay(1000);
  distances[4] = ultrasonic.read(CM);
  
  turnLeft();
  delay(150);
  stopCar();
  delay(300);
  turnLeft();
  delay(150);
  stopCar();
  delay(300);
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
