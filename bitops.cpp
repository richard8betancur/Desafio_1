#include "bitops.h"

uint8_t xor_bits(uint8_t a, uint8_t b) {
    return a ^ b;
}

uint8_t shift_left(uint8_t value, uint8_t n) {
    return value << n;
}

uint8_t shift_right(uint8_t value, uint8_t n) {
    return value >> n;
}

uint8_t rotate_left(uint8_t value, uint8_t n) {
    return (value << n) | (value >> (8 - n));
}

uint8_t rotate_right(uint8_t value, uint8_t n) {
    return (value >> n) | (value << (8 - n));
}
