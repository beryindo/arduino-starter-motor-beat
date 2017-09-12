#include <gprs.h>
#include <softwareserial.h>

#define TIMEOUT    5000
#define LED_PIN    13
#define ON LOW
#define OFF HIGH

const int Relay1 = 2;
const int Relay2 = 3;
const int Relay3 = 4;
const int Relay4 = 5;

int StatRelay1;
int StatRelay2;
int StatRelay3;
int StatRelay4;

GPRS gprs;

void setup() {
  pinMode (Relay1 , OUTPUT); 
  digitalWrite (Relay1, HIGH);
  pinMode (Relay2 , OUTPUT); 
  digitalWrite (Relay2, HIGH);
  pinMode (Relay3 , OUTPUT); 
  digitalWrite (Relay3, HIGH);
  pinMode (Relay4 , OUTPUT); 
  digitalWrite (Relay4, HIGH);
  StatRelay1 = OFF;
  StatRelay2 = OFF;
  StatRelay3 = OFF;
  StatRelay4 = OFF;
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Projek Bery Indo");
  gprs.preInit();
  delay(1000);

  while (0 != gprs.init()) {
    delay(1000);
    Serial.print("init error\r\n");
  }

//  Set SMS mode to ASCII
  if (0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }

//  Start listening to New SMS Message Indications
  if (0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }

  Serial.println("Software berjalan sukses");
  gprs.sendCmdAndWaitForResp("AT+CMGD=1,4\r\n", "OK", TIMEOUT);
  Serial.println("SMS CLear");
}

//Variable to hold last line of serial output from SIM800
char currentLine[50] = "";
int currentLineIndex = 0;

//Boolean to be set to true if message notificaion was found and next
//line of serial output is the actual SMS message content
bool nextLineIsMessage = false;

void loop() {
//  Write current status to LED pin
  digitalWrite(Relay1, StatRelay1);
  digitalWrite(Relay2, StatRelay2);
  digitalWrite(Relay3, StatRelay3);
  digitalWrite(Relay4, StatRelay4);

//  If there is serial output from SIM800
  if (gprs.serialSIM800.available()) {
    char lastCharRead = gprs.serialSIM800.read();
//    Read each character from serial output until \r or \n is reached (which denotes end of line)
    if (lastCharRead == '\r' || lastCharRead == '\n') {
      String lastLine = String(currentLine);

//      If last line read +CMT, New SMS Message Indications was received.
//      Hence, next line is the message content.
      if (lastLine.startsWith("+CMT:")) {

        Serial.println(lastLine);
        nextLineIsMessage = true;

      } else if (lastLine.length() > 0) {

        if (nextLineIsMessage) {
          Serial.println(lastLine);


//           ########## MEMBACA KONTEN SMS DAN MENCARI+MENGARTIKAN KONTEN SMS KE PROGRAM #########
//          Kendali Relay
           if ((lastLine.indexOf("+628123456789")) && (lastLine.indexOf("hidup")) >= 0) 
           {            
            StatRelay1 = ON;
            digitalWrite(Relay1, StatRelay1);
            Serial.println("Relay1 DINYALAKAN");
            delay(7000);                        
            StatRelay2 = ON;
            StatRelay3 = ON;
            digitalWrite(Relay2, StatRelay2);
            digitalWrite(Relay3, StatRelay3);
            delay(3000);
            StatRelay2 = OFF;
            StatRelay3 = OFF;
//            Serial.println("Relay2&3 NYALA trus MATI");
            gprs.sendSMS ("08123456789", "Mesin berhasil HIDUP");
//            gprs.sendCmdAndWaitForResp("AT+CMGD=1,4\r\n", "OK", TIMEOUT);
          }
          if ((lastLine.indexOf("+628123456789")) && (lastLine.indexOf("mati")) >= 0) {
            StatRelay1 = OFF;
//            Serial.println("Relay1 DIMATIKAN");
            gprs.sendSMS ("08123456789", "Mesin berhasil MATI");
//            gprs.sendCmdAndWaitForResp("AT+CMGD=1,4\r\n", "OK", TIMEOUT);
          }
          nextLineIsMessage = false;
        }

      }

//      Clear char array for next line of read
      for ( int i = 0; i < sizeof(currentLine);  ++i ) {
        currentLine[i] = (char)0;
      }
      currentLineIndex = 0;
    } else {
      currentLine[currentLineIndex++] = lastCharRead;
    }
  }
}
