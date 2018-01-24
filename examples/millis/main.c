#include <stm8s.h>
#include <stdint.h>
#include <util.h>
#include <time.h>


uint32_t lasttime = 0;
int main() {
    set_bit(PB_DDR, 5); // PB5 is now output
    set_bit(PB_CR1, 5); // PB5 is now pushpull
    init_time();

    while(1) {
        if ((millis() - lasttime) > 1000 ) {
            toggle_bit(PB_ODR, 5); // Toggle PB5 output
            lasttime = millis();
        }
    }
}
