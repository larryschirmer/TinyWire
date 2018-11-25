/**
 * This file is a mix of helpful script files all over the internet
 * - https://github.com/sudar/TinyWire/blob/master/examples/attiny85_i2c_slave/attiny85_i2c_slave.ino
 * - http://www.getmicros.net/attiny85-ldr-led-arduino-version.php
 * - https://stackoverflow.com/questions/34327520/analog-input-on-attiny85-not-working
 * 
 * Hardware used to flash ATtiny85 - Sparkfun Tiny AVR Programmer (https://www.sparkfun.com/products/11801)
 * Speed: 8 MHz
*/

#include <TinyWireSlave.h>

#define I2C_SLAVE_ADDRESS 0x4 // the 7-bit address 

int analogPin = 3; // pin 2
int LEDPin = 1; // pin 6
int val = 0; // raw light reading value 0-1023
volatile uint8_t i2c_regs[] = { 0x0 }; // single byte to be sent over wire

/**
 * This is called for each read request we receive, never put more than one byte of data (with TinyWireS.send) to the 
 * send-buffer when using this callback
 */
void requestEvent() {  
    TinyWireS.send(i2c_regs[0]); // sends last stored light reading byte
}

void setup() {
    TinyWireS.begin(I2C_SLAVE_ADDRESS); // begins I2C, starts listening at assigned address
    TinyWireS.onRequest(requestEvent); // adds onRequest event listener to requestEvent
    
    pinMode(LEDPin, OUTPUT); // sets LEDPin to OUTPUT mode (INPUT mode is default)
    digitalWrite(LEDPin, LOW); // sets LEDPin to be off
}

void loop() {
    /**
     * This is the only way we can detect stop condition (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=984716&sid=82e9dc7299a8243b86cf7969dd41b5b5#984716)
     * it needs to be called in a very tight loop in order not to miss any (REMINDER: Do *not* use delay() anywhere, use tws_delay() instead).
     * It will call the function registered via TinyWireS.onReceive(); if there is data in the buffer on stop.
     */
    TinyWireS_stop_check();

    val = analogRead(analogPin); // read the input pin
    val = map(val, 0, 1023, 0, 255); // maps analog  value from 0-1023 to 0-255

    i2c_regs[0] = { val }; // stores value in i2c register to be sent on request
    
    if(val < 200) {
        digitalWrite(LEDPin,HIGH); // turn on LED if it is environment dark
    } else {
        digitalWrite(LEDPin,LOW); // turn off LED if it is environment light
    }
}