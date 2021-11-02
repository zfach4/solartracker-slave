#ifndef CONFIG
#define CONFIG
#include <arduino.h>
#include "PZEM/PZEM004Tv30.h"

//define adress
#define i2cAdress 2

//Pin Arduino
struct pArduino
{
    byte voltagePanelSurya = A1;
    byte voltageBaterai = A2;
    byte arusPanel = A0;
    byte ldrLeft = A12;
    byte ldrRight = A13;
    const int sumberAC =  8;
    const int lampu1 =  10;
    const int lampu2 =  11;
} pinArduino;

//module class
PZEM004Tv30 pzem(50,51);

void pinInit()
{
    pinMode(pinArduino.sumberAC, OUTPUT);
    pinMode(pinArduino.lampu1, OUTPUT);
    pinMode(pinArduino.lampu2, OUTPUT);
}

#endif
