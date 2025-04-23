#ifndef BITOPS_H
#define BITOPS_H

// Operación XOR entre dos valores de 8 bits
unsigned char xor_bits(unsigned char a, unsigned char b);

// Desplazamientos
unsigned char shift_left(unsigned char value, int n);
unsigned char shift_right(unsigned char value, int n);

// Rotaciones
unsigned char rotate_left(unsigned char value, int n);
unsigned char rotate_right(unsigned char value, int n);

#endif // BITOPS_H
