#include <stm8s.h>
#include <util.h>

const uint16_t timer2_arr = 999; // PWM with 2kHz frequency
const uint16_t timer2_ccr1 = 249; // 25% duty cycle.
int main() {
  disable_interrupts();

  // As per datasheet of stm8s103f3 PD4 pin is timer 2 channel 1.
  SET_BIT(PD_DDR, 4); // 0b00010000 PD4 is now output
  SET_BIT(PD_CR1, 4); // 0b00010000 PD4 is now pushpull

  TIM2_PSCR = 0x00; // Prescaler = 1

  TIM2_ARRH = timer2_arr >> 8;
  TIM2_ARRL = timer2_arr & 0x00FF;

  TIM2_CCR1H = timer2_ccr1 >> 8;
  TIM2_CCR1L = timer2_ccr1 & 0x00FF;

  SET_BIT(TIM2_CCER1, TIM2_CCER1_CC1P); // channel 1 active low
  SET_BIT(TIM2_CCER1, TIM2_CCER1_CC1E); // Enable channel 1 output

  // PWM mode 1.
  SET_BIT(TIM2_CCMR1, 6); // Set output compare mode as 6 (0b110)
  SET_BIT(TIM2_CCMR1, 5); // So channel 1 will be acitve while counter
  CLEAR_BIT(TIM2_CCMR1, 4);  // is lower than compare value.

  SET_BIT(TIM2_CR1, TIM2_CR1_CEN); // Enable counter

  enable_interrupts();
  while(1) {
    // Do nothing
  }
}
