#include "bitops.h"

// Operación XOR entre dos valores de 8 bits
uint8_t xor_bits(uint8_t a, uint8_t b) {
    return a ^ b;  // Operación XOR a nivel de bit
}

// Desplazamiento a la izquierda
uint8_t shift_left(uint8_t value, uint8_t n) {
    return value << n;  // Desplaza los bits de 'value' a la izquierda 'n' veces
}

// Desplazamiento a la derecha
uint8_t shift_right(uint8_t value, uint8_t n) {
    return value >> n;  // Desplaza los bits de 'value' a la derecha 'n' veces
}

// Rotación a la izquierda
uint8_t rotate_left(uint8_t value, uint8_t n) {
    return (value << n) | (value >> (8 - n));  // Rotación circular a la izquierda
}

// Rotación a la derecha
uint8_t rotate_right(uint8_t value, uint8_t n) {
    return (value >> n) | (value << (8 - n));  // Rotación circular a la derecha
}
