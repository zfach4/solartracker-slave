#ifndef OTOMATIS
#define OTOMATIS

#include <arduino.h>
#include "aktuator.h"
#include "sensor.h"
#include "variabel.h"
#include "calculation.h"

//menggerakan servo mode otomatis
void moveBasedAzimuth(int degreeValue)
{
    controlMotor(degreeValue);
}

//mengontrol lampu secara otomatis
String relayOtomatis(int valJam, float valPzem)
{
	relay dataRelay;	
	//lampu 1 akan menyala ketika jam 18 sampai kurang dari jam 22
	if (valJam >= 18 && valJam < 22){
        lampu1Control(true);
        dataRelay.lamp1 = 1;
    }else{
        lampu1Control(false);
        dataRelay.lamp1 = 0;
    }
    //lampu 2 akan menyala ketika jam 18 sampai kurang dari jam 23
    if (valJam >= 18 && valJam < 23)
    {
        lampu2Control(true);
        dataRelay.lamp2 = 1;
    }else{
        lampu2Control(false);
        dataRelay.lamp2 = 0;
    }
    //ketika konsumsi energi pada smartlight melebihi 0.11kWh maka sumber AC akan di alihkan ke PLC
    //jika tidak maka sumber AC tetap akan diambil dari inverter
	if (valPzem >= 0.11){
        relaySumberAC(false);
        dataRelay.sAC = 0;
    }else{
        relaySumberAC(true);
        dataRelay.sAC = 1;
    } 
    relayData = String(dataRelay.lamp1) + String(dataRelay.lamp2) + String(dataRelay.sAC); 
    return relayData;
}

#endif
