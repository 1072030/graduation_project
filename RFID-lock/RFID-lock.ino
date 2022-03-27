#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
//電視程式
#define RST_PIN         9          
#define SS_PIN          7 //RC522卡上的SDA



char *reference;
int relayPin=3;                    // 連接繼電器腳位                       
byte uid[]={0xFA, 0x5D, 0x49, 0x26};  //這是我們指定的卡片UID，可由讀取UID的程式取得特定卡片的UID，再修改這行
//byte carduid[] = {0x53,0xDA,0xB9,0x16};
MFRC522 mfrc522;   // 建立 MFRC522
String isDetect = "";

void setup()
{
            // 設定繼電器接腳為輸出腳位      // 設定綠LED燈接腳為輸出腳位
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  SPI.begin();
  mfrc522.PCD_Init(SS_PIN, RST_PIN);
  digitalWrite(relayPin, HIGH);
  Serial.println("可開始讀取卡片");
  Serial.println();
  mfrc522.PCD_DumpVersionToSerial();
}

void loop() {
  
 // 是否為新卡？
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  
  // 選擇一張卡
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  
  // 在監控視窗顯示UID
  Serial.print("Card No. :");
  isDetect = "";
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  // 讓在讀卡區的RFID卡進入休眠狀態，不再重複讀卡
//  mfrc522.PICC_HaltA();
//  // 停止讀卡模組編碼  
//  mfrc522.PCD_StopCrypto1();
  Serial.println();
  Serial.print(" Message : ");
  content.toUpperCase();
  // 需改成自己RFID卡的UID
  if (content.substring(1) == "FA DF FA 26")//電視的卡
  {
    Serial.println(content.substring(1));
    Serial.println("合法卡");
    Serial.println();
//    isDetect = "1";
//    Serial.println(isDetect);
    digitalWrite(relayPin, LOW);               // 繼電器常開端(NO)導通
    delay(2000);                                // 延遲2秒
    digitalWrite(relayPin, HIGH);                // 繼電器常閉端(NC)導通
//    mfrc522.PCD_Init(SS_PIN, RST_PIN);
//    Serial.println(" 不合法卡...");
//    Serial.println();
  }else if(content.substring(1) =="FA DE 1B 26"){
    Serial.println(content.substring(1));
    Serial.println("合法卡");
    Serial.println();
//    isDetect = "2";
//    Serial.println(isDetect);
  }
}
/**
 * 這個副程式把讀取到的UID，用16進位顯示出來
 */
//void dump_byte_array(byte *buffer, byte bufferSize) {
//  for (byte i = 0; i < bufferSize; i++) {
//    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
//    Serial.print(buffer[i], HEX);44444
//  }
//}
