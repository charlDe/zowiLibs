#ifndef Zowi_h
#define Zowi_h

#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>
//#include <ZowiSerialCommand.h>
#include <US.h>
#include <LedMatrix.h>
#include <BatReader.h>

#include "Zowi_mouths.h"
#include "Zowi_sounds.h"
#include "Zowi_gestures.h"


//-- Constants
#define FORWARD     1
#define BACKWARD    -1
#define LEFT        1
#define RIGHT       -1
#define SMALL       5
#define MEDIUM      15
#define BIG         30

#define PIN_Buzzer  10
#define PIN_Trigger 8
#define PIN_Echo    9
#define PIN_NoiseSensor A6


class Zowi
{
  public:

    //Zowi (int YL=2, int YR=3, int RL=4, int RR=5, int NoiseSensor = A6, int Buzzer = 10, int SecondButton=6, int ThirdButton=7, int USTrigger=8, int USEcho=9,bool load_calibration=true);
    void init(int YL, int YR, int RL, int RR, bool load_calibration=true, int NoiseSensor=PIN_NoiseSensor, int Buzzer=PIN_Buzzer, int USTrigger=PIN_Trigger, int USEcho=PIN_Echo);

    void setTrims(int YL, int YR, int RL, int RR);
    void saveTrimsOnEEPROM();

    //-- Motion functions
    void moveServos(int time, int  servo_target[]);
    void oscillateServos(int A[4], int O[4], int T, double phase_diff[4], float cycle);
    
    void home();
    void homeold();

    void jump(float steps=1, int T = 2000);

    void walk(float steps=4, int T=1000, int dir = FORWARD);
    void turn(float steps=4, int T=2000, int dir = LEFT);
    void bend (int steps=1, int T=1400, int dir=LEFT);
    void shakeLeg (int steps=1, int T = 2000, int dir=RIGHT);

    void updown(float steps=1, int T=1000, int h = 20);
    void swing(float steps=1, int T=1000, int h=20);
    void tiptoeSwing(float steps=1, int T=900, int h=20);
    void jitter(float steps=1, int T=500, int h=20);
    void ascendingTurn(float steps=1, int T=900, int h=20);

    void moonwalker(float steps=1, int T=900, int h=20, int dir=LEFT);
    void crusaito(float steps=1, int T=900, int h=20, int dir=FORWARD);
    void flapping(float steps=1, int T=1000, int h=20, int dir=FORWARD);

    //-- US
    float getDistance();

    //-- Noise Sensor
    int getNoise();

    //-- Battery
    double getBatteryLevel();
    double getBatteryVoltage();
    
    //-- Mouth
    void putMouth(unsigned long int mouth, bool predefined = true);
    void putAnimationMouth(unsigned long int anim, int index);
    void clearMouth();

    //-- Sounds
    void _tone (float noteFrequency, long noteDuration, int silentDuration);
    void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    void sing(int songName);

    //-- Gestures
    void playGesture(int gesture);



 
  private:
    
    //ZowiSerialCommand SCmd;  // SerialCommand object
    LedMatrix ledmatrix;
    BatReader battery;
    Oscillator servo[4];
    US us;
    
    int servo_trim[4];
    int servo_position[4];
    int pinBuzzer;
    int pinNoiseSensor;
    unsigned long final_time;
    unsigned long partial_time;
    float increment[4];

    unsigned long int getMouthShape(int number);
    unsigned long int getAnimShape(int anim, int index);
    void _execute(int A[4], int O[4], int T, double phase_diff[4], float steps);

};

#endif


