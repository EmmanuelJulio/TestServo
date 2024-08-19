#ifndef SERVO_MANAGER_H
#define SERVO_MANAGER_H

#include <ESP32Servo.h>

class ServoManager {
public:
    ServoManager(int pin);
    void setAngle(int angle);
private:
    Servo myServo;
};

#endif