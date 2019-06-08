#ifndef rover_PM2_5_H
#define rover_PM2_5_H

class rover_PM2_5{
  public:
    PM2_5(int Vo, int V_LED);
    void rover_PM2_5loop();

  
  
  
  private:
    float Vo_value = 0;
    float voltage = 0;
    float dustDensity = 0;


    int _Vo;
    int _V_LED;


};





#endif
