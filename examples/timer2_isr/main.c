#include <stdint.h>
#include <stm8s.h>

// Default system clock will be 2MHz.
// We set 128 as prescaler, then each tick of timer 2 will be in 64 micro seconds.
// So, timer will generate overflow interrupt in each second,
// when counter reaches at 15625 (1S/64uS) which is set in auto reload register.
// There are two 8 bit regisgers to hold 16 bit value for ARR. So, we create a 16
// bit unsigned number.
const uint16_t reload_value = 15625;

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
    // We need to put MSB and LSB in separate 8 bit registers.
    // Also, as per datasheet, we have to put value in ARRH first, then in ARRL.
    TIM2_ARRH = reload_value >> 8;
    TIM2_ARRL = reload_value & 0x00FF;

    TIM2_IER |= (1 << TIM2_IER_UIE); // Enable Update Interrupt
    TIM2_CR1 |= (1 << TIM2_CR1_CEN); // Enable TIM2

    while (1) {
        // do nothing
    }
}
