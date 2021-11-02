#ifndef MANUAL
#define MANUAL
#include <arduino.h>
#include "komdat.h"
#include "variabel.h"
#include "calculation.h"

//menggerakan servo mode manual
int moveManual(String command)
{	
    //mengubah nilai float menjadi int
    Serial.println("move");
  	int result = command.toInt();
  	controlMotor(result);
    // commandMove = "NaN";
    return result;
}

//mengontrol lampu secara manual
String relayManual(float valPzem, int manualLampu1, int manualLampu2)
{
	relay dataRelay;
	//lampu 1
	if (manualLampu1 == 1){
        dataRelay.lamp1 = 1;
        lampu1Control(true);
    }else{
        dataRelay.lamp1 = 0;
        lampu1Control(false);
    }
    //lampu2
    if (manualLampu2 == 1){
        dataRelay.lamp2 = 1;
        lampu2Control(true);
    }else{
        dataRelay.lamp2 = 0;
        lampu2Control(false);
    }
    //ketika konsumsi energi pada smartlight melebihi 0.11kWh maka sumber AC akan di alihkan ke PLC
    //jika tidak maka sumber AC tetap akan diambil dari inverter
	if (valPzem >= 0.11){
        dataRelay.sAC = 0;
        relaySumberAC(false);
    }else{
        dataRelay.sAC = 1;
        relaySumberAC(true);
    }	
    relayData = String(dataRelay.lamp1) + String(dataRelay.lamp2) + String(dataRelay.sAC);
    return relayData;
}

#endif
