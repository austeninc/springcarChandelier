#include <Adafruit_CircuitPlayground.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN 12
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define BRIGHTNESS 55
int8_t brightCustom = 55;

// start of data copied from LED Mapper:

#define NUM_LEDS 60

byte coordsX[NUM_LEDS] = { 0, 7, 15, 22, 29, 36, 44, 51, 58, 66, 73, 80, 87, 95, 102, 109, 117, 124, 131, 138, 146, 138, 131, 124, 131, 138, 146, 153, 146, 138, 131, 124, 131, 138, 146, 138, 131, 124, 131, 138, 131, 124, 131, 138, 146, 153, 160, 168, 175, 182, 189, 197, 204, 211, 219, 226, 233, 240, 248, 255 };
byte coordsY[NUM_LEDS] = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 244, 233, 222, 211, 200, 188, 177, 166, 155, 144, 133, 122, 111, 100, 89, 78, 67, 55, 44, 33, 22, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte angles[NUM_LEDS] = { 233, 232, 231, 229, 228, 226, 225, 223, 221, 219, 217, 214, 212, 209, 205, 202, 199, 195, 191, 188, 184, 187, 191, 196, 191, 185, 176, 165, 167, 172, 191, 0, 64, 83, 88, 74, 64, 57, 64, 69, 64, 60, 64, 67, 70, 74, 77, 80, 83, 85, 88, 90, 92, 94, 96, 97, 99, 100, 101, 103 };
byte radii[NUM_LEDS] = { 255, 245, 235, 225, 215, 206, 197, 188, 180, 172, 164, 158, 151, 146, 141, 138, 135, 134, 133, 134, 135, 121, 109, 97, 85, 74, 65, 60, 44, 27, 12, 12, 12, 27, 44, 50, 60, 74, 85, 97, 109, 121, 133, 146, 147, 150, 153, 157, 162, 168, 174, 181, 189, 197, 205, 214, 223, 232, 242, 252 };

// end of data copied from LED Mapper

CRGB leds[NUM_LEDS];

#define FRAMES_PER_SECOND 120
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

uint8_t offset = 0; // rotating "base color" used by many of the patterns
uint8_t speed = 5;

void setup()
{
  //  delay(3000); // 3 second delay for recovery

  Serial.begin(9600);

  CircuitPlayground.begin();

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setCorrection(TypicalSMD5050);

  FastLED.setBrightness(BRIGHTNESS);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList patterns = {

    inwardPalette
    // 2D map examples:
    //
    /*
    clockwisePalette,
    counterClockwisePalette,
    outwardPalette,
    inwardPalette,
    northPalette,
    northEastPalette,
    eastPalette,
    southEastPalette,
    southPalette,
    southWestPalette,
    westPalette,
    northWestPalette,
    */
    // standard FastLED demo reel examples:
    //  rainbow,
    //  rainbowWithGlitter,
    //  confetti,
    //  sinelon,
    //  juggle,
    //  bpm
};

const uint8_t patternCount = ARRAY_SIZE(patterns);

uint8_t currentPatternIndex = 0; // Index number of which pattern is current

CRGBPalette16 IceColors_p = CRGBPalette16(CRGB::Black, CRGB::Blue, CRGB::Aqua, CRGB::White);

// Gradient palette "bhw4_057_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw4/tn/bhw4_057.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw4_057_gp ) {
    0,   6,  0,  1,
   22,  17,  0,  1,
   58,  20,  1,  2,
   91,  75,  0, 12,
  127, 199,  1, 41,
  204,  17,  0,  1,
  255,   6,  0,  1};

  // Gradient palette "bhw1_04_gp", originally from
    // http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_04.png.index.html
    // converted for FastLED with gammas (2.6, 2.2, 2.5)
    // Size: 20 bytes of program space.

    DEFINE_GRADIENT_PALETTE( bhw1_04_gp ) {
    0, 229,227,  1,
    15, 227,101,  3,
    142,  40,  1, 80,
    198,  17,  1, 79,
    255,   0,  0, 45};

    // Gradient palette "purplefly_gp", originally from
    // http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/purplefly.png.index.html
    // converted for FastLED with gammas (2.6, 2.2, 2.5)
    // Size: 16 bytes of program space.
    DEFINE_GRADIENT_PALETTE( purplefly_gp ) {
        0,   0,  0,  0,
    63, 239,  0,122,
    191, 252,255, 78,
    255,   0,  0,  0};

    // Gradient palette "Sunset_Real_gp", originally from
    // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
    // converted for FastLED with gammas (2.6, 2.2, 2.5)
    // Size: 28 bytes of program space.

    DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
    22, 179, 22,  0,
    51, 255,104,  0,
    85, 167, 22, 18,
    135, 100,  0,103,
    198,  16,  0,130,
    255,   0,  0,160};


const CRGBPalette16 palettes[] = {
    RainbowColors_p,
    CloudColors_p,
    LavaColors_p,
    bhw4_057_gp,
    bhw1_04_gp,
    OceanColors_p,
    ForestColors_p,
    purplefly_gp,
    PartyColors_p,
    Sunset_Real_gp,
    HeatColors_p,
    IceColors_p,
};

const uint8_t paletteCount = ARRAY_SIZE(palettes);

uint8_t currentPaletteIndex = 0;
CRGBPalette16 currentPalette = palettes[currentPaletteIndex];

void loop()
{
    // Call the current pattern function once, updating the 'leds' array
    patterns[currentPatternIndex]();

    offset = beat8(speed);

    // Detect Button
    if ( CircuitPlayground.rightButton() ) {
      nextPalette(); // change patterns periodically
      delay(300);
      while ( CircuitPlayground.rightButton() ) { 
        /*if ( brightCustom = 255 ) { brightCustom = 255; }
        brightCustom = (brightCustom + 1);
        Serial.println(brightCustom);
        FastLED.setBrightness( brightCustom );
        patterns[currentPatternIndex]();
        FastLED.delay(1000 / FRAMES_PER_SECOND);
        */
        delay(100);
       };
      
    }
    if ( CircuitPlayground.leftButton() ) {
      lastPalette(); // change patterns periodically
      delay(300);
      while ( CircuitPlayground.leftButton() ) { 
        /*
        if ( brightCustom = 1 ) { brightCustom = 1; }
        brightCustom = (brightCustom - 1);
        Serial.println(brightCustom);
        FastLED.setBrightness( brightCustom );
        patterns[currentPatternIndex]();
        //FastLED.show();
        FastLED.delay(1000 / FRAMES_PER_SECOND);
        */
       delay(100);
      }
    }

    // send the 'leds' array out to the actual LED strip
    // FastLED.show(); called automatically, internally by FastLED.delay below:

    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  currentPatternIndex = (currentPatternIndex + 1) % patternCount;
}

void nextPalette()
{
  // add one to the current palette number, and wrap around at the end
  currentPaletteIndex = (currentPaletteIndex + 1) % paletteCount;
  currentPalette = palettes[currentPaletteIndex];
}

void lastPalette() {
    // add one to the current palette number, and wrap around at the end
    if ( currentPaletteIndex = 0 ) {
        currentPaletteIndex = paletteCount - 1;
    }
  currentPaletteIndex = (currentPaletteIndex - 1);
  currentPalette = palettes[currentPaletteIndex];
}

void clockwisePalette()
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = ColorFromPalette(currentPalette, offset + angles[i]);
  }
}

void beatSin8() {
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(currentPalette, coordsX[i], beatsin8(speed*40, 0, 255, 0, coordsX[i] + coordsY[i]));
    }
}

void physicalOrder() {
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(currentPalette, i - offset);
    }
}

void inwardPalette()
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = ColorFromPalette(currentPalette, offset + radii[i]);
  }
}