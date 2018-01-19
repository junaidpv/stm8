#include <stm8s.h>
#include <delay.h>

// Unsigned int is 16 bit in STM8.
// So, maximum possible value is 65536.
unsigned long int dl; // Delay

int main() {
	PB_ODR = 0x00;	// Turn all pins of port B to low
	PB_DDR |= 1 << PB5; // 0x00001000 PB5 is now output
	PB_CR1 |= 1 << PB5; // 0x00001000 PB5 is now pushpull

	while(1) {
		PB_ODR ^= 1 << PB5; // Toggle PB5 output

		delay_ms(1000);
	}
}
