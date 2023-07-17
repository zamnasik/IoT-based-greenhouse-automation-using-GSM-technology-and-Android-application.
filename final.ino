/*This code is to use with LCD 2.4" TFT touch screen shield with Arduino UNO board
  It's modified from the Adafruit SPFD5408 library examples for a video tutorial
  The code concerns the use of the touch functions to detect what the user pressed using an example
  Refer to SurtrTech.com for more details
*/
//pin define

#include <SoftwareSerial.h>
SoftwareSerial mySerial(50, 52);
String message;





const int ledPin =  13;

int manualledPin =  40;
int autoledPin =  0;


int T =  0;
int H =  0;
int M =  0;



// variables will change:
int pump = 0;
int pumpBT = 0;
boolean  pumpBTval = false;
int fan = 0;
int fanBT = 0;
boolean  fanBTval = false;
int heater = 0;
int heaterBT = 0;
boolean  heaterBTval = false;
int light = 0;
int lightBT = 0;
boolean  lightBTval = false;

//define sensors
int sensorPin = A8;
int sensorValue = 0;
int percentValue = 0;

//value given n the touch to on the fan and heater
int MIDtemp = 31;
int MIDmoisure = 0;



int lastlight = 0;// variable for reading the pushbutton status
//tempeture sensor
#include "DHT.h"
#define DHTPIN 21//pin for tem
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library display
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif


#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

//Don't forget if your touch function doesn't work check the values above it may be (A1 A2 7 6) resp

// Calibrate values you may want to run the calibration code first and set those points

#define TS_MINX 160
#define TS_MAXX 905
#define TS_MINY 85
#define TS_MAXY 867

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 500);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define bottonHIGH 0x001F
#define bottonLOW   0x0808

#define botton1HIGH 0x0303
#define botton1LOW   0x0101
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);



void setup(void) {
  //to communacte with tem sensor
    mySerial.begin(9600);
  Serial.begin(9600);
  delay(100);

  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);



  dht.begin();


  tft.reset();                         //Shield launching
  tft.begin(0x9341);
  tft.setRotation(0);                  //Rotation 0-3
  tft.fillScreen(BLACK);               //Black background
  tft.fillRect(10, 275, 40, 40, bottonLOW);   //Draws 2 rectangles Green and Red
  tft.fillRect(70, 275, 40, 40, bottonLOW);
  tft.fillRect(130, 275, 40, 40, bottonLOW);   //Draws 2 rectangles Green and Red
  tft.fillRect(190, 275, 40, 40, bottonLOW);





  //dispaly dispalying things
  //place and clours
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Humidity:");

  tft.setCursor(0, 30);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Temperature:");

  tft.setCursor(0, 60);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Heat index:");

  tft.setCursor(0, 90);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Moisture:");






  //small one to set tem and humadity
  tft.setCursor(0, 140);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Temperature");//temp
  tft.setCursor(0, 180);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Moisture");//moisture

  //to increase and degress
  tft.fillRect(70, 130, 30, 30, YELLOW);
  tft.fillRect(138, 130, 30, 30, YELLOW);//constant tem

  tft.fillRect(70, 170, 30, 30, YELLOW);
  tft.fillRect(138, 170, 30, 30, YELLOW);//moisture

  tft.setCursor(72, 128);
  tft.setTextColor(RED);  tft.setTextSize(5);
  tft.println("-");

  tft.setCursor(140, 128);
  tft.setTextColor(RED);  tft.setTextSize(5);
  tft.println("+");


  tft.setCursor(72, 170);
  tft.setTextColor(RED);  tft.setTextSize(5);
  tft.println("-");

  tft.setCursor(140, 168);
  tft.setTextColor(RED);  tft.setTextSize(5);
  tft.println("+");




  //auto manual buttons
  tft.fillRect(20, 220, 80, 30, botton1HIGH);
  tft.fillRect(138, 220, 80, 30, botton1HIGH);//auto manual

  tft.setCursor(25, 225);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Manual");
  tft.setCursor(155, 225);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Auto");



  //manual things to opearte fan pum
  tft.setCursor(15, 262);                                //Position of the cursor from where do you want to start writing
  tft.setTextColor(WHITE);  tft.setTextSize(1);       //Text color and size (1-5)
  tft.println("PUMP");

  tft.setCursor(80, 262);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("FAN");

  tft.setCursor(132, 262);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("HEATER");

  tft.setCursor(195, 262);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("LIGHT");


  pinMode(ledPin, OUTPUT);
  pinMode(13, OUTPUT);


  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);


  pinMode(manualledPin, OUTPUT);
  pinMode(autoledPin, OUTPUT);





}



void loop()
{




  for (int fadeValue = 0 ; fadeValue < 1000; fadeValue ++) {

    TSPoint p = ts.getPoint();       //checking if the user touched the screen

    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);





    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { //p.z means the pressure value so if the touch wants to be detected
      // it pressure should be in this range (it's enough)

      p.x = map(p.x,  TS_MAXX, TS_MINX, 0, tft.width());   //x and y positions of the touch so the program know the postion where the user has pressed

      p.y = map(p.y,  TS_MAXY, TS_MINY, 0, tft.height());



      /*
                      Serial.print("X = "); Serial.print(p.x);
            Serial.print("\tY = "); Serial.print(p.y);
            Serial.print("\tPressure = "); Serial.println(p.z);*/











      //red clour to selct when drawing borders

      if (p.x > 20 && p.x < 100 && p.y > 220 && p.y < 250) { //manual



        tft.drawRect(20, 220, 80, 30, RED);
        tft.drawRect(138, 220, 80, 30, BLACK);
        digitalWrite(manualledPin, HIGH);

        delay(200);

      }      else   if (p.x > 138 && p.x < 218 && p.y > 220 && p.y < 250) { //auto

        tft.drawRect(20, 220, 80, 30, BLACK);
        tft.drawRect(138, 220, 80, 30, RED);
        digitalWrite(manualledPin, LOW);


      }





      int mod = digitalRead(manualledPin);

      if (mod == HIGH ) {/// manual mode



        if (p.x > 10  && p.x < 50 && p.y
            > 275 && p.y < 315) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)

          if (pump == HIGH) {
            tft.fillRect(10, 275, 40, 40, bottonLOW);
            pump = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(22, HIGH);
          } else {
            tft.fillRect(10, 275, 40, 40, bottonHIGH);
            pump = HIGH;
            digitalWrite(ledPin, HIGH);
            digitalWrite(22, LOW);
          }
          delay(500);
        } else   if (p.x > 70 && p.x < 110 && p.y > 275 && p.y < 315) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)
          if (fan == HIGH) {
            tft.fillRect(70, 275, 40, 40, bottonLOW);
            fan = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(24, HIGH);
          } else {
            tft.fillRect(70, 275, 40, 40, bottonHIGH);
            fan = HIGH;
            digitalWrite(ledPin, HIGH);
            digitalWrite(24, LOW);
          }
          delay(500);
        } else   if (p.x > 130 && p.x < 170 && p.y > 275 && p.y < 315) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)
          if (heater == HIGH) {
            tft.fillRect(130, 275, 40, 40, bottonLOW);
            heater = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(26, HIGH);
          } else {
            tft.fillRect(130, 275, 40, 40, bottonHIGH);
            heater = HIGH;
            digitalWrite(ledPin, HIGH);
            digitalWrite(26, LOW);
          }
          delay(500);
        }


        else   if (p.x > 190 && p.x < 230 && p.y > 275 && p.y < 315) { //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)
          if (light == HIGH) {
            tft.fillRect(190, 275, 40, 40, bottonLOW);
            light = LOW;
            digitalWrite(ledPin, LOW);
            digitalWrite(28, HIGH);
          } else {
            tft.fillRect(190, 275, 40, 40, bottonHIGH);
            light = HIGH;
            digitalWrite(ledPin, HIGH);
            digitalWrite(28, LOW);
          }
          delay(200);
        }




      } else {//auto mode


        alloff();

        if (p.x > 70 && p.x < 100 && p.y > 130 && p.y < 160) {//midtem -

          MIDtemp--;

          tft.fillRect(100, 130 , 40, 30, BLACK);
          tft.setCursor(105, 130);                                //Position of the cursor from where do you want to start writing
          tft.setTextColor(WHITE);  tft.setTextSize(2);       //Text color and size (1-5)
          tft.println(MIDtemp);

          // tft.fillRect(70, 130, 30, 30, YELLOW);


        } else   if (p.x > 138 && p.x < 168 && p.y > 130 && p.y < 160) { //midtem +
          MIDtemp++;
          tft.fillRect(100, 130, 40, 30, BLACK);
          tft.setCursor(105, 130);                                //Position of the cursor from where do you want to start writing
          tft.setTextColor(WHITE);  tft.setTextSize(2);       //Text color and size (1-5)
          tft.println(MIDtemp);

        } else   if (p.x > 70 && p.x < 100 && p.y > 170 && p.y < 200) { //mid mourse -
          MIDmoisure--;
          tft.fillRect(100, 170, 40, 30, BLACK);
          tft.setCursor(105, 170);                                //Position of the cursor from where do you want to start writing
          tft.setTextColor(WHITE);  tft.setTextSize(2);       //Text color and size (1-5)
          tft.println(MIDmoisure);

        } else   if (p.x > 138 && p.x < 168 && p.y > 170 && p.y < 200) { //MIDmoisure +
          MIDmoisure++;
          tft.fillRect(100, 170, 40, 30, BLACK);
          tft.setCursor(105, 170);                                //Position of the cursor from where do you want to start writing
          tft.setTextColor(WHITE);  tft.setTextSize(2);       //Text color and size (1-5)
          tft.println(MIDmoisure);
        }


      }

    }

  }




mobiControl();

  Dhtread();//calling the semsors
}






void detalse()
{
  
  mySerial.println("AT+CMGF");
  delay(1000);
  mySerial.println("AT+CMGS=\"+94770219776\"\r");
  delay(1000);
        mySerial.println("Green house project");
        mySerial.println("Designed by - Nasik");
   mySerial.println(" ");
      mySerial.print("Humidity:");
  mySerial.println(H);
    mySerial.print("Temperature:");
  mySerial.println(T);
      mySerial.print("Moisture:");
  mySerial.println(M);
   mySerial.println(" ");
      mySerial.print("pump:");
  mySerial.println(pump);
    mySerial.print("FAN:");
  mySerial.println(fan);
      mySerial.print("heater:");
  mySerial.println(heater);
        mySerial.print("light:");
  mySerial.println(light);
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}
