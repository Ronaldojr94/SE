void setup() {
  // put your setup code here, to run once:
  pinMode(7, INPUT);
  pinMode(9, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int val = digitalRead(7);
  
  digitalWrite(9, !val);
}
