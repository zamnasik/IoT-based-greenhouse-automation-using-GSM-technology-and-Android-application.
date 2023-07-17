


void mobiControl() {
  if (mySerial.available() > 0) { //gsm reading 
    Serial.write(mySerial.read());
    message = mySerial.readString();
  }

  if (message.indexOf("status") > -1) { 
    Serial.println("LED ON");

    message = -2; //resat message low velu
    delay(10);
    detalse(); //re sand msg
  }

  else if (message.indexOf("OFF") > -1) {

    Serial.println("LED OFF");


  }





if (mySerial.available()>0){
    Serial.write(mySerial.read());
  message = mySerial.readString();
  }

  if (message.indexOf("pump on") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(22, LOW);
    tft.fillRect(10, 275, 40, 40, bottonHIGH);
    pump = HIGH;

  }

  else   if (message.indexOf("fan on") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(24, LOW);
    tft.fillRect(70, 275, 40, 40, bottonHIGH);
    fan = HIGH;

  }

  else   if (message.indexOf("heater on") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(26, LOW);
    tft.fillRect(130, 275, 40, 40, bottonHIGH);
    heater = HIGH;
  }

  else   if (message.indexOf("light on") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(28, LOW);
    tft.fillRect(190, 275, 40, 40, bottonHIGH);
    light = HIGH;
  }










else if (message.indexOf("pump off") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(22, HIGH);
    tft.fillRect(10, 275, 40, 40, bottonLOW);
    pump = LOW;

  }

  else   if (message.indexOf("fan off") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(24, HIGH);
    tft.fillRect(70, 275, 40, 40, bottonLOW);
    fan = LOW;

  }

  else   if (message.indexOf("heater off") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(26, HIGH);
    tft.fillRect(130, 275, 40, 40, bottonLOW);
    heater = LOW;
  }

  else   if (message.indexOf("light off") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(28, HIGH);
    tft.fillRect(190, 275, 40, 40, bottonLOW);
    light = LOW;
  }


  

 














  /*if (message.indexOf("pump on") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(22, HIGH);
    tft.fillRect(10, 275, 40, 40, bottonHIGH);
    pump = HIGH;

  }

  else   if (message.indexOf("fan on") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(24, HIGH);
    tft.fillRect(70, 275, 40, 40, bottonHIGH);
    fan = HIGH;

  }

  else   if (message.indexOf("heater on") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(26, HIGH);
    tft.fillRect(130, 275, 40, 40, bottonHIGH);
    heater = HIGH;
  }

  else   if (message.indexOf("light on") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(28, HIGH);
    tft.fillRect(190, 275, 40, 40, bottonHIGH);
    light = HIGH;
  }










else if (message.indexOf("pump off") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(22, LOW);
    tft.fillRect(10, 275, 40, 40, bottonLOW);
    pump = LOW;

  }

  else   if (message.indexOf("fan off") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(24, LOW);
    tft.fillRect(70, 275, 40, 40, bottonLOW);
    fan = LOW;

  }

  else   if (message.indexOf("heater off") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(26, LOW);
    tft.fillRect(130, 275, 40, 40, bottonLOW);
    heater = LOW;
  }

  else   if (message.indexOf("light off") > -1) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

    digitalWrite(28, LOW);
    tft.fillRect(190, 275, 40, 40, bottonLOW);
    light = LOW;
  }


*/

}
