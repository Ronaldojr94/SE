#define LED_PIN 9
#define BUT_PIN1 7
#define BUT_PIN2 4

unsigned long TIMESTAMP;
int ESTADO = 0;
int DELAY = 1000;
int buttonLast1 = 1;
int buttonLast2 = 1;

void setup () {
Serial.begin(9600);
pinMode(LED_PIN, OUTPUT); 
pinMode(BUT_PIN1, INPUT); 
pinMode(BUT_PIN2, INPUT); 
}
void loop () {
  
  unsigned long now = millis();
  if (now >= TIMESTAMP+DELAY) {
    TIMESTAMP = now;
    ESTADO = !ESTADO;
    digitalWrite(LED_PIN, ESTADO);
  }

  if(digitalRead(BUT_PIN1) == 0 && buttonLast1 == 1)
  {
    
    DELAY = DELAY + 50;
    Serial.println(DELAY);
    buttonLast1 = 0;
  }
  else if(digitalRead(BUT_PIN1) == 1 && buttonLast1 == 0)
  {
       buttonLast1 = 1;
  }
  if(digitalRead(BUT_PIN2) == 0 && buttonLast2 == 1)
  {
    if((DELAY - 50)>0){
    DELAY = DELAY - 50;
    }
    Serial.println(DELAY);
    buttonLast2 = 0;
  }
  else if(digitalRead(BUT_PIN2) == 0 && buttonLast2 == 0)
  {
       buttonLast2 = 1;
  }

  
  if(!digitalRead(BUT_PIN1)&&!digitalRead(BUT_PIN2)&&DELAY<500){
    digitalWrite(LED_PIN, 0);
    while(1);
  }
}
