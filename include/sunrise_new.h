#ifndef SUNRISE_NEW_H
#define SUNRISE_NEW_H

#include "platform.h"

#if SUNRISE_METHOD == SUNRISE_NEW

// Generated
#define COLOR_FLOOR 240
#define COLOR_CEILING 15
#define COLOR_BARRIER 360
#define COLOR_MAX (COLOR_BARRIER + COLOR_CEILING)
#define COLOR_RANGE (COLOR_MAX - COLOR_FLOOR)
#define COLOR_SPACE COLOR_RANGE * 2 * 10

float h = 0;
float s = 0;
float l = 0;
int w = 0;
int frameCount = 0;

bool drawSunriseFrame()
{
    if (frameCount >= COLOR_SPACE)
        return false;

    Serial.print(frameCount);

    int f = frameCount % int(COLOR_SPACE);
    int o = (f / 10);

    Serial.print(" - f: " + String(f));
    Serial.print(" - o: " + String(o));

    if (o < COLOR_RANGE)
    {
        Serial.print(" - phase #1");
        h = ((COLOR_FLOOR + o) % COLOR_BARRIER) / 360.0;

        s = 1;

        if(l<0.49)
            l += 0.01;

        // if (h > COLOR_FLOOR)
        //     l = (((h - COLOR_FLOOR) / (COLOR_RANGE)) * 100.0);
        // else
        //     l = (((h + COLOR_FLOOR + COLOR_CEILING) / (COLOR_RANGE)) * 100.0) - 100;

        w = 0;
    }
    else
    {
        Serial.print(" - phase #2");
        h = ((COLOR_MAX - (o - COLOR_RANGE)) % COLOR_BARRIER) / 360.0;
        s = 1.0 - (((o - COLOR_RANGE) / COLOR_RANGE) * 1.0);

        if(f>=2200&&l<1)
            l += 0.001;
            
        // l = (l>1)?1:l;
        w = ((l-0.5)*2) * 255;
    }

    LED_COLOR_METHOD c = LED_COLOR_METHOD(HslColor(h, s, l));

    Serial.print(" - h: " + String(h));
    Serial.print(" - s: " + String(s));
    Serial.print(" - l: " + String(l));
    Serial.print(" - R: " + String(c.R));
    Serial.print(" - G: " + String(c.G));
    Serial.print(" - B: " + String(c.B));
    Serial.print(" - W: " + String(w) + " / " + String(c.W));

#if LED_TYPE == LED_TYPE_RGBW
    fillColour(c.R, c.G, c.B);
    fillWhite(w);
#else
    fillColour(c.R, c.G, c.B);
    fillWhite(w);
#endif

    Serial.println();

    frameCount++;

    return true;
}

bool drawFadeoutFrame()
{
    if (frameCount == 0)
        return false;

    if (frameCount > 300)
        frameCount = 300;

    int c = 255 * pow(FADE_CONSTANT, (300 - frameCount));
#if LED_TYPE == LED_TYPE_RGBW
    fillColour(c, c, c);
    fillWhite(c);
#else
    fillColour(c, c, c);
    fillWhite(c);
#endif

    frameCount--;

    return true;
}

#endif

#endif