 Include Libraries
#include "Arduino.h"
#include "ESP8266.h"
#include "dweet.h"
#include "LED.h"
#include "Switchable.h"
#include "IRremoteInt.h"
#include "IR.h"
#include "IRremote.h"


// Pin Definitions
#define WIFI_PIN_RX	10
#define WIFI_PIN_TX	11
#define LED_PIN_VIN	5
#define IR_PIN_OUT	2



// Global variables and defines

// object initialization
ESP8266 wifi(WIFI_PIN_RX,WIFI_PIN_TX);
Dweet dweet( &wifi, inputToken, outputToken);
LED led(LED_PIN_VIN);
IR ir(IR_PIN_OUT);



// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    wifi.init(SSID, PASSWORD);
    // initialize IR device
    ir.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Basic Ultraviolet LED 5mm - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
        led.dim(i);                      // 1. Dim Led 
        delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    led.off();                        // 3. turns off
    }
    else if(menuOption == '2') {
    // IR Receiver Diode - TSOP38238 - Test Code
    //Receive IR code into irCode
    long irCode =  ir.detect();
    // if a code was received print it to serial monitor, note that the code is of type long but printed in HEX
    // Consider changing the if statment to something like: if(irCode == "YOUR IR CODE")
    if(irCode)
    {
        Serial.print("0x");
        Serial.println(irCode, HEX);
    }
    }
    
    
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Basic Ultraviolet LED 5mm"));
    Serial.println(F("(2) IR Receiver Diode - TSOP38238"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {
            if(c == '1') 
    			Serial.println(F("Now Testing Basic Ultraviolet LED 5mm"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing IR Receiver Diode - TSOP38238"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
