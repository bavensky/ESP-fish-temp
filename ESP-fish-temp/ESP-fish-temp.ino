#include <ESPert.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13

ESPert espert;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
DeviceAddress insideThermometer;

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void printTemperature(DeviceAddress deviceAddress)
{

}


void setup() {
  espert.init();
  espert.oled.init();
  espert.dht.init();

  DS18B20.begin();
  Serial.print("Found ");
  Serial.print(DS18B20.getDeviceCount(), DEC);
  Serial.println(" devices.");
  Serial.print("Parasite power is: ");
  if (DS18B20.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  if (!DS18B20.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  DS18B20.setResolution(insideThermometer, 9);
  Serial.print("Device 0 Resolution: ");
  Serial.print(DS18B20.getResolution(insideThermometer), DEC);
  Serial.println();
  delay(2000);
  espert.oled.clear();
}

void loop() {
  DS18B20.requestTemperatures();
  bool isFarenheit = false;
  float t = espert.dht.getTemperature(isFarenheit);
  float h = espert.dht.getHumidity();

  float tempC = DS18B20.getTempC(insideThermometer);
//  Serial.print("Temp C: ");
//  Serial.println(tempC);
//  Serial.print("Temp: ");
//  Serial.print(t);
//  Serial.print(" Humid: ");
//  Serial.println(h);

  espert.oled.setTextSize(2);
  espert.oled.setTextColor(ESPERT_WHITE);
  espert.oled.setCursor(0, 0);
  espert.oled.println("Room");
  espert.oled.print("Temperature: ");
  espert.oled.print(t);
  espert.oled.print(" C ");
  espert.oled.print("Humidity:");
  espert.oled.print(h);
  espert.oled.println(" %RH ");
  espert.oled.println("");
  espert.oled.println("Water");
  espert.oled.print("Temp : ");
  espert.oled.print(tempC);
  espert.oled.println(" C ");
  espert.oled.update();

  delay(2000);
  espert.oled.clear();
}
