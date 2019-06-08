#ifndef rover_PM2_5_H
#define rover_PM2_5_H

class rover_PM2_5{
  public:
    rover_PM2_5(int Vo, int V_LED);
    rover_PM2_5(int Vo);
    void calulatePM2_5(float _dustDensity);
    float Vo_value = 0;
    float voltage = 0;
    float _dustDensity = 0;

  
  
  
  private:



    int _Vo;
    int _V_LED;


};





#endif
