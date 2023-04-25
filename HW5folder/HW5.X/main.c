#include "nu32dip.h" // constants, functions for startup and UART
#include "spi.h"
#include <math.h>

#define cycles 400
#define PI 3.1415

int main(void) {
  char message[100];
  
  //functions
  unsigned short generate(unsigned short v, int a_or_b);
  
  //start up
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  initSPI();
  NU32DIP_WriteUART1("Hello\r\n"); //check if alive
  
  //initializations
  int sine_w[cycles];
  int triangle_w[cycles];
  
  //preallocation
  for(int i = 0; i < cycles; i++){ //sin wave for loop
      sine_w[i] = (int)511.5*sin(2*PI*i/cycles) + 511.5;
  }
    for(int j = 0; j < cycles; j++){ //triangle wave for loop
        if(j < cycles/200){
            triangle_w[j] = j * 1023 / (cycles/2);
        } else {
            triangle_w[j] = (cycles - j) * 1023 / (cycles/2);
        }
  }
  
  while (1) {
      //figure out the voltage for sin wave
      ////float f = 511.5*sin(2*pi*t)+511.5;
      ////unsigned int sinewave = f;
      //math to make sinewave 0 to 1023
      for(int k = 0; k < cycles; k++){
          generate(sine_w[k],0);
          generate(triangle_w[k],1);
          _CP0_SET_COUNT(0); // should really check for overflow here
            while (_CP0_GET_COUNT() < 48000000 / 2 / 100) { //check delay fast/slow
        }
      }
   
    //delay

}
}

 unsigned short generate(unsigned short v, int a_or_b){
    unsigned short t = 0;
    t = t|0b111<<12;
    t = t|(a_or_b <<15);
    t = t|(v <<2);

//      t = 0b1111111111111111;
    //send the voltage with spi
    LATBbits.LATB0 = 0; //set CS to low (CS = 0)
    spi_io(t>>8);
    spi_io(t&0xFF);
    LATBbits.LATB0 = 1; //set CS to high (CS = 1)
      //figure out the voltage for tri wave
      //send the voltage with spi
 }