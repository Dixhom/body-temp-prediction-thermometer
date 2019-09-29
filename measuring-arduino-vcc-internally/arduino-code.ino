/*

*/
double r1 = 9810; // ohm

long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  // Back-calculate AVcc in mV
  // the magic number 1124000L is optimized to the Arduino I'm using 
  result = 1124000L / result; 
  return result;
}

void setup() {
    Serial.begin(9600);
    Serial.println("time[ms],R1[ohm]");
}

// the loop function runs over and over again forever
void loop() {
  double vcc = readVcc() / 1000.0;
  double v0 = analogRead(0) / 1024.0 * vcc; // Vcc is Vref in default
  double r2 = v0 * r1 / (vcc - v0); // ohm
  Serial.print(millis());
  Serial.print(",");
  Serial.print(r2);
  Serial.println();
  delay(1000);
}
