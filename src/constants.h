#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NTP_SYNC_INTERVAL (600000)

#define ANIMATION_INTERVAL (1000)

enum animationStates
{
    ANIM_STATE_OFF,
    ANIM_STATE_SUNRISE,
    ANIM_STATE_FADEOUT
};

#define DEVICE_NAME "partycat"

#define PWM_RANGE_FULL (1024)

#define FADE_CONSTANT (0.97)

#define WHITE_OFFSET (300.)

#define ROW_FRAME_LAG (90)

#define PROGRESSIVE_FACTOR 0.33

const char *ntpServerName = "time.nist.gov";

enum fillStrategies
{
    STRATEGY_FILL,
    STRATEGY_INCREASE
};

#define LED_TYPE_RGB    0
#define LED_TYPE_RGBW   1

#define SUNRISE_CLASSIC 0
#define SUNRISE_NEW   1

#define RED_LED_PIN LED_BUILTIN 

#endif