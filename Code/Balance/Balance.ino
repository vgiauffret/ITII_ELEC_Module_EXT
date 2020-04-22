#include <Wire.h>
#include <EEPROM.h> //Needed to record user settings
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_NAU8702

NAU7802 myScale; //Create instance of the NAU7802 class

//EEPROM locations to store 4-byte variables
#define LOCATION_CALIBRATION_FACTOR 0 //Float, requires 4 bytes of EEPROM
#define LOCATION_ZERO_OFFSET 10 //Must be more than 4 away from previous spot. Long, requires 4 bytes of EEPROM
#define EEPROM_SIZE 128
#define LOCATION_CODE 15
#define CODE 123456789

bool settingsDetected = false; //Used to prompt user to calibrate their scale
int flag =0;

int read_eeprom_code(void);
void recordSystemSettings(void);
void readSystemSettings(void);
void calibrateScale(void);

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000); //Qwiic Scale is capable of running at 400kHz if desired

  if (!EEPROM.begin(EEPROM_SIZE)) 
  {
    Serial.println("Failed to initialise EEPROM");
  }
  flag = read_eeprom_code();
  if (myScale.begin() == false)
  {
    Serial.println("Scale not detected. Please check wiring. Freezing...");
    while (1);
  }
  Serial.println("Scale detected!");

  readSystemSettings(); //Load zeroOffset and calibrationFactor from EEPROM

  myScale.setSampleRate(NAU7802_SPS_320); //Increase to max sample rate
  myScale.calibrateAFE(); //Re-cal analog front end when we change gain, sample rate, or channel 

  Serial.print("Zero offset: ");
  Serial.println(myScale.getZeroOffset());
  Serial.print("Calibration factor: ");
  Serial.println(myScale.getCalibrationFactor());

  if (flag != 123456789)
  {
  settingsDetected = false;
  }
}

void loop()
{   
  if (myScale.available() == true)
  {
    float currentWeight = myScale.getWeight(false,64);

    Serial.print("\tWeight: ");
    Serial.print(myScale.getWeight(false,64), 3); //Print 3 decimal places

    if(settingsDetected == false) //Tester le code dans l'eeprom
    {
      Serial.print("\tScale not calibrated.");
      calibrateScale();
    }
    Serial.println();
  }
}

int read_eeprom_code() 
{
  int result = 0;
  Serial.println("Lecture de l'eeprom !");
  EEPROM.get(LOCATION_CODE, result);
  Serial.println(result);
  return result;
}

//Gives user the ability to set a known weight on the scale and calculate a calibration factor
void calibrateScale(void)
{
  Serial.println();
  Serial.println();
  Serial.println(F("Scale calibration"));

  Serial.println(F("Ne poser aucun poid sur la balance. Appuyer sur une touche lorsque vous etes pret."));
  while (Serial.available()) Serial.read(); //Clear anything in RX buffer
  while (Serial.available() == 0) delay(10); //Wait for user to press key

  myScale.calculateZeroOffset(128); //Zero or Tare the scale. Average over 64 readings.
  Serial.print(F("New zero offset: "));
  Serial.println(myScale.getZeroOffset());

  Serial.println(F("Placer un poid connu sur la balance. Appuyer sur une touche lorsque le poid est positionné et stable."));
  while (Serial.available()) Serial.read(); //Clear anything in RX buffer
  while (Serial.available() == 0) delay(10); //Wait for user to press key

  Serial.print(F("Entrez la valuer du poid, sans unités, Qui se trouve sur la balance :"));
  while (Serial.available()) Serial.read(); //Clear anything in RX buffer
  while (Serial.available() == 0) delay(10); //Wait for user to press key

  //Read user input
  float weightOnScale = Serial.parseFloat();
  Serial.println();

  myScale.calculateCalibrationFactor(weightOnScale, 128); //Tell the library how much weight is currently on it
 
  settingsDetected = true;

  recordSystemSettings(); //Commit these values to EEPROM

  readSystemSettings(); //Load zeroOffset and calibrationFactor from EEPROM

  Serial.print("Zero offset: ");
  Serial.println(myScale.getZeroOffset());
  Serial.print("Calibration factor: ");
  Serial.println(myScale.getCalibrationFactor());
}

//Record the current system settings to EEPROM
void recordSystemSettings(void)
{
  //Get various values from the library and commit them to NVM
  EEPROM.put(LOCATION_CALIBRATION_FACTOR, myScale.getCalibrationFactor());
  EEPROM.put(LOCATION_ZERO_OFFSET, myScale.getZeroOffset());
  EEPROM.put(LOCATION_CODE, CODE);
  EEPROM.commit();
  Serial.println("On vient d'écrire dans l'Eeprom !");
}

//Reads the current system settings from EEPROM
//If anything looks weird, reset setting to default value
void readSystemSettings(void)
{
  float settingCalibrationFactor=0; //Value used to convert the load cell reading to lbs or kg
  long settingZeroOffset=0; //Zero value that is found when scale is tared
  
  read_eeprom_code(); //Lecture du Code dans l'eeprom

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
  {
    settingsDetected = false; //Defaults detected. Prompt user to cal scale.
  }
}
