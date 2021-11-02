#include <Servo.h>
#include "src/config.h"
#include "src/sensor.h"
#include "src/komdat.h"
#include "src/calculation.h"
#include "src/otomatis.h"
#include "src/manual.h"
#include "src/aktuator.h"
#include "src/sleep.h"


void setup()
{   
    /* memulai komunikasi i2c sebagai slave 
    dan men-set function untuk keadaan jika menerima data perintah dari master dan jika ada permintaan data dari master*/
    komdatInit(i2cAdress);

    //mengatur kecepatan komunikasi serial dengan baudrate 9600
    Serial.begin(9600);

    //menginisialisasi input/output pada Arduino Mega 2560
    pinInit();
    //motorP.attach(12);
}

void loop()
{
    //mengambil data tegangan
    voltageData resVoltage = getTegangan();
    //mengambil data arus
    float resArus = getArus();
    //mengambil data energi (kWh)
    pzemData resPzem = pzemRead();
    //mengambil data waktu
    timeData resTime = getNowTime();
    //mengambil data azimuth matahari yang berasal dari algoritma posisi matahari
    resKoordinat = getKoordinat(resTime);
    //mengkonversi azimuth matahari ke refrensi sudut servo
    int AzimuthToDegreeValue = azimuthToDegree(resKoordinat.azimuth);
    //domain control otomatis dengan persyaratan jam
    if (getMode() == "0" && resTime.jam >= 6 && resTime.jam <= 23)
    {
        //control relay untuk on/off lampu secara otomatis
        String resRelay = relayOtomatis(resTime.jam, resPzem.Energy);
        //berfungsi untuk meng-enablekan fungsi reset nilai pzem yang akan dlakukan saat diatas jam 16 nanti
        flagPzemRst = true;
        //menggerakan motor servo secara otomatis berdasarkan inputan hasil konversi nilai azimuth matahari ke refrensi sudut servo 
        if(flagMoveAzimuth == true){
        moveBasedAzimuth(AzimuthToDegreeValue);
        Serial.println("active");
        Serial.println("nice");
        flagMoveAzimuth = false;
        }
        // //membaca posisi motor servo saat ini
        // int CurrentServoPosition = getDegreeMotor();
        // //control posisi akhir motor servo agar sesuai dengan inputan hasil konversi nilai azimuth matahari ke refrensi sudut servo
        // tuningPosition(AzimuthToDegreeValue, CurrentServoPosition);
        //membaca posisi akhir motor servo
        int ServoLastDegreeValue = getDegreeMotor();
        //mengabungkan data-data hasil eksekusi program pada slave
        setDataKm(resVoltage, resArus, resPzem, resRelay, resKoordinat, AzimuthToDegreeValue, ServoLastDegreeValue);
        //sleep mode 
        //sleepMode();
    }
    //domain control manual
    else if (getMode() == "1")
    {   
        Serial.println("start");
        //mereset nilai energi hasil sensing dari sensor pzem (dilakukan satu kali pada jam 17)
         if (resTime.jam == 17 && flagPzemRst == true){
            pzem.resetEnergy();
            flagPzemRst = false; 
          }
        //control relay untuk on/off lampu secara manual
        String resRelay = relayManual(resPzem.Energy, ManualLampu1, ManualLampu2);
        // if (commandMove != "NaN"){
        //       Serial.println("masuk");
              Serial.println(commandMove);
              //mengerakan motor servo secara manual berdasarkan inputan yang berasal dari user
              manualDegreeValue = moveManual(commandMove);
              // //membaca posisi motor servo saat ini
              // int CurrentServoPosition = getDegreeMotor();
              // //control posisi akhir motor servo agar sesuai dengan dengan inputan yang berasal dari user
              // tuningPosition(manualDegreeValue, CurrentServoPosition);
        // }
        //membaca posisi akhir motor servo
        int ServoLastDegreeValue = getDegreeMotor();
        //mengabungkan data-data hasil eksekusi program pada slave
        setDataKm(resVoltage, resArus, resPzem, resRelay, resKoordinat, AzimuthToDegreeValue, ServoLastDegreeValue);
        Serial.println("finish");
        //sleepMode();
    }
    //domain control otomatis tanpa persyaratan jam
    else if (getMode() == "0") 
    {     
         //mereset nilai energi hasil sensing dari sensor pzem (dilakukan satu kali pada jam 17)
         if (resTime.jam == 17 && flagPzemRst == true){
            pzem.resetEnergy();
            flagPzemRst = false; 
          }
        //control relay untuk on/off lampu secara otomatis
        String resRelay = relayOtomatis(resTime.jam, resPzem.Energy);
        //membaca posisi motor servo saat ini
        int ServoLastDegreeValue = getDegreeMotor();
        //posisikan motor servo ke posisi 90 derajat (dilakukan satu kali)
        if (ServoLastDegreeValue != 90){
            controlMotor(90);
        }
        // //membaca posisi motor servo saat ini
        // int CurrentServoPosition = getDegreeMotor();
        // //control posisi akhir motor servo agar sesuai dengan dengan inputan yang berasal dari user
        // tuningPosition(90, CurrentServoPosition);
        //membaca posisi akhir motor servo
        ServoLastDegreeValue = getDegreeMotor();
        //mengabungkan data-data hasil eksekusi program pada slave
        setDataKm(resVoltage, resArus, resPzem, resRelay, resKoordinat, AzimuthToDegreeValue, ServoLastDegreeValue);
      }
    delay(25);
}
