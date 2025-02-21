unsigned long currentTime = 0;
const int ledPins[] = {8, 9, 10, 11};
const int numberOfLeds = 4;
const int potentiometerPin = A1;
const long maxValue = 1023;    
const int pinButton = 2;
const int HIGHEST = 255;
const int HUNDRED = 100;
const int LOWEST = 0;
const int howLongOfAProgressBar = 20;               
int ledIndex = 0;
unsigned int potentiometerValue;

void setup() {
  Serial.begin(9600);
  pinMode(pinButton, INPUT_PULLUP);
  for (int i = LOWEST; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT); 
  }
  Serial.println("Setup completed");
}

void loop() {
  currentTime = millis();
  potentiometerValue = analogRead(potentiometerPin);
  displayPercentages(isClicked(currentTime), potentiometerValue);
  whichLedIsOn(potentiometerValue);
}

int isClicked(unsigned long ct) {        //Merci pour la fonction!
  static unsigned long lastTime = 0;
  static int lastState = HIGH;
  const int rate = 50;
  int click = 0;

  if (ct - lastTime < rate) {
    return click;
  }

  lastTime = ct;
  int state = digitalRead(pinButton);

  if (state == LOW) {
    if (lastState == HIGH) {
      click = 1;
    }
  }

  lastState = state;

  return click;
}

void displayPercentages(int click, unsigned int potentiometerValue) {
  int percent = map(potentiometerValue, LOWEST, maxValue, LOWEST, HUNDRED);
  int specialA = map(percent, LOWEST, HUNDRED, LOWEST, howLongOfAProgressBar);
  int progressBar = howLongOfAProgressBar - specialA;

  if (click == 1) {
    Serial.print(percent);
    Serial.print("%  [");
    for (int i = 1; i <= specialA; i++) {
      Serial.print("@");
    }
    for (int i = 1; i <= progressBar; i++) {
     Serial.print(".");
    }
    Serial.println("]");
  }
}

void whichLedIsOn(unsigned int potentiometerValue) {
  analogWrite(ledPins[ledIndex], LOWEST);
  ledIndex = map(potentiometerValue, LOWEST, maxValue, LOWEST, numberOfLeds);
  if (ledIndex == numberOfLeds) {
    ledIndex = (numberOfLeds - 1);         //Pour parier un problème au niveau de la répartition des index sur la valeur du potentiomètre
  }
  analogWrite(ledPins[ledIndex], HIGHEST);
}
