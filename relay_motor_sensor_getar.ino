#include <SoftwareSerial.h>
#define ON LOW
#define OFF HIGH

SoftwareSerial gsm(10, 11); //TX,RX

String bacaSMS = "";
String msg = "";
bool siap = 0;
unsigned int errorCounter;

//char nomorHP = "+6281312357771";

const int Relay1 = 2;
const int Relay2 = 3;
const int Relay3 = 4;
const int Relay4 = 5;
const int Relay5 = 6;
const int Relay6 = 7;
const int Relay7 = 8;
const int Relay8 = 9;
const int Relay13 = 13;

int StatRelay1;
int StatRelay2;
int StatRelay3;
int StatRelay4;
int StatRelay5;
int StatRelay6;
int StatRelay7;
int StatRelay8;
int StatRelay13;
const int vibrationSensorPin = 12;
int vibrationSensorState = 0;

void setup() {
  pinMode(vibrationSensorPin, INPUT);
  pinMode (Relay1, OUTPUT);
  digitalWrite (Relay1, HIGH);
  pinMode (Relay2, OUTPUT);
  digitalWrite (Relay2, HIGH);
  pinMode (Relay3, OUTPUT);
  digitalWrite (Relay3, HIGH);
  pinMode (Relay4, OUTPUT);
  digitalWrite (Relay4, HIGH);
  pinMode (Relay5, OUTPUT);
  digitalWrite (Relay5, HIGH);
  pinMode (Relay6, OUTPUT);
  digitalWrite (Relay6, HIGH);
  pinMode (Relay7, OUTPUT);
  digitalWrite (Relay7, HIGH);
  pinMode (Relay8, OUTPUT);
  digitalWrite (Relay8, HIGH);
  StatRelay1 = OFF;
  StatRelay2 = OFF;
  StatRelay3 = OFF;
  StatRelay4 = OFF;
  StatRelay5 = OFF;
  StatRelay6 = OFF;
  StatRelay7 = OFF;
  StatRelay8 = OFF;
//  StatRelay13 = OFF;
  Serial.begin(9600);
  gsm.begin(9600);
  delay(3000);
  Serial.println("Projek Bery Indo");
  gsm.println("AT+CMGF=1");
  delay(500);
  printSerialData();
  gsm.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  printSerialData();
  gsm.println("AT+CMGD=1,4");
  delay(500);
  printSerialData();
}

void loop() {
  //  Write current status to LED pin
  digitalWrite(Relay1, StatRelay1);
  digitalWrite(Relay2, StatRelay2);
  digitalWrite(Relay3, StatRelay3);
  digitalWrite(Relay4, StatRelay4);
  digitalWrite(Relay5, StatRelay5);
  digitalWrite(Relay6, StatRelay6);
  digitalWrite(Relay7, StatRelay7);
  digitalWrite(Relay8, StatRelay8);

  //  If there is serial output from SIM800
  if (gsm.available()) {
    bacaSMS += (char)gsm.read();
    if (bacaSMS.indexOf("motor hidup") >= 0) {
      StatRelay1 = ON;
      digitalWrite(Relay1, StatRelay1);
      Serial.println("Relay1 DINYALAKAN");
      delay(7000);
      StatRelay2 = ON;
      digitalWrite(Relay2, StatRelay2);
      delay(3000);
      StatRelay2 = OFF;
      siap = 1;
      errorCounter = 0;
      bacaSMS.remove(0);
      gsm.println("AT+CMGD=1,4");
    }
    else if (bacaSMS.indexOf("motor mati") >= 0) {
      StatRelay1 = OFF;
      digitalWrite(Relay1, StatRelay1);
      siap = 0;
      errorCounter = 0;
      bacaSMS.remove(0);
      gsm.println("AT+CMGD=1,4");
    }
    else if (bacaSMS.indexOf("motor lock") >= 0) {
      StatRelay3 = ON;
      digitalWrite(Relay3, StatRelay3);
      StatRelay8 = ON;
      digitalWrite(Relay8, StatRelay8);  
      delay(2000);    
      StatRelay8 = OFF;
      digitalWrite(Relay8, StatRelay8);  
      siap = 1;
      errorCounter = 0;
      bacaSMS.remove(0);
      gsm.println("AT+CMGD=1,4");
    }
    else if (bacaSMS.indexOf("motor normal") >= 0) {
      StatRelay4 = OFF;
      digitalWrite(Relay4, StatRelay4);
      StatRelay13 = ON;
      digitalWrite(Relay13, StatRelay13);    
      StatRelay8 = ON;
      digitalWrite(Relay8, StatRelay8);  
      delay(2000);    
      StatRelay8 = OFF;
      digitalWrite(Relay8, StatRelay8);         
      siap = 0;
      errorCounter = 0;
      bacaSMS.remove(0);
      gsm.println("AT+CMGD=1,4");
    }
    else if (bacaSMS.indexOf("motor tidur") >= 0) {
      //      bool sensorGetar();
      StatRelay13 = OFF;
      digitalWrite(Relay13, StatRelay13);
      siap = 1;
      errorCounter = 0;
      bacaSMS.remove(0);
      StatRelay8 = ON;
      digitalWrite(Relay8, StatRelay8);  
      delay(2000);    
      StatRelay8 = OFF;
      digitalWrite(Relay8, StatRelay8); 
      gsm.println("AT+CMGD=1,4");
//      delay(1000);
    }
    else if (bacaSMS.indexOf("motor bangun") >= 0) {
      StatRelay13 = ON;
      digitalWrite(Relay13, StatRelay13);
      siap = 1;
      errorCounter = 0;
      bacaSMS.remove(0);
      StatRelay8 = ON;
      digitalWrite(Relay8, StatRelay8);  
      delay(2000);    
      StatRelay8 = OFF;
      digitalWrite(Relay8, StatRelay8); 
      gsm.println("AT+CMGD=1,4");
    }
    else if (bacaSMS.indexOf("lampu depan") >= 0) {
      StatRelay6 = ON;
      digitalWrite(Relay6, StatRelay6);
      siap = 1;
      errorCounter = 0;
      bacaSMS.remove(0);
      StatRelay8 = ON;
      digitalWrite(Relay8, StatRelay8);  
      delay(2000);    
      StatRelay8 = OFF;
      digitalWrite(Relay8, StatRelay8); 
      gsm.println("AT+CMGD=1,4");
    }
    else if (bacaSMS.indexOf("lampu sen") >= 0) {
      StatRelay7 = ON;
      digitalWrite(Relay7, StatRelay7);
      siap = 1;
      errorCounter = 0;
      bacaSMS.remove(0);
      StatRelay8 = ON;
      digitalWrite(Relay8, StatRelay8);  
      delay(2000);    
      StatRelay8 = OFF;
      digitalWrite(Relay8, StatRelay8); 
      gsm.println("AT+CMGD=1,4");
    }
    else if (bacaSMS.indexOf("klakson") >= 0) {
      StatRelay8 = ON;
      digitalWrite(Relay8, StatRelay8);
      siap = 1;
      errorCounter = 0;
      bacaSMS.remove(0);
      StatRelay8 = ON;
      digitalWrite(Relay8, StatRelay8);  
      delay(2000);    
      StatRelay8 = OFF;
      digitalWrite(Relay8, StatRelay8); 
      gsm.println("AT+CMGD=1,4");
    }
  }
  if (StatRelay13 == OFF) {
    vibrationSensorState = digitalRead(vibrationSensorPin);
    if (vibrationSensorState == LOW) {
//      Serial.println("central lock hidup...");
      StatRelay4 = ON;
      digitalWrite(Relay4, StatRelay4);
    }
  }
}

void printSerialData()
{
  while (gsm.available() != 0)
    Serial.write(gsm.read());
}
