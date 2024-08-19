#include <DabbleESP32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>
#include "ServoManager.h"
#include "DisplayManager.h"

// Definir pines para el driver A4988
#define DIR_PIN  4
#define STEP_PIN 5
#define ENABLE_PIN 16  // Usamos GPIO 16 como pin de ENABLE

// Configuración del motor paso a paso (NEMA 17 con A4988 en 1/16 de micropasos)
const int stepsPerRevolution = 3200;  // 200 pasos por revolución con 1/16 de micropasos

// Crear objetos AccelStepper, ServoManager y DisplayManager
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
ServoManager myServo(18);
DisplayManager lcd(0x3F, 20, 4);

bool bluetoothConnected;
int maxSpeed = 4000;
void setup() {
    // Configurar la velocidad máxima y la aceleración para el NEMA 17
    stepper.setMaxSpeed(maxSpeed);  // Ajusta según las capacidades de tu motor
    stepper.setAcceleration(2000);
    digitalWrite(ENABLE_PIN, LOW); 
    pinMode(ENABLE_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, LOW);  // Inicialmente habilitar el motor

    lcd.init();
    Serial.begin(115200);
    Dabble.begin("MyEsp32");
    Dabble.waitForAppConnection();

    
    bluetoothConnected = true;

    // Posición inicial del servo (90 grados)
    myServo.setAngle(90);
}

void loop() {
    if(!bluetoothConnected){
        lcd.clear();
        lcd.print("Esperando conexion.");
    }

    if (bluetoothConnected) {
        Dabble.processInput();

        // Obtener los valores analógicos del joystick
        float x_axis = GamePad.getXaxisData();  // Valor del eje X (-7 a 7)
        float y_axis = GamePad.getYaxisData();  // Valor del eje Y (-7 a 7)

        // Imprimir los valores por serial con salto de línea
       
        Serial.print("X Axis: ");
        Serial.println(x_axis);
        Serial.print("Y Axis: ");
        Serial.println(y_axis);
        Serial.println();  // Salto de línea adicional para separar las lecturas

        // Mapear el valor del eje X a un ángulo de servo (0 a 180 grados)
        int servoAngle = map(x_axis, 7, -7, 0, 180);
        servoAngle = constrain(servoAngle, 0, 180);
        myServo.setAngle(servoAngle);
        
        lcd.clear();
        // Mostrar el valor del ángulo del servo en la pantalla LCD
        lcd.print("Servo: ", 0, 0);
        lcd.print(servoAngle, 7, 0);

        // Mapear el valor del eje Y a la velocidad del motor (-1000 a 1000)
        int motorSpeed = map(y_axis, -7, 7, -maxSpeed, maxSpeed);
        motorSpeed = constrain(motorSpeed, -maxSpeed, maxSpeed);
        stepper.setSpeed(motorSpeed); 
        stepper.runSpeed();
        // Mostrar la velocidad del motor en la pantalla LCD
        lcd.print("Motor: ", 0, 1);
        lcd.print(motorSpeed, 7, 1);




        // stepper.setSpeed(motorSpeed); 
        // stepper.runSpeed();
        // stepper.moveTo(40)
        // Controlar la velocidad y dirección del motor con el eje Y
        // if (motorSpeed != 0) {
        //       // Habilitar el motor
        //      stepper.setSpeed(motorSpeed);   // Establecer la velocidad del motor

        //     // // Mover el motor una vuelta completa
        //     //  long targetPosition = stepper.currentPosition() + (motorSpeed > 0 ? stepsPerRevolution : -stepsPerRevolution);
        //     // stepper.moveTo(targetPosition);
        //     // stepper.runToPosition();  // Ejecutar movimiento hasta la nueva posición
        //     stepper.setSpeed(motorSpeed); 
        //     stepper.runSpeed();

        // } else {
        //    // digitalWrite(ENABLE_PIN, HIGH); // Deshabilitar el motor para frenado
        // }

        delay(100);  // Ajusta el delay para que no sature el microcontrolador
    }
}