#include <VirtualWire.h>
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
//Serial.begin(9600);

vw_set_ptt_inverted(true); 
vw_setup(2000);
}

void loop() {
  
  unsigned long now = millis();
    if (now >= TIMESTAMP1+DELAY1) {
      TIMESTAMP1 = now;
      t = dht.readTemperature();
      h = dht.readHumidity();
      //Serial.println(t);
      char msg[24];
      sprintf(msg, "%i:%i", t,h);
      vw_send((uint8_t *)msg, strlen(msg));
      vw_wait_tx(); 
      
  }
}
