#ifndef SENSOR
#define SENSOR

#include <arduino.h>
#include "config.h"
#include "variabel.h"
#include "aktuator.h"

//Pembacaan arus panel surya
float getArus()
{
  float current;
  float rawVoltage = analogRead(pinArduino.arusPanel);
  float voltage = (rawVoltage / 1023) * 5000;
  return current = (voltage - ACSOFSET) / MVPERAMP;
}

voltageData getTegangan()
{
  voltageData vdata;
  float Volt1 = analogRead(pinArduino.voltageBaterai); 
  vdata.baterai = ((Volt1 * 0.00489) * 5);
  float Volt2 = analogRead(pinArduino.voltagePanelSurya);
  vdata.panelSurya = ((Volt2 * 0.00489) * 5);
  return vdata;
}

//pembacaan energy sensor pzem
pzemData pzemRead()
{
	pzemData dataPZEM;
	dataPZEM.Energy = pzem.energy();
	return dataPZEM;
}

#endif
