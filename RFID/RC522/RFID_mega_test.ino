/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
*/
/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO_1 9
#define RESET_DIO_1 8
#define SDA_DIO_2 7
#define RESET_DIO_2 6
#define SDA_DIO_3 5
#define RESET_DIO_3 4
/* Create an instance of the RFID library */
RFID RC522_1(SDA_DIO_1, RESET_DIO_1); 
RFID RC522_2(SDA_DIO_2, RESET_DIO_2); 
RFID RC522_3(SDA_DIO_3, RESET_DIO_3); 

void setup()
{ 
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522_1.init();
  RC522_2.init();
  RC522_3.init();
}

void loop()
{
  /* Has a card been detected? */
  if (RC522_1.isCard())
  {
    /* If so then get its serial number */
    RC522_1.readCardSerial();
    Serial.println("ID 1號:");
    for(int i=0;i<5;i++)
    {
    Serial.print(RC522_1.serNum[i],DEC);
    //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    Serial.println();
  }
  if (RC522_2.isCard())
  {
    /* If so then get its serial number */
    RC522_2.readCardSerial();
    Serial.println("ID 2號:");
    for(int i=0;i<5;i++)
    {
    Serial.print(RC522_2.serNum[i],DEC);
    //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    Serial.println();
  }
  if (RC522_3.isCard())
  {
    /* If so then get its serial number */
    RC522_3.readCardSerial();
    Serial.println("ID 3號:");
    for(int i=0;i<5;i++)
    {
    Serial.print(RC522_3.serNum[i],DEC);
    //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    Serial.println();
  }
  delay(1000);
}
