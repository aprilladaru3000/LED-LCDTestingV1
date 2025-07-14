#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C untuk modul LCD 16x2

const int potentiometerPin = A0; // Pin untuk potensiometer
const int ledPinGreen = 3;       // Pin untuk LED hijau
const int ledPinYellow = 5;      // Pin untuk LED kuning
const int ledPinRed = 6;         // Pin untuk LED merah

void setup() {
  lcd.begin(16, 2);  // Inisialisasi layar LCD
  pinMode(ledPinGreen, OUTPUT); // Mengatur pin LED hijau sebagai OUTPUT
  pinMode(ledPinYellow, OUTPUT); // Mengatur pin LED kuning sebagai OUTPUT
  pinMode(ledPinRed, OUTPUT); // Mengatur pin LED merah sebagai OUTPUT
  Serial.begin(9600); // Inisialisasi komunikasi serial untuk pemantauan nilai potensiometer
}

void loop() {
  int potValue = analogRead(potentiometerPin); // Membaca nilai potensiometer
  int brightness = map(potValue, 0, 1023, 0, 255); // Mengonversi nilai potensiometer ke rentang kecerahan LED

  analogWrite(ledPinGreen, 0); // Matikan LED hijau
  analogWrite(ledPinYellow, 0); // Matikan LED kuning
  analogWrite(ledPinRed, 0); // Matikan LED merah

  if (potValue <= 340) { // 0%-33%
    analogWrite(ledPinGreen, brightness); // Nyalakan LED hijau
  } else if (potValue <= 680) { // 34%-66%
    analogWrite(ledPinGreen, brightness); // Nyalakan LED hijau
    analogWrite(ledPinYellow, brightness); // Nyalakan LED kuning
  } else if (potValue <= 1000) { // 67%-100%
    analogWrite(ledPinGreen, brightness); // Nyalakan LED hijau
    analogWrite(ledPinYellow, brightness); // Nyalakan LED kuning
    analogWrite(ledPinRed, brightness); // Nyalakan LED merah
  }

  if (potValue == 1023) { // 100%
    blinkAllLEDs(); // Kedipkan semua LED jika potensiometer mencapai nilai maksimum
  }

  displayPercentage(map(potValue, 0, 1023, 0, 100)); // Menampilkan persentase di layar LCD

  Serial.print("Nilai Potensiometer: ");
  Serial.print(potValue);
  Serial.print(", Persentase: ");
  Serial.println(map(potValue, 0, 1023, 0, 100));

  delay(100); // Menambahkan sedikit penundaan untuk stabilitas tampilan nilai potensiometer
}

void displayPercentage(int percentage) {
  lcd.clear(); // Menghapus layar LCD
  lcd.setCursor(0, 0);
  lcd.print("Persentase:");
  lcd.setCursor(0, 1);
  lcd.print(percentage);
  lcd.print("%");
}

void blinkAllLEDs() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPinGreen, HIGH);
    digitalWrite(ledPinYellow, HIGH);
    digitalWrite(ledPinRed, HIGH);
    delay(500);
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinRed, LOW);
    delay(500);
  }
}
