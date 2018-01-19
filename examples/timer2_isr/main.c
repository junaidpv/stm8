#include <stdint.h>
#include <stm8s.h>

const uint16_t reload_value = 49910;

void timer_isr() __interrupt(TIM2_OVF_ISR) {
    PB_ODR ^= 1 << PB5; // Toggle PB5 output
    TIM2_SR1 &= ~(1 << TIM2_SR1_UIF); // Clear interrupt flag
}

void main() {
    enable_interrupts();

    PB_DDR |= 1 << PB5; // 0x00001000 PB5 is now output
  	PB_CR1 |= 1 << PB5; // 0x00001000 PB5 is now pushpull

    TIM2_PSCR = 0b00000111; //  Prescaler = 128
    // Fill auto reload registers.
    TIM2_ARRH = reload_value >> 8;
    TIM2_ARRL = reload_value & 0x00FF;

    TIM2_IER |= (1 << TIM2_IER_UIE); // Enable Update Interrupt
    //TIM2_CR1 |= (1 << TIM2_CR1_ARPE); //

    TIM2_EGR |= (1 << TIM2_EGR_UG); // Generate an update event so prescaler value will be taken into account.

    TIM2_CR1 |= (1 << TIM2_CR1_CEN); // Enable TIM2


    TIM2_SR1 &= ~(1 << TIM2_SR1_UIF); // Clear interrupt flag

    while (1) {
        // do nothing
    }
}
