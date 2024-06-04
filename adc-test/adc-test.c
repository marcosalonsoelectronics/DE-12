/**
* ADC test
* Measures analog voltage at GPIO26
* Turns the default LED on when the voltage
* is higher than a limit value vlim
* Turns off when the voltage is lower than
* the limit value
 */

#include "pico/stdlib.h"
#include "hardware/adc.h"

int main() {

    // Set up default LED
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    //gpio_put(LED_PIN, 1);

    stdio_init_all();
    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

    while (1) {
        // limit voltage to detect
        const float vlim= 1.8;
        // 12-bit conversion, VREF= 3.3 V
        uint16_t result = adc_read();

        // turn on the LED when vin > vlimit
        // turn off the LED when vin < vlimit
        if (result > (vlim*4096/3.3)) {
                        gpio_put(LED_PIN, 1);} 
        else {
                        gpio_put(LED_PIN, 0);}
        
        sleep_ms(250);
        
    }
    
}
