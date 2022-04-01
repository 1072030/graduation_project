#include  <SoftwareSerial.h>              //  引用<SoftwareSerial.h>函式庫
#include <MFRC522.h>
#include <SPI.h>
//***定義變數區***
#define Bluetooth_KEY 
//  定義藍芽傳輸模組KEY接腳連接至arduino第9接腳
#define Bluetooth_RxD 5
//  定義藍芽傳輸模組RxD接腳連接至arduino第11接腳
#define Bluetooth_TxD 4
//  定義藍芽傳輸模組TxD接腳連接至arduino第10接腳
#define RST_PIN         9          
#define SS_PIN          7 //RC522卡上的SDA
#define relayPin        3
String content = "";
SoftwareSerial BTSerial(Bluetooth_TxD, Bluetooth_RxD);
MFRC522 mfrc522;
//  建立軟體定義串列埠BTSerial，用以控制藍芽模組
void setup()                             //  setup程式
{                                      //  進入setup程式
  pinMode(relayPin, OUTPUT);
  //  設定arduino連接藍芽傳輸模組KEY之接腳為輸出
  //  設定藍芽傳輸模組KEY接腳為HIGH(進入AT command模式)
  Serial.begin(38400);
  digitalWrite(relayPin, HIGH);
  SPI.begin();
  mfrc522.PCD_Init(SS_PIN, RST_PIN);
  //  開啟 Serial Port透過USB(uart)方式與電腦通信，鮑率為 38400bps (Bits Per Second)
  Serial.print("Enter AT commands:");
  //  透過USB(uart)傳輸字串"Enter AT commands:"
  BTSerial.begin(4800);//設定是4800
  //  設定控制HC-05藍芽模組之串列埠BTSerial鮑率為38400bps，此亦為HC-05藍芽模組預設鮑率
  Serial.println("可開始讀取卡片");
  Serial.println();
  mfrc522.PCD_DumpVersionToSerial();
}                                     //  結束setup程式

void loop()                              //  loop程式
{                                      //  進入loop程式
  CheckRFID();
  // Keep reading from HC-05 and send to Arduino Serial Monito
  if (BTSerial.available())
    //  若連接至藍芽模組之Serialport接收到字元
  {                                    //  進入if敘述
    char BTSerial_read;
    //  宣告BTSerial_read字元變數，用於記錄BTSerial.read()回傳字元
    BTSerial_read = BTSerial.read();
    //  將BTSerial.read()回傳字元填入BTSerial_read
    if(BTSerial_read == '0'){
      digitalWrite(relayPin,LOW);
      BTSerial.println("LED OFF");
      Serial.print("relayDown");
      delay(2000);
      digitalWrite(relayPin,HIGH);
    }
    Serial.write(BTSerial_read);
    //  將BTSerial_read回傳至電腦
    if(BTSerial_read == '\n')
    //  若BTSerial_read為換行字元
    {                                  //  進入if敘述
      delay(10);                         //  延遲10ms
      if(BTSerial.available() == 0)          //  若資料傳輸結束
      {                                //  進入if敘述
        Serial.print("Enter AT commands:");
        //digitalWrite(Bluetooth_KEY,HIGH);
        //  透過USB(uart)傳輸字串"Enter AT commands:"
      }                                //  結束if敘述
    }                                  //  結束if敘述
  }                                    //  結束if敘述

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
  //  若與電腦連線之Serial Port接收到字元
  {                                    //  進入if敘述
    char Serial_read;
    //  宣告Serial_read字元變數，用於記錄Serial.read()回傳字元
    Serial_read = Serial.read();
    //  將Serial.read()回傳字元填入Serial_read
    Serial.print(Serial_read);
    //  將Serial_read字元回傳至電腦
    BTSerial.write(Serial_read);
    //  將Serial_read字元傳送至藍芽模組
  }                                    //  結束if敘述
}                                      //  結束loop程式
void CheckRFID(){
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    content = "";
    Serial.print(F("Reader "));
    Serial.print(F(": Card UID:"));
    //dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.println(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.println(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    if(content.substring(1) == "B3 EE 27 17"){
      Serial.println("reader : 0 Match");
      digitalWrite(relayPin,LOW);
      delay(2000);
      digitalWrite(relayPin,HIGH);
    }
  }
}
