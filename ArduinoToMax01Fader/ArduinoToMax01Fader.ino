

// analog input variables
int sustain = A3;
int sustainValue;

// for updateInterval timer:
unsigned long updateInterval = 100; // how often to read pins and send over serial (in ms)
unsigned long lastUpdate = 0;
int now; 

void setup() {

  

  // start the serial port communications
  Serial.begin(115200);
}

void loop() {  

  now = millis();
  // update if updateInterval has been exceeded
  if (now > lastUpdate + updateInterval) {
    lastUpdate = now;

    // read pins
    sustainValue = analogRead(sustain);

    // send values over serial connection
    // print analog value
    Serial.print(sustainValue);

    // send a new line at the end of the list
    Serial.println();
  }
}
