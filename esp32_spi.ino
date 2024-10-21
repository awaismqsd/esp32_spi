#include <SPI.h>

#define HSPI_MISO 12
#define HSPI_MOSI 13
#define HSPI_SCLK 14
#define HSPI_CS   15
static const int spiClk = 240000000/20; // 1/20 MHz = 50Khz
SPIClass * hspi = NULL;

//char buff[]="Hello Slave\n";

byte read_status = 0x05;
byte read_add = 0x03;


void setup() {
  Serial.begin(9600);
  hspi = new SPIClass(HSPI);
  hspi->begin();
  hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_CS); //SCLK, MISO, MOSI, SS
  pinMode(HSPI_CS, OUTPUT); //HSPI SS
  digitalWrite (HSPI_CS, HIGH);
  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
}

void loop() {
  
  Serial.print("Status = ");
  digitalWrite (HSPI_CS, LOW);
  hspi->transfer(read_status);
  Serial.print(hspi->transfer(0), HEX);
  Serial.print(hspi->transfer(0), HEX);
  digitalWrite (HSPI_CS, HIGH);
  Serial.println(".");
  
  Serial.print("ReadAdd = ");
  digitalWrite (HSPI_CS, LOW);
  hspi->transfer(read_add);
  hspi->transfer(0x15);
  Serial.print(hspi->transfer(0), HEX);
  Serial.print(hspi->transfer(0), HEX);
  digitalWrite (HSPI_CS, HIGH);
  Serial.println(".");
  
  Serial.print("Read24Bytes = ");
//  spiCommand(hspi, read_status);
//  spiCommand(hspi, read_add);
//  spiCommand(hspi, 0);

  for(int i=0; i<24; i++)
  {
    if (i==0){
      digitalWrite (HSPI_CS, LOW);
      hspi->transfer(read_add);
      hspi->transfer(0);      
    }
    Serial.print(hspi->transfer(0), HEX);

//  SPI.transfer(read_add[i]);
//    Serial.println(SPI.transfer(0));
//    Serial.print(spiCommand(hspi, 0), HEX);
  }
  digitalWrite (HSPI_CS, HIGH);
  Serial.println("...");
  delay(1000);  
}

//byte spiCommand(SPIClass *spi, byte data) {
//  byte datarcvd =0;
//  //use it as you would the regular arduino SPI API
//  spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
//  digitalWrite(spi->pinSS(), LOW);  //pull SS slow to prep other end for transfer
//  datarcvd = spi->transfer(data);
//  digitalWrite(spi->pinSS(), HIGH);  //pull ss high to signify end of data transfer
//  spi->endTransaction();
//  return datarcvd;
//}
