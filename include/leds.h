#ifndef LEDS_H
#define LEDS_H

#include "platform.h"

#include <NeoPixelBrightnessBus.h>

#if LED_TYPE == LED_TYPE_RGBW
NeoPixelBrightnessBus<NeoGrbwFeature, NeoEsp8266Dma800KbpsMethod> strip(NUM_LEDS, 0);
#define LED_COLOR_METHOD RgbwColor
#else
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> strip(NUM_LEDS, 0);
#define LED_COLOR_METHOD RgbColor
#endif

struct Pixel_t
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
};

Pixel_t canvas[NUM_LEDS];

void initPixels()
{
    strip.Begin();
    strip.Show();
    strip.SetBrightness(127);

    for (int p = 0; p < NUM_LEDS; p++)
    {
        canvas[p].R = 0;
        canvas[p].G = 0;
        canvas[p].B = 0;
        canvas[p].W = 0;
    }
}

void pushPixels()
{
    for (int p = 0; p < NUM_LEDS; p++)
    {
#if LED_TYPE == LED_TYPE_RGBW
        LED_COLOR_METHOD c = LED_COLOR_METHOD(canvas[p].R, canvas[p].G, canvas[p].B, canvas[p].W);
#else
        LED_COLOR_METHOD c = LED_COLOR_METHOD(canvas[p].R, canvas[p].G, canvas[p].B);
#endif
        strip.SetPixelColor(p, c);
    }

    strip.Show();
}

void fadePixel(int p)
{
    canvas[p].R *= FADE_CONSTANT;
    canvas[p].G *= FADE_CONSTANT;
    canvas[p].B *= FADE_CONSTANT;
    canvas[p].W *= FADE_CONSTANT;
}

void setPixel(int p, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t w = 0)
{
    canvas[p].R = r;
    canvas[p].G = g;
    canvas[p].B = b;
    canvas[p].W = w;
}

// Fill up 75% (default) of the LED array with the specified colour

void fillColour(uint8_t r, uint8_t g, uint8_t b, float factor = PROGRESSIVE_FACTOR, int amount = NUM_LEDS)
{
    int cap = (factor * amount);

    for (int i = 0; i < cap; i++)
    {
        int p = random(0, amount);

        canvas[p].R = r;
        canvas[p].G = g;
        canvas[p].B = b;
    }

    pushPixels();
}

void analogWhite(uint8_t white)
{
#ifdef ANALOG_WHITE
    analogWrite(WHITE_PIN, white * (PWM_RANGE_FULL / 256));
#endif
}

void fillWhite(uint8_t white, int amount = NUM_LEDS)
{
    for (int p = 0; p < amount; p++)
    {
        canvas[p].W = white;
    }

    pushPixels();

    analogWhite(white);
}

#endif