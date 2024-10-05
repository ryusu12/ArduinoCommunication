#include "BluetoothSerial.h" // 블루투스 라이브러리
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// 블루투스가 활성화 되지않으면
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
// 오류문구 출력
#endif
BluetoothSerial SerialBT; //BluetoothSerial 객체 SerialBT 선언

#define TRIG 25 // TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 26 // ECHO 핀 설정 (초음파 받는 핀)

#define PIN_LM35 34 //온도 센서 출력선

void setup() {
  Serial.begin(115200);        // esp32에 맞춘 시리얼 통신 속도
  SerialBT.begin("ESP32test"); // Bluetooth device name
  
  pinMode(TRIG, OUTPUT);       // TRIG 핀 출력으로
  pinMode(ECHO, INPUT);        // ECHO 핀 입력으로
}


void loop() {
  float distance = 0;           // 거리 변수 초기화
  if (SerialBT.available()) {   // 폰에서 보낸 문자가 있으면
    char str = SerialBT.read(); // 그 문자를 저장함
    
    if (str == '1') { // 보낸 문자가 1이면
      int val = analogRead(PIN_LM35); // 온도를 가져옴
      float temp = ((5.0 + val + 100.0) / 1024.0) + 20; // 섭씨로 계산
      SerialBT.print("Current Temperature: "); // 폰에 출력
      SerialBT.println(temp);
    }
    else if (str == '2') {  // 보낸 문자가 2면
      distance sensor();    // 거리 측정
      if (distance <= 10) { // 10cm 이내에 물체가 있다면
        SerialBT.println("wait...I'm checking.");
        delay(5000);         // 5초 후에
        distance = sensor(); // 다시 거리 측정
        if (distance > 10) {             // 10cm이내에 없다면
          SerialBT.println("NO exists"); // 없다 출력
          return;                        // 처음으로
        }
        //5초 후에도 10cm이내에 있다면
        SerialBT.println("exists");      // 있다 출력
      } else {
        // 처음부터 10cm이내에 없다면 
        SerialBT.println("NO exists");   // 없다 출력
        return;                          // 처음으로
      }
  } else {
    // 1과 2 이외의 문자를 보내면
    SerialBT.println("retry");
    }
  }
  delay(20);
}

  
float sensor() {
  // 초음파 거리 측정
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  //거리 변수에 저장
  unsigned long duration = pulseIn(ECHO, HIGH);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)으로 거리 계산
  return ((float)(340 * duration)/10000) / 2; //cm단위
}