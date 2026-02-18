#include "standard.h"

extern uint64_t strlen(const uint8_t *s)
{
	int	i = 0;

	while (*s++)
		i++;
	return (i);
}

extern int strcmp(const uint8_t *s1, const uint8_t *s2)
{
	while (*s1 && *s1 == *s2) { s1++; s2++; }
	return *s1 - *s2;
}

extern int strncmp(const uint8_t *s1, const uint8_t *s2, uint64_t len)
{
	while (len && *s1 && *s1 == *s2) { s1++; s2++; len--; }
	if (len == 0) return 0;
	return *s1 - *s2;
}

extern void cat(char *dst, uint32_t cap, char *src)
{
    uint32_t i = 0;
    while (i + 1 < cap && dst[i])
        i++;

    uint32_t j = 0;
    while (i + 1 < cap && src[j]) {
        dst[i++] = src[j++];
    }
    dst[i] = 0;
}

void *memset(void *s, int c, uint64_t n)
{
	uint8_t *p = (uint8_t *)s;
	while (n--)
		*p++ = (uint8_t)c;
	return s;
}
