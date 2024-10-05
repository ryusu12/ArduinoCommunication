#include <SPI.h>
#include <MFRC522.h>

// 연결 핀 설정
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); // 컴퓨터와 통신 속도 설정
  SPI.begin(); // SPI 초기화
  mfrc.PCD_Init(); // MFRC 초기화
}

void loop() {
  // 카드가 접촉되지 않거나 인식되지 않으면 return
  if (!mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial()) {
    delay(500);
    return;
  }

  Serial.print("Card UID: ");
  // 읽은 UID를 출력
  for (byte i = 0; i < mfrc.uid.size; i++) {
    Serial.print(mfrc.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println();
}
