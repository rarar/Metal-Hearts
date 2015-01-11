const int HEARTS = 3;
const int SYSTOLEONTIME = 75;
const int SYSTOLEOFFTIME = 120;
const int DIASTOLEONTIME = 75;
const int DIASTOLEOFFTIME = 1200;

float radVal = 0;

struct {
  char pin;
  unsigned long T;	// time for next state change
  char state;
  float radVal;
  unsigned diastoleOffTimeRange;

} 
hearts [HEARTS] = {
  11, 0, 0, 0, 400,	        // first heart pin,
  10, 0, 0, 3.141, 400,
  12, 0, 0, 1.571, 400
};


void setup() {
  Serial.begin(9600);
  for (int h = 0; h < sizeof(hearts); h++) {
    pinMode(hearts[h].pin, OUTPUT);
  }
}

void loop() {
  heartX (0);
  heartX (1);
  heartX (2);
}


void heartX (int h) {

  if (millis() < hearts[h].T) return;

  switch (hearts[h].state) {
  case 0:
    digitalWrite (hearts[h].pin, 1);
    hearts[h].T= millis() + SYSTOLEONTIME;
    hearts[h].state= 1;
    break;
  case 1:
    digitalWrite (hearts[h].pin, 0);
    hearts[h].T= millis() + SYSTOLEOFFTIME;
    hearts[h].state= 2;
    break;
  case 2:
    digitalWrite (hearts[h].pin, 1);
    hearts[h].T= millis() + DIASTOLEONTIME;
    hearts[h].state= 3;
    break;
  case 3:
    digitalWrite (hearts[h].pin, 0);
    hearts[h].T= millis() + DIASTOLEOFFTIME + (sin(hearts[h].radVal) * hearts[h].diastoleOffTimeRange);
    Serial.print("rad val = "); Serial.println(hearts[h].radVal);
    Serial.print("heart "); Serial.print(h); Serial.print(" and off time is = "); Serial.println(sin(hearts[h].radVal) * hearts[h].diastoleOffTimeRange);
    hearts[h].radVal+=0.01;
    hearts[h].state= 0;
    break;
  }
}





