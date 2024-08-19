#include "ServoManager.h"

ServoManager::ServoManager(int pin) {
    myServo.attach(pin);
}

void ServoManager::setAngle(int angle) {
    myServo.write(angle);
}