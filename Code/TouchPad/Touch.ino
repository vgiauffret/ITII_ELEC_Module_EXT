/* 
 *  Copyright (c) 2018, circuits4you.com
 *  All rights reserved.
 * 
 * ESP32 Capacitive Touch Example
 */

byte touch;
//======================================================================
//            Setup
//======================================================================
void setup() {
    Serial.begin(115200);
    
    touch_pad_filter_start(T0);
    touch_pad_set_filter_period(T0);
}

//======================================================================
//            Loop
//======================================================================
void loop() {  
    touch= touchRead(T0); 
    touch = touch;   
    
    delay(100);
    if (touch <20 && touch > 0)
    {
    Serial.println("On appuie");  
    }
    else
    {
      Serial.println ("On relache");
    }
    }
    
}
