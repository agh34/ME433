#include "nu32dip.h"
// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    // Turn of analog pins
    //... //skip this part b/c it shouldn't matter
    // Make an output pin for CS
    TRISBbits.TRISB0 = 0;//TRIS set it as output
    LATBbits.LATB0 = 1; //LAT set it high
    // Set SDO1
    RPA1Rbits.RPA1R = 0b0011; //assign SDO1 to pin A1
    // Set SDI1
    SDI1Rbits.SDI1R = 0010; //assign SDI1 to pin B1

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 1000; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}