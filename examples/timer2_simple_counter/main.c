#include <stm8s.h>

int main() {
  // Default clock is HSI/8 = 2MHz

  PB_DDR |= (1 << PB5); // PB5 is now output
  PB_CR1 |= (1 << PB5); // PB5 is now pushpull

  TIM2_PSCR = 0b00000111; //  Prescaler = 128
  TIM2_EGR |= (1 << TIM2_EGR_UG); // Generate an update event so prescaler value will be taken into account.
  TIM2_CR1 |= (1 << TIM2_CR1_CEN); // Enable TIM2

  while (1) {
    if ( ( ((uint16_t)TIM2_CNTRH << 8) + (uint16_t)TIM2_CNTRL ) >= 7000 ) {
      // Reset counter back to 0
      TIM2_CNTRH = 0;
      TIM2_CNTRL = 0;

      // Toggle LED.
      PB_ODR ^= (1 << PB5);
    }
  }
}
