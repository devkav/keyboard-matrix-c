#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <pico/stdio.h>
#include "hardware/gpio.h"

#include <pico/time.h>
#include <stdio.h>

static const uint row_pins[] = {2, 3};
static const uint col_pins[] = {4, 5};

#define NUM_ROWS (sizeof(row_pins) / sizeof(row_pins[0]))
#define NUM_COLS (sizeof(col_pins) / sizeof(col_pins[0]))

#define ROW_SLEEP_US 10

// Turn the led on or off
void pico_set_led(bool led_on) {
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

int main() {
    stdio_init_all();

    // int rc = cyw43_arch_init();
    // hard_assert(rc == PICO_OK);

    for (uint i = 0; i < NUM_ROWS; i++) {
        uint pin = row_pins[i];

        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }

    for (uint i = 0; i < NUM_COLS; i++) {
        uint pin = col_pins[i];

        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_down(pin);
    }

    while (true) {
        for (uint row = 0; row < NUM_ROWS; row++) {
            uint row_pin = row_pins[row];

            gpio_put(row_pin, 1);
            sleep_us(ROW_SLEEP_US);

            for (uint col = 0; col < NUM_COLS; col++) {
                uint col_pin = col_pins[col];

                if (gpio_get(col_pin)) {
                    printf("Key press at (%d, %d)\n", row, col);
                }
            }

            gpio_put(row_pin, 0);
        }
    }
}
