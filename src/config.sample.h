#ifndef CONFIG_H
#define CONFIG_H

#include "constants.h"

#define WIFI_SSID "yourwifi"
#define WIFI_PASSWORD "yourpassword"
#define WEBSERVER_USERNAME "no"
#define WEBSERVER_PASSWORD "something"

// Start and stop times in seconds
#define TIME_ON     23400
#define TIME_OFF    28800
#define TIME_FPS    1
#define TIME_OFFSET -7

#define NUM_LEDS 120
#define LEDS_PER_ROW 24

#define SUNRISE_METHOD SUNRISE_NEW

#define LED_TYPE LED_TYPE_RGBW

// Uncomment the WHITE_PIN define if you want to use a dedicated white LED strip controlled by MOSFET
// #define WHITE_PIN 14

#endif