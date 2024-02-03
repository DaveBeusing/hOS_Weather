/*
 *
 * NodeMCU Amica ESP8266 ESP-12F
 * -> https://www.amazon.de/gp/B0754HWZSQ
 *
 * (c) 2020 Dave Beusing <david.beusing@gmail.com>
 *
 * BME280 at i2c address 0x76
 * 128x64 OLED at i2c address 0x3C
 *
 * variants/nodemcu/pins_arduino.h
 * #define LED_BUILTIN 2
 * #define LED_BUILTIN_AUX 16
 * #define PIN_WIRE_SDA (4)
 * #define PIN_WIRE_SCL (5)
 *
 * Checkout alternative BME280 Library prvoided by cactus.io
 * -> http://cactus.io/hookups/sensors/barometric/bme280/hookup-arduino-to-bme280-barometric-pressure-sensor
 */


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define SCREEN_RESET  -1      // OLED reset pin (internal reset button)
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_RESET);


#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;


void setup(){

  Serial.begin(115200);   //init BAUDRATE 115.200
  while(!Serial);         //time to get serial up & running
  delay(1000);            //wait for 1 more seconds


  pinMode(LED_BUILTIN_AUX, OUTPUT);   //set pin16 to output (internal LED)
  digitalWrite(LED_BUILTIN, HIGH);    //set pin16 to high (internal LED active)


  Serial.println(" init SSD1306_OLED...");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 initialization failed"));
    for(;;); //wait here -> loop forever
  }

  Serial.println(" init BME280...");
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);//wait here -> loop forever
  }


  //wait 2secs and proceed
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);


}


void loop(){

  display.clearDisplay();
 // display temperature
 display.setTextSize(1);
 display.setCursor(0,0);
 display.print("Temperature: ");
 display.setTextSize(2);
 display.setCursor(0,10);
 display.print(String(bme.readTemperature()));
 display.print(" ");
 display.setTextSize(1);
 display.cp437(true);
 display.write(167);
 display.setTextSize(2);
 display.print("C");

 // display humidity
 display.setTextSize(1);
 display.setCursor(0, 35);
 display.print("Humidity: ");
 display.setTextSize(2);
 display.setCursor(0, 45);
 display.print(String(bme.readHumidity()));
 display.print(" %");

 display.display();


Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();


 delay(1000);
}
