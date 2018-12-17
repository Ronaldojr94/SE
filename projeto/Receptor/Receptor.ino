#include <VirtualWire.h>
#include <ServoTimer2.h> 

#define POTPIN 5

ServoTimer2 myservo;
unsigned long TIMESTAMP=0;
int ESTADO = 1;
int DELAY = 1000;
int potval = 0;
int val = 0;
int t = 0;
int h = 0;
char retorno[5]="";

void setup()
{
Serial.begin(9600); // Debugging only
Serial.println("setup");

DDRB |= 1 << 0;
DDRB |= 1 << 1;
DDRB |= 1 << 2;
DDRB |= 1 << 3;
DDRB |= 1 << 4;
DDRB |= 1 << 5;
DDRB |= 1 << 6;
DDRD |= 1 << 2;
DDRD |= 1 << 4;
DDRD |= 1 << 5;
DDRD |= 1 << 6;
DDRD |= 1 << 7;

myservo.attach(3);
vw_set_rx_pin(2);
vw_set_ptt_inverted(true); // Required for DR3100
vw_setup(2000); // Bits per sec
vw_rx_start(); // Start the receiver PLL running
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
      for(int i=0;i<buflen;i++){ 
        retorno[i]=char(buf[i]);
  }
  sscanf( retorno, "%d,%d", &t, &h );
  retorno[buflen]=NULL;
  }
  potval = analogRead(POTPIN);
  DELAY = map(potval, 0 , 1023, 1, 5000);
  unsigned long now1 = millis();
  if (now1 >= TIMESTAMP+DELAY) {
    TIMESTAMP = now1;
    ESTADO = !ESTADO;
    if(!ESTADO){
      val = t / 10;
      PORTB |= 1 << 3;
    }
    if(ESTADO){
      val = (int)t % 10;
      PORTB &= ~(1 << 3);
    }
  }
  setDisplay(val);
  if(t<20){
    PORTD = PORTD & ~(1<<5) & ~(1<<6);
    PORTD |= 1 << 7;
  }
  if((t>=20)&&(t<35)){
    
    PORTB = PORTB & ~(1<<5) & ~(1<<7);
    PORTD |= 1 << 6;
  }
  if(t>35){
    PORTD = PORTD & ~(1<<6) & ~(1<<7);
    PORTD |= 1 << 5;
  }
  int hval = map(h, 0, 100, 0, 180); 
  myservo.write(hval); 
  delay(15);
}

void setDisplay(int number)
{
  if (number == 1){
      displayOn(1);displayOn(2);
      displayOff(0);displayOff(3);displayOff(4);displayOff(5);displayOff(6);
  }
  if (number == 2){
      displayOn(0);displayOn(1);displayOn(3);displayOn(4);displayOn(6);
      displayOff(2);displayOff(5);
    }  
  if (number == 3){
      displayOn(0);displayOn(1);displayOn(2);displayOn(3);displayOn(6);
      displayOff(4);displayOff(5);
    }  
  if (number == 4){
      displayOn(1);displayOn(2);displayOn(5);displayOn(6);
      displayOff(0);displayOff(3);displayOff(4);
    }  
  if (number == 5){
      displayOn(0);displayOn(2);displayOn(3);displayOn(5);displayOn(6);
      displayOff(1);displayOff(4);
    }  
  if (number == 6){
      displayOn(0);displayOn(2);displayOn(3);displayOn(4);displayOn(5);displayOn(6);
      displayOff(1);
  }
  if (number == 7){
      displayOn(0);displayOn(1);displayOn(2);
      displayOff(3);displayOff(4);displayOff(5);displayOff(6);
    }  
  if (number == 8){
      displayOn(0);displayOn(1);displayOn(2);displayOn(3);displayOn(4);displayOn(5);displayOn(6);
    }  
  if (number == 9){
      displayOn(0);displayOn(1);displayOn(2);displayOn(3);displayOn(4);displayOn(6);
      displayOff(5);
    }  
  if (number == 0){
      displayOn(0);displayOn(1);displayOn(2);displayOn(3);displayOn(4);displayOn(5);
      displayOff(6);
  }  
}

void displayOn(int led)
{
  if (led == 0){
      PORTB = PORTB & ~(1<<0);
  }
  if (led == 1){
      PORTB = PORTB & ~(1<<1);
  }
  if (led == 2){
      PORTB = PORTB & ~(1<<2);
  }
  if (led == 3){
      PORTB = PORTB & ~(1<<3);
  }
  if (led == 4){
      PORTB = PORTB & ~(1<<4);
  }
  if (led == 5){
      PORTB = PORTB & ~(1<<5);
  }
  if (led == 6){
      PORTD = PORTD & ~(1<<4);
  }
}
void displayOff(int led)
{
  if (led == 0){
      PORTB |= (1<<0);
  }
  if (led == 1){
      PORTB |= (1<<1);
  }
  if (led == 2){
      PORTB |= (1<<2);
  }
  if (led == 3){
      PORTB |= (1<<3);
  }
  if (led == 4){
      PORTB |= (1<<4);
  }
  if (led == 5){
      PORTB |= (1<<5);
  }
  if (led == 6){
      PORTD |= (1<<4);
  }
}
