// #include <AccelStepper.h>

// #define DIR_PIN  4
// #define STEP_PIN 5

// // Crear un objeto AccelStepper
// AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// void setup() {
//   // Configurar la velocidad máxima y la aceleración
//   stepper.setMaxSpeed(2500); // Velocidad máxima en pasos por segundo
//   stepper.setAcceleration(2000); // Aceleración en pasos por segundo^2

//   // Inicializar el motor en posición 0
//   stepper.moveTo(10000); // Mover 200 pasos en adelante
// }

// void loop() {
//   // Verificar si el motor ha alcanzado su posición objetivo
//   if (stepper.distanceToGo() == 0) {
//     // Cambiar la dirección
//     stepper.moveTo(-stepper.currentPosition());
//   }

//   // Hacer que el motor avance hacia la posición objetivo
//   stepper.run();
// }