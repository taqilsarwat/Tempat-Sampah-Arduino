#include <Servo.h>
#include <NewPing.h>

// Pin untuk sensor HC-SR04-1
const int trigPin1 = 5;
const int echoPin1 = 3;

// Pin untuk sensor HC-SR04-2
const int TRIGGER_PIN = 10;
const int ECHO_PIN = 9;

// Pin untuk servo motor
const int servoPin = 6;

// Pin untuk buzzer
const int BUZZER_PIN = 2;

// Objek Servo
Servo myServo;

void setup() {
  Serial.begin(9600);

  // Inisialisasi pin untuk sensor HC-SR04-1
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  // Inisialisasi pin untuk sensor HC-SR04-2
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inisialisasi pin untuk buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // Inisialisasi servo
  myServo.attach(servoPin);
  myServo.write(90); // Posisi awal servo
}

void loop() {
  long duration1, duration2;
  long distance1, distance2;

  // Pengukuran jarak dengan HC-SR04-1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Pengukuran jarak dengan HC-SR04-2
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration2 = pulseIn(ECHO_PIN, HIGH);
  distance2 = duration2 * 0.034 / 2;

  Serial.print("Jarak HC-SR04-1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Jarak HC-SR04-2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Periksa jarak dari sensor HC-SR04-2 untuk mengaktifkan buzzer
  if (distance2 < 5) {
    digitalWrite(BUZZER_PIN, HIGH); // Nyalakan buzzer
    delay(500); // Tahan buzzer selama 0.5 detik
    digitalWrite(BUZZER_PIN, LOW); // Matikan buzzer
    delay(500); // Tunggu sebentar sebelum mengukur lagi
  }

  // Logika untuk HC-SR04-1 (misalnya untuk gerakan servo)
  if (distance1 < 20) {
    myServo.write(0); // Gerakkan servo ke 0 derajat (atau sesuai kebutuhan)
    delay(5000); // Tunggu 5 detik

    myServo.write(90); // Kembalikan servo ke posisi awal (90 derajat)
    delay(500); // Tunggu 0.5 detik
  }

  delay(500); // Tunggu sebentar sebelum mengukur lagi
}
