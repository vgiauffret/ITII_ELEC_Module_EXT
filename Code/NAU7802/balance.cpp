#include <Wire.h>
#include <EEPROM.h> //Needed to record user settings
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_NAU8702

//EEPROM locations to store 4-byte variables
#define LOCATION_CALIBRATION_FACTOR 0 //Float, requires 4 bytes of EEPROM
#define LOCATION_ZERO_OFFSET 10 //Must be more than 4 away from previous spot. Long, requires 4 bytes of EEPROM
//Create an array to take average of weights. This helps smooth out jitter.
#define AVG_SIZE 4

NAU7802 myScale; //Create instance of the NAU7802 class
float weight;
//Function's headers
void CalibrateScale(void);
void readSystemSettings(void);
void recordSystemSettings(void);

bool settingsDetected = false; //Used to prompt user to calibrate their scale

float avgWeights[AVG_SIZE];
byte avgWeightSpot = 0;


void setup(){
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000); //Qwiic Scale is capable of running at 400kHz if desired
  
  if (myScale.begin() == false)
  {
    Serial.println("balance non detecte");
  }
  //CalibrateScale();
  readSystemSettings();
    
  //myScale.setSampleRate(NAU7802_SPS_320); //Increase to max sample rate
  //myScale.calibrateAFE(); //Re-cal analog front end when we change gain, sample rate, or channel 

}


void loop(){

 
  if(myScale.available()==true){
    Serial.print("reading = ");
    float reading = myScale.getReading();
  
    weight = reading*(0.138/(91556 - 78585)) + 78585;
    Serial.println(reading);
    Serial.print("weight = ");
    Serial.println(weight)
    
    //float currentWeight = myScale.getWeight();
    //Serial.print("Weight = ");
    //Serial.println(currentWeight);
    //Serial.print("Average weight = ");
    //Serial.println(myScale.getAverage(100));
  }
  
 delay(500);
  
}

void CalibrateScale(void){

  Serial.println("Scale Calibration...");
  
  myScale.calculateZeroOffset(64); //Zero or Tare the scale. Average over 64 readings.

  //myScale.calculateCalibrationFactor(weightOnScale, 64); //Tell the library how much weight is currently on it

  myScale.setZeroOffset(float(219800));
  myScale.setCalibrationFactor(float((30900-219800)/178));
  
  recordSystemSettings();

  Serial.println("Calibration done !");
}

void readSystemSettings(void)
{
  float settingCalibrationFactor; //Value used to convert the load cell reading to lbs or kg
  long settingZeroOffset; //Zero value that is found when scale is tared

  //Look up the calibration factor
  EEPROM.get(LOCATION_CALIBRATION_FACTOR, settingCalibrationFactor);
  if (settingCalibrationFactor == 0xFFFFFFFF)
  {
    settingCalibrationFactor = 0; //Default to 0
    EEPROM.put(LOCATION_CALIBRATION_FACTOR, settingCalibrationFactor);
  }

  //Look up the zero tare point
  EEPROM.get(LOCATION_ZERO_OFFSET, settingZeroOffset);
  if (settingZeroOffset == 0xFFFFFFFF)
  {
    settingZeroOffset = 1000L; //Default to 1000 so we don't get inf
    EEPROM.put(LOCATION_ZERO_OFFSET, settingZeroOffset);
  }

  //Pass these values to the library
  myScale.setCalibrationFactor(settingCalibrationFactor);
  myScale.setZeroOffset(settingZeroOffset);

  settingsDetected = true; //Assume for the moment that there are good cal values
  if (settingCalibrationFactor < 0.1 || settingZeroOffset == 1000)
    settingsDetected = false; //Defaults detected. Prompt user to cal scale.
}

void recordSystemSettings(void)
{
  //Get various values from the library and commit them to NVM
  EEPROM.put(LOCATION_CALIBRATION_FACTOR, myScale.getCalibrationFactor());
  EEPROM.put(LOCATION_ZERO_OFFSET, myScale.getZeroOffset());
}
