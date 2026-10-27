/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <pico/stdio.h>
#include "hardware/gpio.h"

#include <stdio.h>

#define LED_DELAY_MS 1000
#define BUTTON_PIN 15

// Turn the led on or off
void pico_set_led(bool led_on) {
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

int main() {
    stdio_init_all();

    /*
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("Hello, world!\n");
    */

    int rc = cyw43_arch_init();
    hard_assert(rc == PICO_OK);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);

    bool last = false;
    while (true) {
        bool pressed = gpio_get(BUTTON_PIN);

        // only print when the state changes, not every loop
        if (pressed != last) {
            printf("button: %d\n", pressed);
            pico_set_led(pressed);
            last = pressed;
        }

        sleep_ms(10);
    }
}
