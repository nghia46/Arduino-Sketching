#include <IRremote.h>
#include <SoftwareSerial.h>
#define RECV_PIN 2
SoftwareSerial BTSerial(8, 9);  // RX | TX
IRrecv irrecv(RECV_PIN);
decode_results results;
int ledPin3 = 3;  // Chọn chân 13 để kết nối với LED
int ledPin4 = 4;
int ledPin5 = 5;
void setup() {
  Serial.begin(9600);  // Establish serial communication
  BTSerial.begin(9600);
  irrecv.enableIRIn();  // Start the receiver
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    switch (results.value) {
      case 275288430:
        digitalWrite(ledPin3, HIGH);
        break;
      case 275295570:
        digitalWrite(ledPin4, HIGH);
        break;
      case 275308830:
        digitalWrite(ledPin5, HIGH);
        break;
      // Logic tắt
      case 275266500:
        digitalWrite(ledPin5, LOW);
        break;
      case 275276190:
        digitalWrite(ledPin3, LOW);
        break;
      case 275292510:
        digitalWrite(ledPin4, LOW);
        break;
      case 275313165:
        digitalWrite(ledPin3, HIGH);  // Tắt đèn LED
        digitalWrite(ledPin4, HIGH);
        digitalWrite(ledPin5, HIGH);
        break;
      case 275307045:
        digitalWrite(ledPin3, LOW);  // Tắt đèn LED
        digitalWrite(ledPin4, LOW);
        digitalWrite(ledPin5, LOW);
        break;
    }

    irrecv.resume();  // Receive the next value
  }
  //BT
  if (BTSerial.available()) {
    String cmd = BTSerial.readStringUntil('\n');  // Đọc chuỗi cho đến khi gặp ký tự xuống dòng
    cmd.trim();                                   // Loại bỏ khoảng trắng và ký tự xuống dòng ở đầu và cuối chuỗi

    Serial.println("Received: " + cmd);

    if (cmd == "ON1") {
      digitalWrite(ledPin3, HIGH);  // Bật đèn LED
      BTSerial.println("LED ON");
      Serial.println("LED ON");
    } else if (cmd == "OFF1") {
      digitalWrite(ledPin3, LOW);  // Tắt đèn LED
      BTSerial.println("LED OFF");
      Serial.println("LED OFF");
    } else if (cmd == "ON2") {
      digitalWrite(ledPin4, HIGH);  // Tắt đèn LED
      BTSerial.println("LED 2 ON");
      Serial.println("LED 2 OFF");
    } else if (cmd == "OFF2") {
      digitalWrite(ledPin4, LOW);  // Tắt đèn LED
      BTSerial.println("LED 2 OFF");
      Serial.println("LED 2 OFF");
    } else if (cmd == "ON3") {
      digitalWrite(ledPin5, HIGH);  // Tắt đèn LED
      BTSerial.println("LED 3 ON");
      Serial.println("LED 3 OFF");
    } else if (cmd == "OFF3") {
      digitalWrite(ledPin5, LOW);  // Tắt đèn LED
      BTSerial.println("LED 5 OFF");
      Serial.println("LED 5 OFF");
    } else if (cmd == "OFF4") {
      digitalWrite(ledPin3, LOW);  // Tắt đèn LED
      digitalWrite(ledPin4, LOW);
      digitalWrite(ledPin5, LOW);
    } else if (cmd == "ON4") {
      digitalWrite(ledPin3, HIGH);  // Tắt đèn LED
      digitalWrite(ledPin4, HIGH);
      digitalWrite(ledPin5, HIGH);
    }
  }
}
