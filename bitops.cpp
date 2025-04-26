#include "bitops.h"

// Operacion XOR entre dos valores de 8 bits
uint8_t xor_bits(uint8_t a, uint8_t b) {
    return a ^ b;  // Operación XOR a nivel de bit
}

// Desplazamiento a la izquierda
uint8_t shift_left(uint8_t valor, uint8_t n) {
    return valor << n;  // Desplaza los bits de 'valor' a la izquierda 'n' veces
}

// Desplazamiento a la derecha
uint8_t shift_right(uint8_t valor, uint8_t n) {
    return valor >> n;  // Desplaza los bits de 'valor' a la derecha 'n' veces
}

// Rotación a la izquierda
uint8_t rotate_left(uint8_t valor, uint8_t n) {
    return (valor << n) | (valor >> (8 - n));  // Rotacion circular a la izquierda
}

// Rotación a la derecha
uint8_t rotate_right(uint8_t valor, uint8_t n) {
    return (valor >> n) | (valor << (8 - n));  // Rotacion circular a la derecha
}
