// 使用可變電阻控制 Servo 的旋轉角度
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

// 引用 Servo Library
#include <Servo.h> 

// 建立一個 Servo 物件 
Servo myservo; 
 
// 可變電阻接在 Analog pin 0 
int potpin = A0;
// 儲存旋轉角度的變數
int val;
 
void setup() 
{ 
  myservo.attach(9);  // Servo 接在 pin 9
} 
 
void loop() 
{ 
  val = analogRead(potpin);            // 讀取可變電阻(數值介於 0 到 1023)
  val = map(val, 0, 1023, 0, 179);     // 把 0 - 1023 的數值按比例縮放為 0 - 180 的數值
  myservo.write(val);                  // 設定 Servo 旋轉角度
  delay(15);                           // 等待 Servo 旋轉指定的位置
}
