#ifndef BITOPS_H // Iniciamos la directiva //
#define BITOPS_H // Definimos la consola BITOPS_H para marcar que ya se incluyo

#include <cstdint>  // Biblioteca para definir tipos de entero con un tamaño exacto, en este caso (uint8_t)


// Declaracion de las funciones a nivel de bits //


// Operacion XOR entre dos valores de 8 bits
uint8_t xor_bits(uint8_t a, uint8_t b);

// Desplazamientos
uint8_t shift_left(uint8_t value, uint8_t n);
uint8_t shift_right(uint8_t value, uint8_t n);

// Rotaciones
uint8_t rotate_left(uint8_t value, uint8_t n);
uint8_t rotate_right(uint8_t value, uint8_t n);

#endif // Finalizamos la directiva //
