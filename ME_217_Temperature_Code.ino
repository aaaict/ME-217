#include <OneWire.h>
#include <DallasTemperature.h>
#include <ezButton.h>


#define LOOP_STATE_STOPPED 0
#define LOOP_STATE_STARTED 1
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);	
DallasTemperature sensors(&oneWire);
ezButton button(3);

int deviceCount = 0;
float tempC;
float tempF;

float Sensor_1;
float Sensor_2;
float Sensor_3;

int loopState = LOOP_STATE_STOPPED;

void setup(void)
{
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  sensors.begin();	
  Serial.begin(9600);
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
}

void loop(){ 
  button.loop(); //

  if (button.isPressed()) {
    if (loopState == LOOP_STATE_STOPPED)
      loopState = LOOP_STATE_STARTED;
    else
      loopState = LOOP_STATE_STOPPED;
  }

  // if (loopState == LOOP_STATE_STOPPED) {
  //   delay(1000);
  // }
  
  if (loopState == LOOP_STATE_STARTED) {
  // Send command to all the sensors for temperature conversion
    sensors.requestTemperatures(); 
    // Display temperature from each sensor
      Sensor_1 = (DallasTemperature::toFahrenheit(sensors.getTempCByIndex(0)));
      Sensor_2 = (DallasTemperature::toFahrenheit(sensors.getTempCByIndex(1)));
      Sensor_3 = (DallasTemperature::toFahrenheit(sensors.getTempCByIndex(2)));

    Serial.print("Top_Sensor:");
    Serial.print(Sensor_1);
    Serial.print(",");
    Serial.print("Middle_Sensor:");
    Serial.print(Sensor_2);
    Serial.print(",");
    Serial.print("Base_Sensor:");
    Serial.print(Sensor_3);
    Serial.println("");
     delay(1000);
    
  }
}
