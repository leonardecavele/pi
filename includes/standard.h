#ifndef STANDARD_H
#define STANDARD_H

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

typedef unsigned int uint_t;

uint64_t strlen(const uint8_t *s);
int strcmp(const uint8_t *s1, const uint8_t *s2);
int strncmp(const uint8_t *s1, const uint8_t *s2, uint64_t len);
void cat(char *dst, uint32_t cap, char *src);
void *memset(void *s, int c, uint64_t n);

#endif
