/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/



/*  Sharp Optical Dust Sensor GP2Y1010AU0F

출처: https://bbangpan.tistory.com/51 [빵판닷컴 (bbangpan.com)]

*/

#ifndef rover_PM2_5_H
#define rover_PM2_5_H


#define SAMPLING_TIME 280
#define DELTA_TIME 40
#define SLEEP_TIME 9680
class RoverPM2_5{
  public:
    RoverPM2_5(int Vo, int V_LED);
    void begin();
    float calulatePM2_5();
  
  private:
    float _dustDensity ;
    int _Vo;
    int _V_LED;
    long _last_millis;


};





#endif
