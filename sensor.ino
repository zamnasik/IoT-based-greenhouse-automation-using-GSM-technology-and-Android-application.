
void Dhtread() {

  sensorValue = analogRead(sensorPin);
  percentValue = map(sensorValue, 1023, 200, 0, 100);



  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  tft.fillRect(110, 0, 60, 15, BLACK);
  tft.setCursor(110, 0);                                //Position of the cursor from where do you want to start writing
  tft.setTextColor(WHITE);  tft.setTextSize(2);       //Text color and size (1-5)
  tft.println(h);

  tft.fillRect(140, 30, 60, 15, BLACK);
  tft.setCursor(140, 30);                                //Position of the cursor from where do you want to start writing
  tft.setTextColor(WHITE);  tft.setTextSize(2);       //Text color and size (1-5)
  tft.println(t);
   

  tft.fillRect(145, 60, 60, 15, BLACK);
  tft.setCursor(145, 60);                                //Position of the cursor from where do you want to start writing
  tft.setTextColor(WHITE);  tft.setTextSize(2);       //Text color and size (1-5)
  tft.println(hif);

T=t;
H=h;
M=percentValue;




  tft.fillRect(120, 90, 25, 15, BLACK);
  tft.setCursor(120, 90);                                //Position of the cursor from where do you want to start writing
  tft.setTextColor(WHITE);  tft.setTextSize(2);       //Text color and size (1-5)
  tft.println(percentValue);







  int mod = digitalRead(manualledPin);
if (mod == LOW ){

          if (T > MIDtemp + 3) {
            tft.fillRect(70, 275, 40, 40, bottonHIGH); //fan
            fan = HIGH;
            digitalWrite(ledPin, HIGH);
            digitalWrite(24, LOW);
          } else {
            tft.fillRect(70, 275, 40, 40, bottonLOW);
            fan = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(24, HIGH);
          }


          if (T < MIDtemp - 3) {
            tft.fillRect(130, 275, 40, 40, bottonHIGH);//heater
            heater = HIGH;
            digitalWrite(ledPin, HIGH);
            digitalWrite(26, LOW);
          } else {
            tft.fillRect(130, 275, 40, 40, bottonLOW);
            heater = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(26, HIGH);


          }

          if ( percentValue  <  MIDmoisure) {

            tft.fillRect(10, 275, 40, 40, bottonHIGH);
            pump = HIGH;
            digitalWrite(ledPin, HIGH);
            digitalWrite(22, LOW);
          } else {
            tft.fillRect(10, 275, 40, 40, bottonLOW);
            pump = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(22, HIGH);
          }






  }




}



  void alloff() {
               tft.fillRect(10, 275, 40, 40, bottonLOW);
            pump = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(22, HIGH);
                        tft.fillRect(70, 275, 40, 40, bottonLOW);
            fan = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(24, HIGH);
                        tft.fillRect(130, 275, 40, 40, bottonLOW);
            heater = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(26, HIGH);
                        tft.fillRect(190, 275, 40, 40, bottonLOW);
            light = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(28, HIGH);
  }
