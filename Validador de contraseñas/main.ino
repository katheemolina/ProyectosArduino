#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <RTClib.h>
#include <Servo.h>

#define LED_ROJO 10
#define LED_VERDE 12
#define BUZZER 13

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;
Servo barrera;

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 5, 4, 3, 2 }; // Pines conectados a C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 9, 8, 7, 6 }; // Pines conectados a R1, R2, R3, R4 segun documentacion

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "12345"; // Contraseña inventada estatica
String inputPassword;
int intentosFallidos = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ingrese clave:");

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  barrera.attach(11);
  barrera.write(90); //para que este "cerrada la barrera inicialmente"

  if (!rtc.begin()) {
    Serial.println("No se pudo encontrar el RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("El RTC no está corriendo, ajustando la hora...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  }
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') { // El usuario presiona '#' para ingresar la contraseña
      lcd.clear();
      DateTime now = rtc.now();
      String dateTime = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " +
                        String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

      if (inputPassword == password) {
        Serial.println("Acceso permitido");
        lcd.setCursor(0, 0);
        lcd.print("Acceso permitido");
        lcd.setCursor(0, 1);
        lcd.print(dateTime);
        digitalWrite(LED_VERDE, HIGH);
        barrera.write(0); // abre 
        delay(2000); 
        barrera.write(90); // cierra 
        digitalWrite(LED_VERDE, LOW);
        intentosFallidos = 0; // reinicia el contador de intentos fallidos
      } else {
        Serial.println("Acceso denegado");
        lcd.setCursor(0, 0);
        lcd.print("Acceso denegado");
        lcd.setCursor(0, 1);
        lcd.print(dateTime);
        digitalWrite(LED_ROJO, HIGH);
        delay(2000);
        digitalWrite(LED_ROJO, LOW);
        intentosFallidos++;
      }

      if (intentosFallidos >= 3) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ALERTA!");
        lcd.setCursor(0, 1);
        lcd.print("llamar a la policia");
        digitalWrite(LED_ROJO, HIGH);
        digitalWrite(BUZZER, HIGH);
        delay(2000);
        digitalWrite(BUZZER, LOW);
        intentosFallidos = 0; // reinicia el contador de intentos fallidos después de la alerta
      } else {
        delay(2000); 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ingrese clave:");
      }
      
      inputPassword = ""; // reinicia la entrada
    } else {
      inputPassword += key; // va agregando los caracteres a la contraseña corta con # para validar
      lcd.setCursor(0, 1);
      lcd.print(inputPassword); // va mostrando la contraseña ingresada en el lcd
    }
  }
}
