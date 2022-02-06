#ifndef UTILS_H
#define UTILS_H

#include "platform.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

String formatSettings()
{
    return String("onTime=") + String(settings.onTime) +
           String(",offTime=") + String(settings.offTime) +
           String(",fps=") + String(settings.fps) +
           String(",timeZone=") + String(settings.timeZone);
}

void handleSettings()
{
    REQUIRE_AUTH;

    for (int i = 0; i < server.args(); i++)
    {
        if (server.argName(i).equals("onTime"))
        {
            settings.onTime = server.arg(i).toFloat();
        }
        else if (server.argName(i).equals("offTime"))
        {
            settings.offTime = server.arg(i).toFloat();
        }
        else if (server.argName(i).equals("fps"))
        {
            settings.fps = server.arg(i).toInt();
        }
        else if (server.argName(i).equals("timeZone"))
        {
            settings.timeZone = server.arg(i).toInt();
        }
        else
        {
            Serial.println("Unknown argument: " + server.argName(i) + ": " + server.arg(i));
        }
    }

    saveSettings();

    String msg = String("Settings saved: ") + formatSettings();
    Serial.println(msg);
    server.send(200, "text/plain", msg);
}

void flash(int times)
{
    for (int i = 0; i < times; i++)
    {
        digitalWrite(RED_LED_PIN, HIGH);
        delay(50);
        digitalWrite(RED_LED_PIN, LOW);
        delay(100);
    }
}

#endif