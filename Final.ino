#include <Servo.h>
#include <Keypad.h>
/* red light= d13,  buzzer= d12,  keypad= 3 to 10 ulta, servo= 11,  */
Servo servo1;
int red=13;
String pass,check,new1,new2;
String chpass;
int buz=12;
int alarm=0;
int on=0;
int option=3;
char key;
String pass1="123*";
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4, 3}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(red,OUTPUT);
pinMode(buz,OUTPUT);
servo1.attach(11);
servo1.write(180);
}

void loop() {
  // put your main code here, to run repeatedly:
  char customKey = customKeypad.getKey();
  if(option==3){
    if (customKey=='#'){                         //Turn ON
      Serial.println("Enter Password");
      option=1;
      check="";
    }
    if(customKey=='A'){                          //CHANge Password
      Serial.println("Enter Current Password");
      option=2;
      check="";
    }                           
  }
  if(option==1){
    customKey = customKeypad.waitForKey();
    if(customKey!=NO_KEY){
      check=check+customKey;
      Serial.println(check);
      if(customKey=='*'){
        if (check==pass1){
          on=1;
          option=0;
        }
        else{
          Serial.println("Wrong Password");
          on=0;
          option=3;
        }
      }
    }
  }
  else if(option==2){
    customKey = customKeypad.waitForKey();
    if(customKey!=NO_KEY){
      check=check+customKey;
      Serial.println(check);
      if(customKey=='*'){
        if (check==pass1){
          new1="";
          new2="";
          Serial.println("Enter New Password");
          option=4;
        }
        else{
          Serial.println("Wrong password");
          option=3;
        }
      }
    }
  }
  else if(option==4){
    customKey = customKeypad.waitForKey();
    if(customKey!=NO_KEY){
      new1=new1+customKey;
      Serial.println(new1);
      if(customKey=='*'){
        option=5;
        Serial.println("ReEnter new password");
      }
    }
  }
  else if(option==5){
    customKey = customKeypad.waitForKey();
    if(customKey!=NO_KEY){
      new2=new2+customKey;
      Serial.println(new2);
      if(customKey=='*'){
        if(new1==new2){
          pass1=new2;
          Serial.println("Password changed");
          option=3;
        }
        else{
          Serial.println("Password doesn't match");
          option=3;  
        }
      }
    }
  }
  if(on==0){
    digitalWrite(red,LOW);
    servo1.write(180);
    
  }
  else if(on==1){
    //Serial.println(analogRead(A10));
    delay(10);
    if(analogRead(A10)>=1000){
      alarm=1;
    } 
  if(alarm==1){
    digitalWrite(red,HIGH);
    tone(12,4000,200);
    delay(10);
    tone(12,2000,200);
    delay(10);
    servo1.write(90);
    key = customKeypad.getKey();
    if(key!=NO_KEY){
      pass=pass+key;
      Serial.println(pass);
      if(key=='*'){
        if(pass==pass1){
          alarm=0;
          on=0;
          Serial.println("Turned Off");
        }
        else{
          Serial.println("WRONG PASSWORD");
          pass="";
        }
      }    
    }
  }
  else if(alarm==0){
    digitalWrite(red,LOW);
    servo1.write(180);
  }
}
}
