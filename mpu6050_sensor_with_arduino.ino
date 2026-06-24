#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  mpu.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.display();
}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  display.clearDisplay();   // IMPORTANT
  display.fillRect(0,0,128,64,BLACK); // 🔥 FORCE CLEAN SCREEN

  display.setTextSize(1);
  display.setTextColor(WHITE);

  // ACCELERATION LEFT
  display.setCursor(0, 0);
  display.print("AX:"); display.print(a.acceleration.x,1);

  display.setCursor(0, 10);
  display.print("AY:"); display.print(a.acceleration.y,1);

  display.setCursor(0, 20);
  display.print("AZ:"); display.print(a.acceleration.z,1);

  // GYRO RIGHT (safe spacing)
  display.setCursor(75, 0);
  display.print("GX:"); display.print(g.gyro.x,1);

  display.setCursor(75, 10);
  display.print("GY:"); display.print(g.gyro.y,1);

  display.setCursor(75, 20);
  display.print("GZ:"); display.print(g.gyro.z,1);

  // TEMPERATURE (bottom clean area)
  display.setTextSize(2);
  display.setCursor(10, 40);
  display.print("T:");
  display.print(temp.temperature,1);
  display.print("C");

  display.display();

  delay(300);
}
