// arduino-oled-ssd130x-tester

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DigitalButton.h>

constexpr uint8_t PIN_BUTTON = 29;
constexpr uint8_t PIN_SDA = 4;
constexpr uint8_t PIN_SCL = 5;

constexpr uint8_t DISPLAY_WIDTH = 128;
constexpr uint8_t DISPLAY_HEIGHT = 64;
constexpr int8_t OLED_RESET = -1;
constexpr uint8_t DISPLAY_ADDRESS = 0x3C;

constexpr char DISPLAY_TEXT[] = "OLED SSD130x Tester";
constexpr uint8_t TEXT_SIZE = 1;
constexpr uint8_t CHAR_WIDTH = 6 * TEXT_SIZE;
constexpr uint8_t CHAR_HEIGHT = 8 * TEXT_SIZE;

enum class Pattern : uint8_t {
  CENTERED_TEXT,
  FILLED_SCREEN,
  TRIANGLE_TOP_LEFT,
  TRIANGLE_TOP_RIGHT,
  TRIANGLE_BOTTOM_RIGHT,
  TRIANGLE_BOTTOM_LEFT,
  COUNT,
};

DigitalButton button(PIN_BUTTON, true);
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);

Pattern currentPattern = Pattern::CENTERED_TEXT;

void setup()
{
  Serial.begin(115200);
  while (!Serial.available() && millis() < 5000)
  {
    delay(100);
  }

  button.begin();

  Wire.setSDA(PIN_SDA);
  Wire.setSCL(PIN_SCL);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
    {
      delay(10);
    }
  }

  display.display();
  delay(3000);

  drawCurrentPattern();
}

void loop()
{
  button.update();

  if (button.isClicked())
  {
    currentPattern = static_cast<Pattern>((static_cast<uint8_t>(currentPattern) + 1) % static_cast<uint8_t>(Pattern::COUNT));
    drawCurrentPattern();
  }
}

void drawCurrentPattern()
{
  switch (currentPattern)
  {
  case Pattern::CENTERED_TEXT:
    drawCenteredText();
    break;
  case Pattern::FILLED_SCREEN:
    drawFilledScreen();
    break;
  case Pattern::TRIANGLE_TOP_LEFT:
    drawTriangleTopLeft();
    break;
  case Pattern::TRIANGLE_TOP_RIGHT:
    drawTriangleTopRight();
    break;
  case Pattern::TRIANGLE_BOTTOM_RIGHT:
    drawTriangleBottomRight();
    break;
  case Pattern::TRIANGLE_BOTTOM_LEFT:
    drawTriangleBottomLeft();
    break;
  default:
    break;
  }
}

void drawCenteredText() {
  const uint8_t textWidth = CHAR_WIDTH * (sizeof(DISPLAY_TEXT) - 1);
  const int16_t x = (DISPLAY_WIDTH - textWidth) / 2;
  const int16_t y = (DISPLAY_HEIGHT - CHAR_HEIGHT) / 2;

  display.clearDisplay();
  display.setTextSize(TEXT_SIZE);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x, y);
  display.println(DISPLAY_TEXT);
  display.display();
}

void drawFilledScreen() {
  display.fillScreen(SSD1306_WHITE);
  display.display();
}

void drawTriangleTopLeft() {
  constexpr int16_t left = 0;
  constexpr int16_t top = 0;
  constexpr int16_t right = DISPLAY_WIDTH - 1;
  constexpr int16_t bottom = DISPLAY_HEIGHT - 1;

  display.clearDisplay();
  display.drawRect(left, top, DISPLAY_WIDTH, DISPLAY_HEIGHT, SSD1306_WHITE);
  display.fillTriangle(left, top, right, top, left, bottom, SSD1306_WHITE);
  display.display();
}

void drawTriangleTopRight() {
  constexpr int16_t left = 0;
  constexpr int16_t top = 0;
  constexpr int16_t right = DISPLAY_WIDTH - 1;
  constexpr int16_t bottom = DISPLAY_HEIGHT - 1;

  display.clearDisplay();
  display.drawRect(left, top, DISPLAY_WIDTH, DISPLAY_HEIGHT, SSD1306_WHITE);
  display.fillTriangle(left, top, right, top, right, bottom, SSD1306_WHITE);
  display.display();
}

void drawTriangleBottomLeft() {
  constexpr int16_t left = 0;
  constexpr int16_t top = 0;
  constexpr int16_t right = DISPLAY_WIDTH - 1;
  constexpr int16_t bottom = DISPLAY_HEIGHT - 1;

  display.clearDisplay();
  display.drawRect(left, top, DISPLAY_WIDTH, DISPLAY_HEIGHT, SSD1306_WHITE);
  display.fillTriangle(left, top, left, bottom, right, bottom, SSD1306_WHITE);
  display.display();
}

void drawTriangleBottomRight() {
  constexpr int16_t left = 0;
  constexpr int16_t top = 0;
  constexpr int16_t right = DISPLAY_WIDTH - 1;
  constexpr int16_t bottom = DISPLAY_HEIGHT - 1;

  display.clearDisplay();
  display.drawRect(left, top, DISPLAY_WIDTH, DISPLAY_HEIGHT, SSD1306_WHITE);
  display.fillTriangle(right, top, left, bottom, right, bottom, SSD1306_WHITE);
  display.display();
}
