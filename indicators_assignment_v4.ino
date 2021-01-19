const int ledPinLeft     =             2;
const int ledPinRight =                 3;
#define buttonPinLeft           4
#define buttonPinRight              5
#define buttonPinHazards           6
#define downLeft                   0
#define upLeft                     1
#define downRight                  7
#define upRight                    8
#define downHazards               9
#define upHazards                 10

int currentState;
int eventRight ;
int eventLeft;
int eventHazards;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  currentState = 0 ;
  pinMode(ledPinLeft, OUTPUT);
  pinMode(ledPinRight, OUTPUT);
  pinMode(buttonPinLeft, INPUT);
  pinMode(buttonPinRight, INPUT);
  pinMode(buttonPinHazards, INPUT);
  Serial.begin(9600);


}

void loop() {
  unsigned long currentMillis = millis();
  int eventRight = detectEventRight();
  int eventLeft = detectEventLeft();
  int eventHazards = detectEventHazards();
  Serial.println(currentState);






  //no indicators on
  if ((currentState == 0) && (eventLeft == downLeft)) {
    currentState = 1;
  }
  if ((currentState == 1) && (eventLeft == upLeft)) {
    currentState = 2;
  }
  if ((currentState == 2) && (eventHazards == downHazards)) {
    currentState = 3;
  }
  if ((currentState == 3) && (eventHazards == upHazards)) {
    currentState = 4;
    //hazzards on
  }
  if ((currentState == 4) && (eventHazards == downHazards)) {
    currentState = 5;
  }
  if ((currentState == 5) && (eventHazards == upHazards)) {
    currentState = 2;

    //right indicator resumes
  }
  if ((currentState == 2) && (eventLeft == downLeft)) {
    currentState = 6;
  }
  if ((currentState == 6) && (eventLeft == upLeft)) {
    currentState = 0; //no indicators on
  }




  if ((currentState == 0) && (eventRight == downRight)) {
    currentState = 7;
  }
  if ((currentState == 7) && (eventRight == upRight)) {
    currentState = 8 ;
    // Right indicator on
  }
  if ((currentState == 8) && (eventHazards == downHazards)) {
    currentState = 9;
  }
  if ((currentState == 9) && (eventHazards == upHazards)) {
    currentState = 10;
    //hazzards on
  }
  if ((currentState == 10) && (eventHazards == downHazards)) {
    currentState = 11;
  }
  if ((currentState == 11) && (eventHazards == upHazards)) {
    currentState = 8; //resumes right indicator
  }
  if ((currentState == 8) && (eventRight == downRight)) {
    currentState = 12;
  }
  if ((currentState == 12) && (eventRight == upRight)) {
    currentState = 0; // no indicators on
  }





  if ((currentState == 0) && (eventHazards == downHazards)) {
    currentState = 13;
  }
  if ((currentState == 13) && (eventHazards == upHazards)) {
    currentState = 14 ;
    // Hazzards  on

  }
  if ((currentState == 14) && (eventHazards == downHazards)) {
    currentState = 15;
  }
  if ((currentState == 15) && (eventHazards == upHazards)) {
    currentState = 0  ; //hazzards off
  }





  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    if ((currentState == 0) || (currentState == 1) || (currentState == 7) || (currentState == 13)) {
      digitalWrite(ledPinLeft, LOW);
      digitalWrite(ledPinRight, LOW);
    }
    if ((currentState == 2) || (currentState == 3) || (currentState == 6)) {
      digitalWrite(ledPinLeft, ledState);
      digitalWrite(ledPinRight, LOW);

    }

    if ((currentState == 8) || (currentState == 9) || (currentState == 12)) {
      digitalWrite(ledPinRight, ledState);
      digitalWrite(ledPinLeft, LOW);

    }
    if ((currentState == 4) || (currentState == 5) || (currentState == 10) || (currentState == 11) || (currentState == 14) || (currentState == 15)) {
      digitalWrite(ledPinLeft, ledState);
      digitalWrite(ledPinRight, ledState);

    }
  }
}











int detectEventLeft() {
  if (digitalRead(buttonPinLeft) == HIGH) {
    return 0;
  }
  if (digitalRead(buttonPinLeft) == LOW) {
    return 1;
  }
}
int detectEventRight() {
  if (digitalRead(buttonPinRight) == HIGH) {
    return 7;
  }
  if (digitalRead(buttonPinRight) == LOW) {
    return 8;
  }
}
int detectEventHazards() {
  if (digitalRead(buttonPinHazards) == HIGH) {
    return 9;
  }
  if (digitalRead(buttonPinHazards) == LOW) {
  }
  return 10;
}
