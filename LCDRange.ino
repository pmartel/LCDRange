//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * (Put these in order
 * LCD VSS pin to ground
 * LCD VCC pin to 5V (should be VDD - POM)
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * LCD RS pin to digital pin 7
 * LCD E(nable) pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD A pin through 220 Ohm resistor to 5V (added -POM)
 * LCD K pin to ground (added -POM)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */
//#define BLINK_BUILTIN_LED

// include the library code:
#include <LiquidCrystal.h>
#include "SR04.h"
#include "Streaming.h"

// initialize the library with the numbers of the interface pins
//               RS, E,D4, D5, D6, D7 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define TRIG_PIN 2
#define ECHO_PIN 3
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long r1,r2;
long usec1,usec2;
float v;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Hello, World!");
    pinMode( LED_BUILTIN, OUTPUT);
  #ifndef BLINK_BUILTIN_LED
    digitalWrite( LED_BUILTIN, LOW); //turn BUILTIN_LED off if you don't want to blink it
  #endif
   delay(1000);
   r1=0;
   usec1 = micros();
   Serial.begin(115200);
}

void loop() {
  r2 = sr04.Distance();
  usec2 = micros();
  v = float(r2-r1)*1e6/float(usec2-usec1);

  Serial << "R " << r2 << "\t" << r1 << endl;
  Serial << "t " << usec2 - usec1 << endl;
  Serial << v << " cm/sec"<< endl;
  Serial << endl;
  
  lcd.clear();
  lcd.print(r2);
  lcd.setCursor(5,0);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print(v);
  delay(100);
  r1 = r2;
  usec1 = usec2;
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):

//  lcd.setCursor(0, 1);
//  // print the number of seconds since reset:
//  lcd.print(millis() / 1000);
  #ifdef BLINK_BUILTIN_LED
    delay(500);
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  #endif
}

