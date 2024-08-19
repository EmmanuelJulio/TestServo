#include "DisplayManager.h"

DisplayManager::DisplayManager(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows)
    : lcd(lcdAddr, lcdCols, lcdRows) {}

void DisplayManager::init() {
    lcd.init();
    lcd.backlight();
}

// Implementación para imprimir cadenas de texto
void DisplayManager::print(const char* message, uint8_t col, uint8_t row) {
    
    lcd.setCursor(col, row);
    lcd.print(message);
}

void DisplayManager::clear(){
    lcd.clear();
}
// Implementación para imprimir números enteros
void DisplayManager::print(int number, uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
    lcd.print(number);
}

// Implementación para imprimir números flotantes
void DisplayManager::print(float number, uint8_t col, uint8_t row, int decimalPlaces) {
    lcd.setCursor(col, row);
    lcd.print(number, decimalPlaces);
}

void DisplayManager::setCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
}