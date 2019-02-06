#include<Servo.h>

volatile unsigned long timer[4];
volatile byte last_channel[6], tick = 0;
volatile int input[10]={1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};
volatile int delT;
volatile bool servoWrite = false,takeover = false;
long failsafe;

Servo motor, steer;

void setup()
{
  PCICR |= (1 << PCIE0);   
  PCMSK0 |= (1 << PCINT1); //9
  PCMSK0 |= (1 << PCINT2); //10
  PCMSK0 |= (1 << PCINT3); //11
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
//  Serial.begin(38400);
}


void serialprint()
{
  Serial.print(input[0]);Serial.print("||");
  Serial.print(input[1]);Serial.print("||");
  Serial.print(input[2]);Serial.print("||");
  Serial.print(input[3]);Serial.print("||");
  Serial.print(input[4]);Serial.print("||");
  Serial.print(input[5]);Serial.print("||");
  Serial.print(input[6]);Serial.print("||");
  Serial.print(input[7]);Serial.print("||");
  Serial.print(input[8]);Serial.print("||");
  Serial.print(input[9]);Serial.print("||");
  Serial.println();
}


void fucc()
{
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
}
  
void loop()
{
  long timer = micros();
  if(input[2] < 1000)
  {
    fucc();
    takeover = false;
    motor.writeMicroseconds(1500);
    steer.writeMicroseconds(1500);
  }
  else if(takeover && !(input[2]<1000) )
  {
    motor.writeMicroseconds(input[2]);
    steer.writeMicroseconds(input[0]);
  }

  if(servoWrite)
  {
    failsafe = millis();
    servoWrite = false;
    takeover = false;
  }
  if(millis() - failsafe > 1000)
  {
    takeover = true;
    motor.attach(3);
    steer.attach(4);
  }
  while( micros() - timer < 20000);
}

ISR(PCINT0_vect)
{
  timer[0]=micros();
  //channel 1 ----
  
  if(last_channel[0]==0 && PINB & B00000010) //makes sure that the first pin was initially low and is now high
  {                                         //PINB & B00000001 is equivalent to digitalRead but faster
    last_channel[0] = 1;
    delT=timer[0]-timer[1];          
    if(delT>3000)
    {
      tick=0;
    }
    else
    {
      input[tick++] = delT;
    }
    timer[1]=timer[0];
  }
  else if(last_channel[0]==1 && !(PINB & B00000010))
  {
    last_channel[0]=0;
  }
  //channel 2---                  
  if(last_channel[1]==0 && PINB & B00000100) //makes sure that the first pin was initially low and is now high
  {                                         //PINB & B00000001 is equivalent to digitalRead but faster
    last_channel[1]=1;
    timer[2]=timer[0];          
  }
  else if(last_channel[1]==1 && !(PINB & B00000100))
  {
    last_channel[1]=0;
    input[8]=timer[0]-timer[2];
    servoWrite = true;
  }
  
  //channel 3-- 
  if(last_channel[2]==0&& PINB & B00001000) //makes sure that the first pin was initially low and is now high
  {                                         //PINB & B00000001 is equivalent to digitalRead but faster
    last_channel[2]=1;
    timer[3]=timer[0];          
  }
  else if(last_channel[2]==1 && !(PINB & B00001000))
  {
    last_channel[2]=0;
    input[9]=timer[0]-timer[3];
    
  }
}

