#ifndef KOMDAT
#define KOMDAT

#include <Wire.h>

//menyusun data
void setDataKm(voltageData vData, float aData, pzemData dPzem, String dRelay, krData kData, int ADV, int SLDV)
{
    Data1 = "*" +
                 String(vData.baterai) + ":" +
                 String(vData.panelSurya) + ":" +
                 String(aData) + ":" +
                 String(dPzem.Energy,3) + ":" +
                 String(dRelay) + "/";
                 
	Data2 = "*" +
                 String(kData.azimuth) + ":" +
                 String(ADV) + ":" +
                 String(SLDV) + "/";              
                 
}

//ketika ada request (permintaan data) dari master
void requestEvent()
{
	if (turn == 1){
		Wire.write(Data2.c_str());
		turn = 0;	
	}else if (turn == 0){
		Wire.write(Data1.c_str());
		turn += 1;
	}		
}

//ketika receive (menerima data perintah) dari master
void receiveEvent()
{
    while (Wire.available()){
        if (char(Wire.read()) == '*'){
            String pData[10];
            int sIndex = 0;
            boolean flagFinish = false;
            while (Wire.available()){
                char sRead = Wire.read();
                if (sRead == '/'){
                    flagFinish = sIndex == 9 ? true : false;
                    break;
                }else if (sRead == ':'){
                    sIndex++;
                    if (sIndex >= 10){
                        break;
                    }
                }else{
                    pData[sIndex].concat(sRead);
                }
            }
            if (flagFinish){
                mode = pData[0];
                commandMove = pData[1];
                jam = pData[2].toInt();
                menit = pData[3].toInt();
                detik = pData[4].toInt();
                hari = pData[5].toInt();
                bulan = pData[6].toInt();
                tahun = pData[7].toInt();
                ManualLampu1 = pData[8].toInt();
                ManualLampu2 = pData[9].toInt();
                flagMoveAzimuth = true;
            }
        }
    }
}

/* mulai komunikasi I2C dan men-set function ketika ada request (permintaan data) dari master dan 
ketika receive (menerima data perintah) dari master */
void komdatInit(int adr)
{
     Wire.begin(adr);
     Wire.onReceive(receiveEvent);
     Wire.onRequest(requestEvent);
}

//mengambil data mode
String getMode()
{
    return mode;
}

#endif
