#include <DabbleESP32.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>



#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define DIR_PIN  4
#define STEP_PIN 5


AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
LiquidCrystal_I2C lcd( 0x3F, 20, 4); 
bool bluetoothConnected;
Servo myServo;


void setup() {

  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(100);

  lcd.init();                      
  lcd.backlight();                 
  lcd.setCursor(0, 0);            
  Serial.begin(115200);   
  Dabble.begin("MyEsp32");
   myServo.attach(18); 
   Dabble.waitForAppConnection();
   
  lcd.print("Sistema conigurado correctamente.");        
  bluetoothConnected = true;
}

void loop() {
if(bluetoothConnected){
    Dabble.processInput();

    // Obtener los valores analógicos del joystick
    float x_axis = GamePad.getXaxisData();  // Valor del eje X (-512 a 512)
    float y_axis = GamePad.getYaxisData();  // Valor del eje Y (-512 a 512)

if (GamePad.isSquarePressed())
  {
    lcd.print("Square");
    myServo.write(180);
  }

  if (GamePad.isCirclePressed())
  {
    lcd.print("Circle");
    myServo.write(0);
  }

  if (GamePad.isCrossPressed())
  {
    myServo.write(90);
    lcd.print("Cross");
  }

  if (GamePad.isTrianglePressed())
  {
    lcd.print("Triangle");
    myServo.write(0);
  }
  // else{
    // Ajustar la sensibilidad del joystick
    // Mapear con un rango más pequeño para aumentar la sensibilidad
    int servoAngle = map(x_axis, -256, 256, 0, 180);
    servoAngle = constrain(servoAngle, 0, 180); // Asegurarse que esté dentro de los límites

    // Controlar la velocidad y dirección del motor paso a paso con el eje Y
    int motorSpeed = map(y_axis, -256, 256, -1000, 1000);
    motorSpeed = constrain(motorSpeed, -1000, 1000); // Limitar dentro del rango permitido

    // Aplicar los valores al hardware

   Serial.print("Servo: ");
    Serial.print(servoAngle);
    Serial.print("Motor: ");
     Serial.print(motorSpeed);
    // stepper.runSpeed();

  //   // Mostrar en la LCD los valores actuales
  //   lcd.clear();
  //   lcd.setCursor(0, 0);
  //   lcd.print("Servo: ");
  //   lcd.print(servoAngle);
  //   lcd.setCursor(0, 1);
  //   lcd.print("Motor: ");
  //   lcd.print(motorSpeed);

  //   delay(500);
  // }

    
  }
}
