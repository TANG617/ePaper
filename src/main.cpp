
/* The ESP32 has four SPi buses, however as of right now only two of
 * them are available to use, HSPI and VSPI. Simply using the SPI API 
 * as illustrated in Arduino examples will use VSPI, leaving HSPI unused.
 * 
 * However if we simply intialise two instance of the SPI class for both
 * of these buses both can be used. However when just using these the Arduino
 * way only will actually be outputting at a time.
 * 
 * Logic analyser capture is in the same folder as this example as
 * "multiple_bus_output.png"
 * 
 * created 30/04/2018 by Alistair Symonds
 */
#include <SPI.h>
#include "Arduino.h"

static const int spiClk = 1000000; // 1000 KHz
#define SCK 18
#define MISO 4
#define MOSI 17
#define SS 16
#define DC 5
//uninitalised pointers to SPI objects
SPIClass * spi = NULL;
void spiWrite(SPIClass *spi, byte data);
void SendCommand(SPIClass *spi, byte Reg);
void InitPin();


void setup() {
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  spi = new SPIClass(HSPI);
  spi->begin(SCK,-1,MOSI,SS);
}

// the loop function runs over and over again until power down or reset
void loop() {
  //use the SPI buses
  InitPin();
  SendCommand(spi, 0XAF); // junk data to illustrate usage
  delay(100);
}

void InitPin()
{
    pinMode(DC,OUTPUT);
    pinMode(SS,OUTPUT);
}


void SendCommand(SPIClass *spi, byte Reg)
{
    digitalWrite(DC, 0);
    digitalWrite(SS, 0);
    spiWrite(spi,Reg);
    digitalWrite(SS, 1);
}

void spiWrite(SPIClass *spi, byte data) {
  //use it as you would the regular arduino SPI API
  spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(spi->pinSS(), LOW); //pull SS slow to prep other end for transfer
  spi->transfer(data);
  digitalWrite(spi->pinSS(), HIGH); //pull ss high to signify end of data transfer
  spi->endTransaction();
}