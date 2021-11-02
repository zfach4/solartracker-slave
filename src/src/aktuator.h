#ifndef AKTUATOR
#define AKTUATOR

#include <arduino.h>
#include "config.h"
#include <Servo.h>
//#include "variabel.h"

//controll relay lampu 1
void lampu1Control(boolean command)
{
    digitalWrite(pinArduino.lampu1, command);
}

//controll relay lampu 2
void lampu2Control(boolean command)
{
    digitalWrite(pinArduino.lampu2, command);
}

//controll relay sumber AC
void relaySumberAC(boolean command)
{
    digitalWrite(pinArduino.sumberAC, command);
}


//module class
Servo motorP;

// //baca posisi derajat servo saat ini
// int getDegreeMotor()
// {
//     return motorP.read();
// }

// //kontrol motor
// void controlMotor(float sudut)
// { 
//   motorP.attach(12);
//   //mebatasi input sudut yang bisa dicapai oleh servo, karena memakai servo standard 0-180 derajat
//   sudut = constrain(sudut, 0, 180);

//   //ambil sudut servo saat ini
//   int pos = motorP.read();
  
//  //jika input variabel sudut lebih besar dari sudut servo saat ini
//   if (sudut > pos){
//   	//tambahkan derajat servo sebesar 1 derajat sampai nilai variabel sudut dan pos sama
//     for (pos; pos <= sudut; pos += 1) {             
//     motorP.write(pos);
//     delay(20);                       
//      }
//    }
//  //jika input variabel sudut lebih kecil dari sudut servo saat ini
//  if (sudut < pos){
//   	//kurangi derajat servo sebesar 1 derajat sampai nilai variabel sudut dan pos sama  
//     for (pos; pos >= sudut; pos -= 1) { 
//     motorP.write(pos);
//     delay(20);                       
//      }
//    }
//    motorP.detach();
// }

//baca posisi derajat servo saat ini
int getDegreeMotor()
{
    int degreeServo = motorP.read();
    int testEroor;
    if(flagErorr == false){
      testEroor = sudutErorr;
    
    }else if (flagErorr == true){
        testEroor = sudutErorr - 2;
        //flagErorr = false;    
    }
    //delay(100);
    // Serial.print("suduterorr return : ");
    // Serial.println(testEroor);
    return testEroor;
}

//kontrol motor
void controlMotor(float sudut)
{ 
  motorP.attach(12);
  if (sudut > 25 && sudut < 176){
    sudutErorr = sudut + 2;
    flagErorr = true;
    // Serial.println("true");
  }else{
    sudutErorr = sudut;
    flagErorr = false;
    // Serial.println("false ");
  }
  
  // Serial.print("suduterorr : ");
  // Serial.println(sudutErorr);

  sudut = sudutErorr;

  //mebatasi input sudut yang bisa dicapai oleh servo, karena memakai servo 0-180 derajat
  sudut = constrain(sudut, 0, 184);
  //ambil sudut servo saat ini
  int pos = motorP.read();

 //jika input variabel sudut lebih besar dari sudut servo saat ini
  if (sudut > pos){
  	//tambahkan derajat servo sebesar 1 derajat sampai nilai variabel sudut dan pos sama
    for (pos; pos <= sudut; pos += 1) {             
    motorP.write(pos);
    delay(100);                       
     }
   }
 
 //25
 //15
 //jika input variabel sudut lebih kecil dari sudut servo saat ini
 if (sudut < pos){
 	//kurangi derajat servo sebesar 1 derajat sampai nilai variabel sudut dan pos sama  
    for (pos; pos >= sudut; pos -= 1) { 
    motorP.write(pos);
    delay(100);                       
     }
   }
   //pos = 0;
   motorP.detach();
}


// //control posisi sudut
// void tuningPosition(int inputPosition, int servoPosition)
// {
//    int controlDeg = servoPosition;
//    while (controlDeg != inputPosition)
//    {
//        int currentServoPosition = getDegreeMotor();
//        if (currentServoPosition < inputPosition)
//        {
//            controlDeg += MOVESERVO;
//        }
//        else if (currentServoPosition > inputPosition)
//        {
//            controlDeg -= MOVESERVO;
//        }
//        else
//        {
//            break;
//        }
//        controlMotor(controlDeg);
//        delay(100);
//    }
// }

#endif
