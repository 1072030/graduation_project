#define C5 523
#define E5 659
#define G5 784

#define pinPz 8
const byte analogPin0 = A0;
const byte analogPin1 = A1;

int value1, value2;
int dawy = 603;
int x;
int morris = 832;
int y;
void setup() {
  Serial.begin(9600);
  pinMode(pinPz, OUTPUT);

}

void loop() {
  aaa(pinPz);
}

void aaa(int pin) {
  value1 = analogRead(analogPin0);

  Serial.println(value1);
  if (value1 >= dawy) {
    x = value1 - dawy;
  }
  else {
    x = dawy - value1;
  }

  value2 = analogRead(analogPin1);
  Serial.println(value2);
  if (value2 >= morris) {
    y = value2 - morris;
  }
  else {
    y = morris - value2;
  }
  tone(pinPz, 500);
  delay(10);

  noTone(pin);
  delay(x + y);
  if(x+y<=7){
    music();
  }
}

void music(){
  tone(pinPz,E5,150);
  delay(150);
  tone(pinPz,E5,150);
  delay(150);
  tone(pinPz,E5,150);
  delay(300);
  tone(pinPz,C5,150);
  delay(150);
  tone(pinPz,E5,150);
  delay(300);
  tone(pinPz,G5,150);
  delay(2000);
}
