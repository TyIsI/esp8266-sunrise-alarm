#include "platform.h"

void setup()
{
#ifdef WHITE_PIN
  analogWriteRange(PWM_RANGE_FULL);
  pinMode(WHITE_PIN, OUTPUT);
#endif

  digitalWrite(RED_LED_PIN, LOW);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, LOW);

  Serial.begin(115200);

  randomSeed(analogRead(0));

  loadSettings();

  initPixels();

  fillColour(0, 0, 0);

  WiFi.mode(WIFI_AP_STA);

  WiFi.softAP("Internet Lightbox", WEBSERVER_PASSWORD);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  server.on("/settings", handleSettings);
  server.on("/restart", handleRestart);
  server.on("/status", handleStatus);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}

void loop()
{
  // Connect to wifi if not already
  if (WiFi.status() != WL_CONNECTED)
  {
    flash(3);
    Serial.println("Connecting to wifi...");
    delay(1000);
    return;
  }

  // Handle incoming NTP packet
  if (udp.parsePacket())
  {
    Serial.print("packet received after ");
    Serial.print(millis() - lastNTPRequest);
    Serial.print("ms... ");
    setTime(readNTPpacket(settings.timeZone));
    Serial.println("DONE");
    lastNTPSync = millis();
    Serial.println(elapsedSecsToday(now()));
    Serial.println(now());
  }

  // Handle web request
  server.handleClient();

  // Run CRON algorithm, but only if we have sync'd to NTP
  if (lastNTPSync != 0)
  {
    if (elapsedSecsToday(now()) > settings.offTime)
    {
      if (animationState == ANIM_STATE_SUNRISE)
      {
        Serial.println("Start fadeout");
        animationState = ANIM_STATE_FADEOUT;
        animationStartTime = millis();
      }
    }
    else if (elapsedSecsToday(now()) > settings.onTime)
    {
      if (animationState == ANIM_STATE_OFF)
      {
        Serial.println("Start sunrise");
        animationState = ANIM_STATE_SUNRISE;
        animationStartTime = millis();
      }
    }
  }

  // Animate
  if (animationState == ANIM_STATE_SUNRISE && (millis() - lastAnimationUpdate > ANIMATION_INTERVAL))
  {
    if (!drawSunriseFrame())
    {
      Serial.println("Finished sunrise");
      animationState = ANIM_STATE_OFF;
      animationStartTime = 0;
    }
    lastAnimationUpdate = millis();
  }
  if (animationState == ANIM_STATE_FADEOUT && (millis() - lastAnimationUpdate > ANIMATION_INTERVAL))
  {
    if (!drawFadeoutFrame())
    {
      Serial.println("Finished fadeout");
      animationState = ANIM_STATE_OFF;
      animationStartTime = 0;
    }
    lastAnimationUpdate = millis();
  }

  // Send NTP packet at regular intervals,
  // or more frequently if we haven't had a successful sync in the last 10 intervals (or ever)
  if (
    (millis() - lastNTPRequest > NTP_SYNC_INTERVAL) ||
    (((lastNTPSync == 0) || (millis() - lastNTPSync > NTP_SYNC_INTERVAL * 10)) && millis() - lastNTPRequest > 1000))
  {
    flash(2);
    lastNTPRequest = millis();
    sendNTPpacket();
  }
}
