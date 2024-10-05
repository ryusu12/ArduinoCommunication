/* Master 코드 */
#include <Wire.h>
#define SLAVE 7 //Slave 주소

void setup() {
  Wire.begin();          //마스터 주소 초기화
  Serial.begin(9600);    //시리얼 모니터 시작
}

void loop() {
  I2C_communication();
  Serial.print("\n");
  delay(1000);
}//1초씩 함수를 실행

void I2C_communication() {
  Wire.requestFrom(SLAVE, 2);
  // (주소,바이트) 지정해서 마스터에서 슬레이브로 데이터 요청 후 가져옴
  // >>> 이때 Slave에서 AB를 받아옴
  while (Wire.available()) {    // 읽을 데이터가 있다면
    char c = Wire.read();       // 문자형 변수 c에 저장
    Serial.print(c);            // 받은 문자를 시리얼 모니터에 출력
  }
}
