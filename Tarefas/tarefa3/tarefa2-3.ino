#include <DHT.h>

#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11
#define POTPIN 5

DHT dht(DHTPIN, DHTTYPE);

unsigned long TIMESTAMP=0;
unsigned long TIMESTAMP1=0;
int val = 1;
int ESTADO = 1;
int DELAY = 1000;
int DELAY1 = 2000;
int potval = 0;
float t=0; 
int pos;


void setup() {
DDRD = 0b11111111;
DDRB |= 1 << 4;
DDRB |= 1 << 3;
DDRB |= 1 << 2;
DDRB |= 1 << 1;
//Serial.begin(9600);
}

void loop() {
  potval = analogRead(POTPIN);
  DELAY = map(potval, 0 , 1023, 1, 5000);
  
  unsigned long now = millis();
  if (now >= TIMESTAMP1+DELAY1) {
    TIMESTAMP1 = now;
    t = dht.readTemperature();
    //Serial.println(t);
  } 
   
  unsigned long now1 = millis();
  if (now1 >= TIMESTAMP+DELAY) {
    TIMESTAMP = now1;
    ESTADO = !ESTADO;
    if(!ESTADO){
      val = t / 10;
      PORTB |= 1 << 4;
    }
    if(ESTADO){
      val = (int)t % 10;
      PORTB &= ~(1 << 4);
    }
  }
  setDisplay(val);
  if(t<20){
    PORTB = PORTB & ~(1<<1) & ~(1<<2);
    PORTB |= 1 << 3;
  }
  if((t>=20)&&(t<35)){
    
    PORTB = PORTB & ~(1<<1) & ~(1<<3);
    PORTB |= 1 << 2;
  }
  if(t>35){
    PORTB = PORTB & ~(1<<2) & ~(1<<3);
    PORTB |= 1 << 1;
  }
}

void setDisplay(int number){
  if (number == 1){
      PORTD = 0b11110010;
  }
  if (number == 2){
      PORTD = 0b01001001;
    }  
  if (number == 3){
      PORTD = 0b01100000;
    }  
  if (number == 4){
      PORTD = 0b00110010;
    }  
  if (number == 5){
      PORTD = 0b00100100;
    }  
  if (number == 6){
      PORTD = 0b00000100;
  }
  if (number == 7){
      PORTD = 0b11110000;
    }  
  if (number == 8){
      PORTD = 0b00000000;
    }  
  if (number == 9){
      PORTD = 0b00100000;
    }  
  if (number == 0){
      PORTD = 0b10000000;
    }  
}
