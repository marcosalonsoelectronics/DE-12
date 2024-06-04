/**
* PWM test
* Output PWM signals on pins 0 and 1
 */

#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
     // Turn default LED on to show power is on
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    // Tell GPIO 0 and 1 they are allocated to the PWM
    gpio_set_function(0, GPIO_FUNC_PWM);
    gpio_set_function(1, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(0);
    // set clock divider to 1, then frequency is 125 MHz
    pwm_set_clkdiv(slice_num, 1); // maximum value here is 256

    // Set period number of cycles for 100 kHz output
    // period= 125e6/100e5 = 1250
    int period=1250;
    pwm_set_wrap(slice_num, period);
    // Set channel A output high for a number of cycles
    pwm_set_chan_level(slice_num, PWM_CHAN_A, period*0.9);
    // Set initial B output high for a number of cycles
    pwm_set_chan_level(slice_num, PWM_CHAN_B, period/3);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.
       while (1) {  }; // idle loop

}
