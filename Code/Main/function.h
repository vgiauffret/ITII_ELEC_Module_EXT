#include "header.h"


void drawProgressBar() {
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, String(progress) + "%");
}

void Accueil() {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawStringMaxWidth(10, 10, 128,"Projet Ruche Module Externe");
    display.display();
    delay(2000);
    //drawProgressBar();
}


int MenuDefile() {
    
    int indice=0;
    Serial.println("Je suis au menu");
    // clear the display
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(33, 10, 128,Menu[indice]);
    // write the buffer to the display
    display.display();
    while(1) //touchRead(BP_VALID)>30
	{
	  	touchValue = touchRead(BP_NEXT);
		Serial.print("BP Next : ");
		Serial.println(touchValue);

		Serial.print("BP Valid : ");
		Serial.println(touchRead(BP_VALID));
	    		if(touchValue < 35 )
				{
				indice++;
				delay(TouchDelay);
				}
		// clear the display
		display.clear();
		display.setFont(ArialMT_Plain_24);
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.drawStringMaxWidth(33, 10, 128,Menu[indice]);
		// write the buffer to the display
		display.display();
	}
   //drawProgressBar();
return indice;
}

void Action(int CHOIX)
{

switch (CHOIX)
   {
	case 0 : //Visite
	{
	
	break;
	}
	case 1 : //Sleep
	{

	break;
	}
	case 2 : //Sirop   50/50
	{

	break;
	}
	case 3 : //Sirop   70/30
	{

	break;
	}
	case 4 : //Candy
	{

	break;
	}
	case 5 : //Mesure seule
	{

	break;
	}
	default :
	{

	break;	
	}
   }
}




void drawImageDemo() {
    // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
    // on how to create xbm files
    //display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}
