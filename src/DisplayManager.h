#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>

class DisplayManager {
public:
    DisplayManager(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows);
    void init();
    
    void clear();
    // Sobrecarga para imprimir cadenas de texto
    void print(const char* message, uint8_t col = 0, uint8_t row = 0);

    // Sobrecarga para imprimir números enteros
    void print(int number, uint8_t col = 0, uint8_t row = 0);

    // Sobrecarga para imprimir números flotantes
    void print(float number, uint8_t col = 0, uint8_t row = 0, int decimalPlaces = 2);
    
    void setCursor(uint8_t col, uint8_t row);
private:
    LiquidCrystal_I2C lcd;
};

#endif