#ifndef UTILS_H
#define UTILS_H

void dsb_sy(void) { __asm__ volatile("dsb sy" ::: "memory"); }
void isb(void)    { __asm__ volatile("isb" ::: "memory"); }

#endif
