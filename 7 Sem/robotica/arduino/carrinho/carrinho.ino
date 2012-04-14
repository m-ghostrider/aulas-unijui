
#include <Servo.h>
Servo servoRoda; // Define  Servo
Servo servoCam; // Define  Servo

//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control
 
int posCam = 0; 
 
void stop(void)                    //Stop
{
  digitalWrite(E1,LOW);  
  digitalWrite(E2,LOW);     
}  
void advance(char a,char b)          //Move forward
{
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,HIGH);   
  analogWrite (E2,b);   
  digitalWrite(M2,HIGH);
} 
void back_off (char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);  
  analogWrite (E2,b);   
  digitalWrite(M2,LOW);
}
void turn_L (char a,char b)             //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);   
  analogWrite (E2,b);   
  digitalWrite(M2,HIGH);
}
void turn_R (char a,char b)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);   
  analogWrite (E2,b);   
  digitalWrite(M2,LOW);
}
void setup(void)
{
  servoRoda.attach(13);
  servoRoda.write(45);
  
  servoCam.attach(11);
  servoCam.write(45);
  
  int i;
  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT); 
  Serial.begin(9600);      //Set Baud Rate
  Serial.println("Run keyboard control");
}
void loop(void)
{
  if(Serial.available()){
    char val = Serial.read();
    if(val != -1)
    {
      switch(val)
      {
      case 'w'://Move Forward
        advance (255,255);   //move forward in max speed
        servoRoda.write(45);
        break;
      case 's'://Move Backward
        back_off (255,255);   //move back in max speed
        break;
      case 'a'://Turn Left
        turn_L (255,255);
        break;      
      case 'd'://Turn Right
        turn_R (255,255);
        break;
        case 'q'://Turn Right
        servoRoda.write(65);
        break;
        case 'e'://Turn Left
        servoRoda.write(30);
        break;
      case 'x':
        stop();
        break;
      case '+'://camera ++
        posCam= posCam+20;
        if(posCam>180)
          posCam = 180;
        servoCam.write(posCam);
        Serial.println("Camera "+posCam);
        break;
        case '-'://camera ++
        posCam= posCam-20;
        if(posCam<0)
          posCam = 0;
        servoCam.write(posCam);
        Serial.println("Camera "+posCam);
        break;
    }
    }
    else stop(); 
  }
}
