#include  <SoftwareSerial.h>
SoftwareSerial BT(10, 11); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
const byte LED_PIN = 13;  // 定義LED腳位
 
void setup() {
  // 設定HC-05藍牙模組，AT命令模式的連線速率。
  BT.begin(38400);
  pinMode(LED_PIN, OUTPUT);
}
 
void loop() {
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    if (val == '1') {
      digitalWrite(LED_PIN, HIGH);
      // 回應命令發送端，告知「已開燈」
      BT.println("LED ON");
    } else if (val == '0') {
      digitalWrite(LED_PIN, LOW);
      // 回應命令發送端，告知「已關燈」
      BT.println("LED OFF");
    }
  }
}
