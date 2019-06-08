#ifndef roverPM25_H
#define roverPM25_H

class roverPM25{
  public:
    roverPM25(int Vo, int V_LED);
    void rover_PM2_5loop();

  
  
  
  private:
    float Vo_value = 0;
    float voltage = 0;
    float dustDensity = 0;


    int _Vo;
    int _V_LED;


};





#endif
