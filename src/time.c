#include <stdint.h>

#include "time.h"
#include "stm8s.h"
#include "util.h"

volatile uint32_t __global_millis = 0;

void timer4_millis_isr() __interrupt(TIM4_ISR) {
    __global_millis++;
    clear_bit(TIM4_SR, TIM4_SR_UIF);  // Clear interrupt flag
}

void init_time() {
    enable_interrupts();
    TIM4_PSCR = 3; // So prescaler will be 2^3 = 8
    // Timer 4 will increment in each 4 micro seconds
    TIM4_ARR = 249; // So timer 4 will overflow in each milli second.
    set_bit(TIM4_IER, TIM4_IER_UIE);  // Enable update interrupt.
    //set_bit(TIM4_EGR, TIM4_EGR_UG);
    set_bit(TIM4_CR1, TIM4_CR1_CEN);  // Enable timer 4.
}

/**
  * Return current milli seconds.
  */
uint32_t millis() {
    return __global_millis;
}
