#include "bitops.h"

unsigned char shift_left(unsigned char value, int n) {
    return value << n;
}

unsigned char shift_right(unsigned char value, int n) {
    return value >> n;
}

unsigned char rotate_right(unsigned char value, int n) {
    return (value >> n) | (value << (8 - n));
}
