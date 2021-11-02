#ifndef VARIABEL
#define VARIABEL

//error
int sudutErorr;
bool flagErorr;

//move azimuth
bool flagMoveAzimuth;

//Const Variable
const float MVPERAMP = 185;
const float ACSOFSET = 2500;
const float GMT = 7;
const float LONGITUDE = 107.6211;
const float LATITUDE = -6.8775;
const int MAXDEFERENCE = 10;
const int MOVESERVO = 1;

//Variable Global
int turn;
String Data1 = "0:0:0:0:0/";
String Data2 = "0:0:0/";
String mode = "0";
String commandMove = "0";
int manualDegreeValue;
int ManualLampu1 = 0;
int ManualLampu2 = 0;
int jam;
int menit;
int detik;
int hari;
int bulan;
int tahun;
int dtjam;

//int servoAzimuthValue;
float PzemVoltage = 0;
float PzemCurrent = 0;
float PzemPower = 0;
float PzemEnergy = 0;
bool flagPzemRst = false;
String relayData; 

//Struct Global
struct voltageData
{
    float baterai = 0;
    float panelSurya = 0;
};

struct pzemData
{
    float Power = 0;
    float Energy = 0;
    float Voltage = 0;
    float Current = 0;
};

struct krData
{
    float elevasi = 0;
    float azimuth = 0;
    float derajat = 0;
} resKoordinat;

struct timeData
{
    int jam = 0;
    int menit = 0;
    int detik = 0;
    int tahun = 0;
    int bulan = 0;
    int hari = 0;
};

struct relay
{
	int lamp1 = 0;
	int lamp2 = 0;
	int sAC;
};

#endif
