const int ledPin = 13;

void setup() {
  Serial.begin(9600); // 시리얼 통신 속도 설정
  pinMode(ledPin, OUTPUT); //LED를 출력으로 설정
}

void loop() {
    if(Serial.available()) {
      char readChar = Serial.read(); // PC에서 문자 읽기

      if (readChar == 'A') {
        digitalWrite(ledPin, HIGH); // LED 켜기
        Serial.println("LED ON") // PC로 상태 메시지 전송
          
      } else if (readChar == 'B') {
        digitalWrite(ledPin, LOW); // LED 끄기
        Serial.println("LED OFF") // PC로 상태 메시지 전송
      }
    }
}
