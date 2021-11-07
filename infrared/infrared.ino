int sensor = 2;  //訊號線

void setup() {                
  Serial.begin(9600);
 // pinMode(13, OUTPUT);
  pinMode(sensor, INPUT); 
}

void loop() {
  
  int moving = digitalRead(sensor); //讀取D9是否有偵測到物體移動
  if(moving==1){ //如果有物體移動
    Serial.println("有東西在動！");
    digitalWrite(13,1); 
  }
  else
    digitalWrite(13,0);
}
