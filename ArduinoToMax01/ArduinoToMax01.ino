

// analog input variables
int analogPin = A0;
int analogValue;
int ANALOG_THRESH = 200;

// button variables
int buttonPin = 7;
int buttonState = 0;
int lastButtonState = 0;

// for updateInterval timer:
unsigned long updateInterval = 100; // how often to read pins and send over serial (in ms)
unsigned long lastUpdate = 0;
int now; 


void setup() {

  // configure pins as inputs / outputs as needed
  pinMode(buttonPin, INPUT_PULLUP);

  // start the serial port communications
  Serial.begin(115200);
}

void loop() {  

  now = millis();
  // update if updateInterval has been exceeded
  if (now > lastUpdate + updateInterval) {
    lastUpdate = now;

    // read pins
    //analogValue = analogRead(analogPin);
    // read pins
    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
      Serial.print(1);
      delay(4000);
    }
    else {
      Serial.print(0);
    }

    /*// send values over serial connection
    // print analog value
    Serial.print(analogValue);*/

    // send a new line at the end of the list
    Serial.println();
  }
}
