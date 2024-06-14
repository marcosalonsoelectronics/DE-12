/**
* PWM and ADC test
* Measures analog voltage at GPIO26
* and generates a PWM signal of 100 kHz
* and duty cycle proportional to the analog voltage
 */

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

int main() {

    // Set up default LED
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1); // turns LED on to show power is on 
    // Set up ADC
    stdio_init_all();
    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);
    // Set up PWM output
    // Tell GPIO0 it is allocated to the PWM
    gpio_set_function(0, GPIO_FUNC_PWM);
    // Find out which PWM slice is connected to GPIO0 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(0);

    // set clock divider to 1, frequency is 125 MHz
    pwm_set_clkdiv(slice_num, 1);
    // Set period number of cycles for 100 kHz output
    // period=125e6/100e3= 1250
    int period=1250;
    pwm_set_wrap(slice_num, period);
    // Set channel A duty cycle
    pwm_set_chan_level(slice_num, PWM_CHAN_A, period*0.5);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);

    while (1) {
    
        // 12-bit conversion, VREF= 3.3 V
        uint16_t result = adc_read();
        // set PWM output duty cycle
        pwm_set_chan_level(slice_num, PWM_CHAN_A, period*result/4096 );  
        sleep_ms(100);
    }
}


