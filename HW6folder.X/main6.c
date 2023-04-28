#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>
#include "i2c_master_noint.h"

void blink(int, int); // blink the LEDs function
void turnOn_GP7(void);
void generic_i2c_write(unsigned char address, unsigned char reg, unsigned char value);
unsigned char readPin(unsigned char address, unsigned char reg);
		

int main(void) {
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  i2c_master_setup();
//init the chip, GP0 is input, GP7 is output
  unsigned char send = 0b01000000;
  unsigned char r;
  generic_i2c_write(0b01000000, 0x0, 0b00000001);

  while (1) {
      //turnOn_GP7();
      //blink GP7
      
      r = readPin(send, 0x09);
      if (r){
          generic_i2c_write(send,0x0A, 0b10000000);
      } else {
          generic_i2c_write(send,0x0A, 0b00000000); 

} 
  }}

void turnOn_GP7(void){      //turn on GP7
      generic_i2c_write(0b01000000, 0x0A, 0b10000000);
      _CP0_SET_COUNT(0); // should really check for overflow here
      while (_CP0_GET_COUNT() < 48000000 / 2 / 10) {
      }
      //turn off GP7
      generic_i2c_write(0b01000000, 0x0A, 0b00000000);
      _CP0_SET_COUNT(0); // should really check for overflow here
      while (_CP0_GET_COUNT() < 48000000 / 2 / 10) {
      }
}

void generic_i2c_write(unsigned char address, unsigned char reg, unsigned char value){
    i2c_master_start();
    i2c_master_send(address);
    i2c_master_send(reg);
    i2c_master_send(value);
    i2c_master_stop();
}
// blink the LEDs


unsigned char readPin(unsigned char address, unsigned char reg){
    //send start
    i2c_master_start();
    i2c_master_send(address); //write
    i2c_master_send(reg);
    i2c_master_restart();
    i2c_master_send(address|1); //read
    unsigned char rf = (i2c_master_recv());
    i2c_master_ack(1);
    i2c_master_stop();
    return (rf&0b00000001);
}
