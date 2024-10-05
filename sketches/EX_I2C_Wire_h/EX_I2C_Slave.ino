/* Slave 코드 */
#include <Wire.h>
#define SLAVE 7 //Slave 주소

void setup() {
  Wire.begin(SLAVE);             // 슬레이브 주소 7로 초기화
  Wire.onRequest(requestEvent);
} // 마스터에서 요청이 오면 requestEvent 함수 호출

void loop() {
  delay(1000);  //1초 대기
}

void requestEvent() {
  Wire.write("A");
  Wire.write("B");
} // 마스터의 요청이 있을 때 AB를 전송
