#ifndef PLATFORM_H
#define PLATFORM_H

#include "constants.h"
#include "config.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdint.h>

#define SETTINGS_VERSION "s4d3"
struct Settings {
  // Time in seconds after midnight to begin sunrise
  int onTime;

  // Time in seconds after midnight to turn off the light
  int offTime;

  // How quickly to advance the sunrise frames (default 1)
  int fps;

  // Timezone offset
  int timeZone;
} settings = {
  TIME_ON,
  TIME_OFF,
  TIME_FPS,
  TIME_OFFSET
};

#include "libdcc/webserver.h"
#include "libdcc/settings.h"
#include "animation.h"
#include "leds.h"
#include "ntp.h"
#include "sunrise_classic.h"
#include "sunrise_new.h"
#include "utils.h"

#endif