#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char song[40] = "";
char artist[40] = "";
char buffer[100];
byte bufferIndex = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(10, 28);
  display.println("Esperando musica...");
  display.display();
}

void drawScreen() {

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Header
  display.setTextSize(1);
  display.setCursor(30, 2);
  display.print("NOW PLAYING");

  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

  // Canción (centrada)
  display.setTextSize(2);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(song, 0, 0, &x1, &y1, &w, &h);

  int songX = (SCREEN_WIDTH - w) / 2;
  if (songX < 0) songX = 0;

  display.setCursor(songX, 18);
  display.print(song);

  // Artista (centrado)
  display.setTextSize(1);
  display.getTextBounds(artist, 0, 0, &x1, &y1, &w, &h);

  int artistX = (SCREEN_WIDTH - w) / 2;
  if (artistX < 0) artistX = 0;

  display.setCursor(artistX, 46);
  display.print(artist);

  display.display();
}

void parseLine(char* line) {

  char* token = strtok(line, "|");
  if (!token) return;
  strncpy(song, token, sizeof(song) - 1);
  song[sizeof(song) - 1] = '\0';

  token = strtok(NULL, "|");
  if (!token) return;
  strncpy(artist, token, sizeof(artist) - 1);
  artist[sizeof(artist) - 1] = '\0';

  drawScreen();  
}

void loop() {

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      buffer[bufferIndex] = '\0';
      parseLine(buffer);
      bufferIndex = 0;
    } else {
      if (bufferIndex < sizeof(buffer) - 1) {
        buffer[bufferIndex++] = c;
      }
    }
  }
}