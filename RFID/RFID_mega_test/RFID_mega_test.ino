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
  pinMode(3, OUTPUT);
  
}

void loop()
{
  boolean check1,check2,check3=false;
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
    
    if(RC522_1.serNum[0]==227&&RC522_1.serNum[1]==218&&RC522_1.serNum[2]==3&&RC522_1.serNum[3==23&&RC522_1.serNum[4]==45]){
       check1=true;
       
    }
    else{
       check1=false;
    }
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
    if(RC522_2.serNum[0]==179&&RC522_2.serNum[1]==238&&RC522_2.serNum[2]==39&&RC522_2.serNum[3]==23&&RC522_2.serNum[4]==109){
      check2=true;
       
    }
    else{
       check2=false;
    }
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
    if(RC522_3.serNum[0]==51&&RC522_3.serNum[1]==46&&RC522_3.serNum[2]==187&&RC522_3.serNum[3]==22&&RC522_3.serNum[4]==176){
       check3=true;
    }
    else{
       check3=false;
    }
    }
    Serial.println();
  }


  
  if(check1==true&&check2==true&&check3==true){
digitalWrite(3,HIGH);
delay(1000);
  }
else{
  digitalWrite(3,LOW);
}
Serial.print(check1);
Serial.print(check2);
Serial.println(check3);
  
}
