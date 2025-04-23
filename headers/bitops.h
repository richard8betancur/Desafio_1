#ifndef BITOPS_H
#define BITOPS_H

#include <cstdint>  // Usamos uint8_t para ser más explícitos y portables

// Operación XOR entre dos valores de 8 bits
uint8_t xor_bits(uint8_t a, uint8_t b);

// Desplazamientos
uint8_t shift_left(uint8_t value, uint8_t n);
uint8_t shift_right(uint8_t value, uint8_t n);

// Rotaciones
uint8_t rotate_left(uint8_t value, uint8_t n);
uint8_t rotate_right(uint8_t value, uint8_t n);

#endif // BITOPS_H
