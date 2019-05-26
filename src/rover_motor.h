/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/


#ifndef RoverMotor_H
#define RoverMotor_H


class RoverMotor {

    public:
        RoverMotor();
        void getCornerDegree(float *corner_degree);
        float approxTurningRadius(float *corner_degree);
        void calculateVelocity(int vel_joy,float radius,float *velocity_wheel);
        void sendCommand(float *velocity_wheel,float *corner_degree);
        void calculateTargetDeg(int radius_joy,float *target_degree );        
        void cornerPosControl(float *target_degree);

    private:
        float currunt_radius;
        float corner_degree[4];
        float target_degree[4];
        float velocity_wheel[6];
        float d1=7.254,d2=10.5,d3=10.5,d4=10.073; // distance of wheel from centor
};


#endif