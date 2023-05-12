#include "nu32dip.h" // constants, functions for startup and UART
#include <stdio.h>
#include "ws2812b.h"

void blink(int iterations, int time_ms); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    ws2812b_setup();
    int numLEDs = 4;
    int hue = 0;
    wsColor colors[numLEDs];
    while (1) {
        for (int i = 0; i < numLEDs; i++) {
            colors[i] = HSBtoRGB(hue, 0.5, 1);
            
        if (hue < 360) {
            hue = hue + 1;
        } else {
            hue = 0;
            }}
        ws2812b_setColor(colors, numLEDs);
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000 / 2 / 10) {
    }
    }
}
// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}

