// Module sensor getar sw18010p
// Arduino UNO/Nano
// Pin A0 atau D0 di hubungkan ke PIN12
// VCC ke 5V, GND ke GND

const int vibrationSensorPin = 12; // Vibration Sensor di hubungkan ke Pin 12
int vibrationSensorState = 0;
unsigned long previousMillis = 0;
long OnTime = 100; //100ms
long OffTime = 300000; //5 menit

void setup() {
  Serial.begin(9600);
  pinMode(vibrationSensorPin, INPUT); // Jadikan Vibration sensor sebagai input
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  vibrationSensorState = digitalRead(vibrationSensorPin);
  // ketika ada getaran LED akan hidup selama 5 menit (300000 mili detik)
  if ((vibrationSensorState == LOW) && (currentMillis - previousMillis >= OnTime)) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Hidup");
    previousMillis = currentMillis;
  }
  // ketika TIDAK ada getaran selama 5 menit (300000 mili detik) LED akan mati
  else if ((vibrationSensorState == HIGH) && (currentMillis - previousMillis >= OffTime)) {
    // ketik kode power saving disini
    digitalWrite(LED_BUILTIN, LOW);
     Serial.println("Mati");
    previousMillis = currentMillis;
  }
}
