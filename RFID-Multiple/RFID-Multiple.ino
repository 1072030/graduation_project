
/**
   --------------------------------------------------------------------------------------------------------------------
   Example sketch/program showing how to read data from more than one PICC to serial.
   --------------------------------------------------------------------------------------------------------------------
   This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid

   Example sketch/program showing how to read data from more than one PICC (that is: a RFID Tag or Card) using a
   MFRC522 based RFID Reader on the Arduino SPI interface.

   Warning: This may not work! Multiple devices at one SPI are difficult and cause many trouble!! Engineering skill
            and knowledge are required!

   @license Released into the public domain.

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required *
   SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required *
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

*/

#include <SPI.h>
#include <MFRC522.h>
// PIN Numbers : RESET + SDAs
#define RST_PIN         9
#define SS_1_PIN        7
#define SS_2_PIN        6

// Led and Relay PINS
#define relayIN         3


// List of Tags UIDs that are allowed to open the puzzle
byte tagarray[][4] = {
  {0xB3, 0x8C, 0x4A, 0x16},
  {0x53, 0xDA, 0xB9, 0x16}, 
};

// Inlocking status :
int tagcount = 0;
int reader1_count = 0;
int reader2_count = 0;
bool access = false;
String content = "";
#define NR_OF_READERS   2

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

// Create an MFRC522 instance :
MFRC522 mfrc522[NR_OF_READERS];

/**
   Initialize.
*/
void setup() {

  Serial.begin(9600);           // Initialize serial communications with the PC
  while (!Serial);              // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();                  // Init SPI bus

  /* Initializing Inputs and Outputs */
  pinMode(relayIN, OUTPUT);
  digitalWrite(relayIN, HIGH);
  /* looking for MFRC522 readers */
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
    //mfrc522[reader].PCD_SetAntennaGain(mfrc522[reader].RxGain_max);
  }
}

/*
   Main loop.
*/

void loop() {

  if (mfrc522[0].PICC_IsNewCardPresent() && mfrc522[0].PICC_ReadCardSerial()) {
      content = "";
      Serial.print(F("Reader "));
      Serial.print(0);
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[0].uid.uidByte, mfrc522[0].uid.size);
      for (byte i = 0; i < mfrc522[0].uid.size; i++)
      {
        Serial.println(mfrc522[0].uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.println(mfrc522[0].uid.uidByte[i], HEX);
        content.concat(String(mfrc522[0].uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522[0].uid.uidByte[i], HEX));
      }
      content.toUpperCase();
        if(content.substring(1) == "B3 8C 4A 16"){
          Serial.println("reader : 0 Match");
          reader1_count = reader1_count+1;
        }
        if(content.substring(1) == "53 DA B9 16"){
          Serial.println("reader : 1 Match ||||| But Not Correct reader");
//          tagcount = tagcount+1;
        }  
    }
    if (mfrc522[1].PICC_IsNewCardPresent() && mfrc522[1].PICC_ReadCardSerial()) {
      String content = "";
      Serial.print(F("Reader "));
      Serial.print(1);
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[1].uid.uidByte, mfrc522[1].uid.size);
      for (byte i = 0; i < mfrc522[1].uid.size; i++)
      {
        Serial.println(mfrc522[1].uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.println(mfrc522[1].uid.uidByte[i], HEX);
        content.concat(String(mfrc522[1].uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522[1].uid.uidByte[i], HEX));
      }
      content.toUpperCase();
        if( content.substring(1) == "B3 8C 4A 16"){
          Serial.println("reader : 0 Match ||||| But Not Correct reader");
//          tagcount = tagcount+1;
        }
        if(content.substring(1) == "53 DA B9 16"){
          Serial.println("reader : 1 Match");
          reader2_count = reader2_count+1;
        }  
    }
    if(reader1_count == 1){
      Serial.println("In Check Again Loop!@~");
      CheckAgain(1);
    }else if(reader2_count == 1){
      Serial.println("In Check Again Loop!@~");
      CheckAgain(0);
    }
    delay(100);
   if(reader1_count && reader2_count){
     InitApp();
   }
   ResetVariable();
}

/**
   Helper routine to dump a byte array as hex values to Serial.
*/

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
void InitApp(){
  reader1_count = 0;
  reader2_count = 0;
  Serial.println("InitApp");
  delay(5000); //10秒緩衝reset
   for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}
void ResetVariable(){
  reader1_count = 0;
  reader2_count = 0;
}
void CheckAgain(int readerId){
  if (mfrc522[readerId].PICC_IsNewCardPresent() && mfrc522[readerId].PICC_ReadCardSerial()) {
      content = "";
      Serial.print(F("Reader "));
      Serial.print(readerId);
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[readerId].uid.uidByte, mfrc522[readerId].uid.size);
      for (byte i = 0; i < mfrc522[readerId].uid.size; i++)
      {
        Serial.println(mfrc522[readerId].uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.println(mfrc522[readerId].uid.uidByte[i], HEX);
        content.concat(String(mfrc522[readerId].uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522[readerId].uid.uidByte[i], HEX));
      }
      content.toUpperCase();
        if(content.substring(1) == "B3 8C 4A 16"){
          if(readerId == 0){
            Serial.println("reader : 0 Match");
            reader1_count = reader1_count+1;
          }
        }
        if(content.substring(1) == "53 DA B9 16"){
          if(readerId == 1){
            Serial.println("reader : 1 Match");
            reader2_count = reader2_count+1;
          }
        }  
      }
}
