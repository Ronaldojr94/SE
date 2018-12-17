#include <VirtualWire.h>
#include <DHT.h>

DHT dht(8 , DHT11);
unsigned long TIMESTAMP1 = 0;
int DELAY1 = 2000;
int t = 0;
int h = 0;
 

void setup()
{
Serial.begin(9600);                                      // Debugging only
vw_set_tx_pin(1);
vw_set_ptt_inverted(true);                          // Required for DR3100
vw_setup(2000);                                          // Bits per sec 
}

void loop()
{

unsigned long now = millis();
  if (now >= TIMESTAMP1+DELAY1) {
    TIMESTAMP1 = now;
    t = dht.readTemperature();
    h = dht.readHumidity();

    const char *msg = sprintf(msg, "%i,%i", t,h);;

                                   
  vw_send((uint8_t *)msg, strlen(msg));      
  vw_wait_tx();                                         

  }
}
