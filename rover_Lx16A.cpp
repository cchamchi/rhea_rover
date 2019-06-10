/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/
#include <arduino.h>
#include <SoftwareSerial.h>
#include "rover_Lx16A.h"

byte RoverLx16A::LobotCheckSum(byte buf[]){
    byte i;
    uint16_t temp = 0;
    for (i = 2; i < buf[3] + 2; i++) {
        temp += buf[i];
    }
    temp = ~temp;
    i = (byte)temp;
    return i;
}

void RoverLx16A::Move(uint8_t id, int16_t position, uint16_t time){
    byte buf[10];
    if(position < 0)
        position = 0;
    if(position > 1000)
        position = 1000;
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 7;
    buf[4] = LOBOT_SERVO_MOVE_TIME_WRITE;
    buf[5] = GET_LOW_BYTE(position);
    buf[6] = GET_HIGH_BYTE(position);
    buf[7] = GET_LOW_BYTE(time);
    buf[8] = GET_HIGH_BYTE(time);
    buf[9] = LobotCheckSum(buf);
    SerialX->write(buf, 10);
}

void RoverLx16A::StopMove(uint8_t id){
    byte buf[6];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_MOVE_STOP;
    buf[5] = LobotCheckSum(buf);
    SerialX->write(buf, 6);
}
void RoverLx16A::SetID(uint8_t oldID, uint8_t newID){
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = oldID;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_ID_WRITE;
    buf[5] = newID;
    buf[6] = LobotCheckSum(buf);
    SerialX->write(buf, 7);
    
    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT SERVO ID WRITE");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif
}

int RoverLx16A::GetID(uint8_t ID){
    int count = 10000;
    int ret;
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = ID;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_ID_READ;
    buf[5] = LobotCheckSum(buf);
    
    
    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT SERVO ID READ");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif
    while (SerialX->available())
        SerialX->read();

    SerialX->write(buf, 6);

    while (!SerialX->available()) {
        count -= 1;
        if (count < 0)
        return -1;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
        ret = BYTE_TO_HW(buf[2], buf[1]);
    else
        ret = -1;

    #ifdef LOBOT_DEBUG
    Serial.println(ret);
    #endif
    return ret;    
}
void RoverLx16A::SetMode(uint8_t id, uint8_t Mode, int16_t Speed){
    byte buf[10];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 7;
    buf[4] = LOBOT_SERVO_OR_MOTOR_MODE_WRITE;
    buf[5] = Mode;
    buf[6] = 0;
    buf[7] = GET_LOW_BYTE((uint16_t)Speed);
    buf[8] = GET_HIGH_BYTE((uint16_t)Speed);
    buf[9] = LobotCheckSum(buf);

    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT SERVO Set Mode");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif

    SerialX->write(buf, 10);
}

void RoverLx16A::Load(uint8_t id){
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
    buf[5] = 1;
    buf[6] = LobotCheckSum(buf);
    
    SerialX->write(buf, 7);
    
    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT SERVO LOAD WRITE");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif
}

void RoverLx16A::Unload(uint8_t id){
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
    buf[5] = 0;
    buf[6] = LobotCheckSum(buf);
    
    SerialX->write(buf, 7);
    
    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT SERVO LOAD WRITE");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif
}

int RoverLx16A::LobotSerialServoReceiveHandle(byte *ret){
    bool frameStarted = false;
    bool receiveFinished = false;
    byte frameCount = 0;
    byte dataCount = 0;
    byte dataLength = 2;
    byte rxBuf;
    byte recvBuf[32];
    byte i;

    while (SerialX->available()) {
        rxBuf = SerialX->read();
        delayMicroseconds(100);
        if (!frameStarted) {
        if (rxBuf == LOBOT_SERVO_FRAME_HEADER) {
            frameCount++;
            if (frameCount == 2) {
            frameCount = 0;
            frameStarted = true;
            dataCount = 1;
            }
        }
        else {
            frameStarted = false;
            dataCount = 0;
            frameCount = 0;
        }
        }
        if (frameStarted) {
        recvBuf[dataCount] = (uint8_t)rxBuf;
        if (dataCount == 3) {
            dataLength = recvBuf[dataCount];
            if (dataLength < 3 || dataCount > 7) {
            dataLength = 2;
            frameStarted = false;
            }
        }
        dataCount++;
        if (dataCount == dataLength + 3) {
            
    #ifdef LOBOT_DEBUG
            Serial.print("RECEIVE DATA:");
            for (i = 0; i < dataCount; i++) {
            Serial.print(recvBuf[i], HEX);
            Serial.print(":");
            }
            Serial.println(" ");
    #endif

            if (LobotCheckSum(recvBuf) == recvBuf[dataCount - 1]) {
            
    #ifdef LOBOT_DEBUG
            Serial.println("Check SUM OK!!");
            Serial.println("");
    #endif

            frameStarted = false;
            memcpy(ret, recvBuf + 4, dataLength);
            return 1;
            }
            return -1;
        }
        }
    }

}

int RoverLx16A::ReadPosition(uint8_t id){
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_POS_READ;
    buf[5] = LobotCheckSum(buf);

    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT SERVO Pos READ");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif

    while (SerialX->available())
        SerialX->read();

    SerialX->write(buf, 6);

    while (!SerialX->available()) {
        count -= 1;
        if (count < 0)
        return -1;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
        ret = BYTE_TO_HW(buf[2], buf[1]);
    else
        ret = -1;

    #ifdef LOBOT_DEBUG
    Serial.println(ret);
    #endif
    return ret;
}

int RoverLx16A::ReadVin(uint8_t id){
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_VIN_READ;
    buf[5] = LobotCheckSum(buf);

    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT SERVO VIN READ");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif

    while (SerialX->available())
        SerialX->read();

    SerialX->write(buf, 6);

    while (!SerialX->available()) {
        count -= 1;
        if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
        ret = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
    else
        ret = -2048;

    #ifdef LOBOT_DEBUG
    Serial.println(ret);
    #endif
    return ret;
}
void RoverLx16A::OffsetAdjust(uint8_t id, int16_t offsetpos){
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_ANGLE_OFFSET_ADJUST;
    buf[5] = offsetpos;
    buf[6] = LobotCheckSum(buf);
    SerialX->write(buf, 7);
    
    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT SERVO ANGLE OFFSET ADJUST");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif
}
void RoverLx16A::Offsetwrite(uint8_t id, int16_t offsetpos){
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_ANGLE_OFFSET_WRITE;
    buf[5] = offsetpos;
    buf[6] = LobotCheckSum(buf);
    SerialX->write(buf, 7);
    
    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT_SERVO_ANGLE_OFFSET_WRITE");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif
}
void RoverLx16A::OffsetRead(uint8_t id){
    byte buf[6];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_ANGLE_OFFSET_READ;
    buf[5] = LobotCheckSum(buf);
    SerialX->write(buf, 6);
    
    #ifdef LOBOT_DEBUG
    Serial.println("LOBOT_SERVO_ANGLE_OFFSET_READ");
    int debug_value_i = 0;
    for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
    {
        Serial.print(buf[debug_value_i], HEX);
        Serial.print(":");
    }
    Serial.println(" ");
    #endif

}
