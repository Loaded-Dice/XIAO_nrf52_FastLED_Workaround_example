/*
Physical Microcontroller XIAO nRF52840 BLE Sense
Core & version: Seeed nRF52 Boards 1.1.8  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 --> don't choose mbed enabled version!
FastLED version = 3.6.0 https://github.com/FastLED/FastLED
Adafruit NeoPixel version = 1.11.0 https://github.com/adafruit/Adafruit_NeoPixel

Tested RGB Led Type: WS2812B (common type with 4 pins Vcc,Gnd,Din,Dout)

for other RGB Leds you might have to change "NEO_GRB + NEO_KHZ800"

  Everything that begins with leds[]... is regarding  FastLED array and library
  and everything that begins with strip. is regarding the Neopixel Led Array and data
 */



#define LED_PIN     D1 // your Led Data Pin
#define NUM_LEDS   34 // number of LEDs
#define DELAYMS_SHOWLED   25 // 100Hz
#define SIZE(ARRAY)    (sizeof(ARRAY) / sizeof(ARRAY[0]))

#include <FastLED.h> 
FASTLED_USING_NAMESPACE
#include <colorpalettes.h>

#include <Adafruit_NeoPixel.h>

uint8_t brightness = 60;

CRGB leds[NUM_LEDS]; // create virtual FastLED LED Strip with NUM_LEDS

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);//create adafruit Neopixel LED strip with also NUM_LEDS

void setup() {
  strip.begin();
  strip.setBrightness(brightness);
  ledsClear(); // Initialize all pixels to 'off'
}

void loop() {
  EVERY_N_MILLIS(DELAYMS_SHOWLED) {
    
    //uncomment rainbow(); and comment out ledPlasma(); 
    //for standard FastLED rainbow animation
    
    ledPlasma();
    //rainbow(); 

    //the above funtions will fill the CRGB leds[NUM_LEDS] array of fastLed which is attached to no pin  
    // now we copy the the CRGB data to the Neopixel Array and show(push to Leds) the data 
    ledsCopyAndShow();
    
  }
}
// inoise8 will generate a 2D noisefield
void ledPlasma(){
  int zoom = 60; // try values between 20 and 80 to zoom in or out into the plasma noise field
  float speedFract = 5 ;// increase to go slower , decrease to move the noise faster
  uint16_t aniSpeed = millis() / speedFract;  
  for( int i = 0; i< NUM_LEDS; i++){
    int xPos = 0; 
    int yPos = i;
    byte noises =  inoise8 (yPos * zoom, xPos * zoom, aniSpeed);
    leds[i] = ColorFromPalette (RainbowColors_p , noises, 255 );//  (color palette  ,rainbow color index, brightness)
  }
}

void rainbow() {  
  static uint8_t gHue = 0;
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } 
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
  }

void ledsCopyAndShow(){
  for(int i = 0; i < NUM_LEDS; i++){ 

      //we use --> strip.setPixelColor(led_index, r_val, g_val, b_val); 
      // and set the R/G/B values to the R/G/B values of the fastLED Array
      
    strip.setPixelColor(i, leds[i].r, leds[i].g, leds[i].b);   
                        // leds[i] --> fastLED pixel number i 
    }
  strip.show();
}

void ledsClear(){fill_solid(leds, NUM_LEDS, CRGB::Black); ledsCopyAndShow();} 
