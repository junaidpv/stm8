#ifndef TIME_H
#define TIME_H

#include "stm8s.h"

#ifndef F_CPU
#warning "F_CPU not defined, using 2MHz by default"
#define F_CPU 2000000UL
#endif

void timer4_millis_isr() __interrupt(TIM4_ISR);

void init_time();

uint32_t millis();

#endif /* TIME_H */
