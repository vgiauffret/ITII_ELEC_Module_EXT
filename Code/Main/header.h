// Include library
// 
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
// OLED library
#include "SH1106Wire.h"   // legacy: #include "SH1106.h"




//Definition des PINOUT
//#define MASSE_I2C_SCL   //IO
//#define MASSE_I2C_SDA   //IO
#define OLED_I2C_SCL 16  //IO16
#define OLED_I2C_SDA 17  //IO17
#define BP_NEXT  12	//IO12 Pin 14
#define BP_VALID 2 	//IO2  Pin 24



//Fonction qui passe en parametre l'adresse I2C et les pin de connexions
SH1106Wire display(0x3c, OLED_I2C_SDA, OLED_I2C_SCL);     // ADDRESS, SDA, SCL



#define TouchDelay 1000 //Temps entre deux appuie sur le bouton
typedef void (*Demo)(void);

char* Menu[]={"Visite","Sleep","Sirop   50/50","Sirop   70/30","Candy", "Mesure seule"};
int touchValue;
int counter=0;

