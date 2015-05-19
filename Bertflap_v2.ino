#include <JeeLib.h>
#include <Servo.h>
#include <JeeLib.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)


ISR(WDT_vect) { Sleepy::watchdogEvent(); } // setup watchdog timer


//Servo bits
Servo myservo;  
int angle; //sets initial angle to unlocked
int curfew = 18;
int freedom = 8;



//Clock bits

int rtcPower = 3; 

void setup() 
{ 
    Serial.begin(9600);
    // Start the I2C interface
    setSyncProvider(RTC.get);   // the function to get the time from the RTC

    //Wire.begin();
    // Sets up pin to power RTC 
    pinMode(rtcPower, OUTPUT); 
    
    
} 
 
 
void loop() 
{ 
        digitalWrite(rtcPower, HIGH);
        //read the RTC
	
        //if (Clock.getHour(h12, PM) >= 19) {
        if ((minute() % 2) == 0) {
            
            Serial.println("Curfew - closed!");
            myservo.attach(5);
            delay(100);
            angle = 60;  
            if (myservo.read() != 60) { 
            myservo.write(angle); 
            delay(75);
            }
            myservo.detach();             
          }  
          
         //if (hour == 8) {
        if (minute() % 2) {

            Serial.println("Freeeedom!");

            myservo.attach(5);
            delay(100);
            angle = 0;  
            if (myservo.read() != 0) { 
            myservo.write(angle); 
            delay(75);
            }
            myservo.detach(); 
          }  
          
          digitalClockDisplay();  


          digitalWrite(rtcPower, LOW);
          Sleepy::loseSomeTime(5000);
       
 
}

void digitalClockDisplay(void)
{
    // digital clock display of the time
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(' ');
    Serial.print(day());
    Serial.print(' ');
    Serial.print(month());
    Serial.print(' ');
    Serial.print(year()); 
    Serial.println(); 
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
