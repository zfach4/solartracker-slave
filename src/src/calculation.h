#ifndef CALCULATION
#define CALCULATION

#include <arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "config.h"
#include "variabel.h"

//module class
RTC_DS1307 rtc;

//function untuk menghitung hari ke berapa dalam tahun ini
int calculateDayOfYear(int day, int month, int year)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // check jika tahun ini tahun kabisat
    if (year % 4 == 0){
        if (year % 100 != 0){
            daysInMonth[1] = 29;
        }else{
            if (year % 400 == 0){
                daysInMonth[1] = 29;
            }
        }
    }

	//menghitung hari ke berapa dalam tahun ini
    int doy = 0;
    for (int i = 0; i < month - 1; i++){
        doy += daysInMonth[i];
    }
    doy += day;
    return doy;
}

//perhitungan algoritma posisi matahari untuk mendapatkan nilai azimuth matahari
krData getKoordinat(timeData dTime)
{
    //input data perintah berupa waktu dari master
    int hari = dTime.hari;
    int bulan = dTime.bulan;
    int tahun = dTime.tahun;
    float menit = dTime.menit;
	float detik = dTime.detik;
    float jam = dTime.jam;
    
    //perhitungan algoritma posisi matahari
    float LT = jam + (menit/60) + (detik/3600);
    float LSTM = 15 * GMT;
    float d = calculateDayOfYear(hari, bulan, tahun);
    float B = ((d - 81) * 360) / 365;
    float EoT = 9.87 * sin((2 * 3.14) * 2 * B / 360) - 7.52 * cos((2 * 3.14) * B / 360) 
                - 1.5 * sin((2 * 3.14) * B / 360);
    float TC = 4 * (LONGITUDE - LSTM) + EoT;
    float LST = (LT + (TC / 60));
    int HRA = 15 * (LST - 12);

    float deklinasi = 23.45 * sin((2 * 3.14) * B / 360);

    krData koorData;
    koorData.elevasi = asin((sin((2 * 3.14) * deklinasi / 360) * sin((2 * 3.14) * LATITUDE / 360)) 
                       + (cos((2 * 3.14) * deklinasi / 360) * cos((2 * 3.14) * LATITUDE / 360) 
                       * cos((2 * 3.14) * HRA / 360))) * 180 / 3.14;

    //Azimuth
    koorData.azimuth = acos(((sin((2 * 3.14) * deklinasi / 360) * cos((2 * 3.14) * LATITUDE / 360)) 
                       - (cos((2 * 3.14) * deklinasi / 360) * sin((2 * 3.14) * LATITUDE / 360) 
                       * cos((2 * 3.14) * HRA / 360))) / cos((2 * 3.14) * koorData.elevasi / 360)) * 180 / 3.14;
    koorData.azimuth = jam < 12 ? koorData.azimuth : 360 - koorData.azimuth;
    return koorData;
}

//mengkonversi refrensi azimuth matahari ke refrensi sudut servo
//sudut 0 matahari ada disebelah utara sedangkan sudut 0 servo ada ditimur
int azimuthToDegree(int value)
{
    int result;
    if (value <= 180)
    {
        if (value <=90){
            result = map(value, 90, 0, 0, 90);
        }else{
            result = map(value, 180, 90, 270, 360);
        }
    }
    else
    {
        if (value >=270){
            result = map(value, 360, 270, 90, 180);
        }else{
            result = map(value, 270, 180, 180, 270);
        }
    }
    return result;
}

//mengambil data waktu
timeData getNowTime()
{
    timeData valTime;
    valTime.tahun = tahun;
    valTime.bulan = bulan;
    valTime.hari = hari;
    valTime.jam = jam;
    valTime.menit = menit;
    valTime.detik = detik;
    return valTime;
}

#endif
