#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include <stdio.h>
#include "font.h"
#include "ssd1306.h"

void blink(int iterations, int time_ms); // blink the LEDs function
void blinkScreen(int iterations, int time_ms, int across);
void drawChar(char letter, char x, char y);
void drawString(char*m, char x, char y);

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    init_mpu6050();
    ssd1306_setup();
    i2c_master_setup();
    
    char message[100];
    // int i = 0;
	// char array for the raw data
    unsigned char d[14];
	// floats to store the data
	float ax, ay, az, gx, gy, gz, t;
	// read whoami
    unsigned char who;
    who = whoami();
	// print whoami
    char m[100];
    sprintf(m,"0x%X\r\n",who);
    NU32DIP_WriteUART1(m);
	// if whoami is not 0x68, stuck in loop with LEDs on
    if(who != 0x68){
        while(1){
            blink(10,100);
        }
    }
	// wait to print until you get a newline
    NU32DIP_ReadUART1(m,100);
    //int test = 0;
    while (1) {
		// use core timer for exactly 100Hz loop
        _CP0_SET_COUNT(0);
        blink(1, 100);
        //blinkScreen(1,100, test);
        // read IMU
        burst_read_mpu6050(d);
		// convert data
        az = conv_zXL(d);
        // print out the data
        sprintf(m, "%f\r\n",az);
        NU32DIP_WriteUART1(m);
        
        ssd1306_clear();
        drawString(m, 10, 10);
        ssd1306_update();
        //test = test + 5;
        while (_CP0_GET_COUNT() < 48000000 / 2 / 100) {
        }

    }
    ssd1306_clear();
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
// blink the LEDs
void blinkScreen(int iterations, int time_ms, int across) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        ssd1306_drawPixel(across, 10, 1);
        ssd1306_update();
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
        ssd1306_drawPixel(across, 10, 0);
        ssd1306_update();
        ssd1306_clear();
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}

void drawChar(char letter, char x, char y) {
    for (int j = 0; j<5; j++) {
        char col = ASCII[letter- 0x20][j];
        for (int i=0; i<8; i++) {
            ssd1306_drawPixel(x+j,y+i, (col>>i)&0b1);
        }
    }
}

void drawString(char*m, char x, char y) {
    int k = 0;
    while (m[k] !='\r') {
        drawChar(m[k],x+5*k,y);
        k++;
    }
}