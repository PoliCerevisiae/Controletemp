/ Teste do sensor de temperatura e umidade DHT11 com exibição no display
// Escrito por P&D - PoliCerevisiae

// É requerido as seguintes bibliotecas:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include "DHT.h"
#include "max6675.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Insira as especificações:
const int buttonPin = 2;
int buttonState = 0;
int iniciou = 0;
const int dt = 2000;       // Intervalo entre as medições. Mínimo de 250 millisegundos
const int pinoDHT = 7;     // Pino digital conectado ao DHT11, utilize somente os pinos 3, 4, 5, 12, 13 ou 14
int tempo = 0;             // Tempo em que a medição é realizada
const int thermoDO = 8;    // Pino digital conectado a porta SO do MAX6675
const int thermoCS = 9;    // Pino digital conectado a porta CS do MAX6675
const int thermoCLK = 10;  // Pino digital conectado a porta SCK do MAX6675

#define DHTPIN pinoDHT
#define DHTTYPE DHT11
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.

DHT dht(DHTPIN, DHTTYPE);

const byte SCREEN_WIDTH = 128;  // OLED display width, in pixels
const byte SCREEN_HEIGHT = 64;  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
const int OLED_RESET = -1;  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  // Inicializa Termopar
  Serial.begin(9600);
  delay(500);
  dht.begin();
  pinMode(buttonPin, INPUT);

  // Inicializa OLED com endereço I2C 0x3C (para 128x64)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

}

void loop() {
  // Wait a few seconds between measurements.
  delay(dt);
  display.clearDisplay();
  buttonState = digitalRead(buttonPin);
  if (iniciou == 1 || buttonState == 1)       {
    iniciou = 1;

    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read external temperature as Celsius (the default)
    float text = dht.readTemperature();
    round(text);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(text)) {
      Serial.print(F("Falha na leitura do sensor DHT11"));
      return;
    }
    Serial.print(1.02 * thermocouple.readCelsius() - 2.88);
    Serial.print(",");
    Serial.print(0.921 * text - 2.36);
    Serial.print(",");
    Serial.print(0.948 * h + 6.68);

    float ti = 1.02 * thermocouple.readCelsius() - 2.88;
    float te = 0.921 * text - 2.36;
    float u = 0.948 * h + 6.68;
    
    display.setTextSize(2);
    display.setTextColor(WHITE);    
    display.setCursor(0, 0);
    display.println("Cerevisiae");
    display.print("Ti:");
    display.println(ti);
    display.print("Te:");
    display.println(te);
    display.print("U:");
    display.println(u);
    display.display();
  }
  display.display();  
}
