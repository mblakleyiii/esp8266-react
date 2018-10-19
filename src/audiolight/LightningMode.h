#ifndef LIGHTNING_MODE_H
#define LIGHTNING_MODE_H

#include <Arduino.h>
#include <FastLed.h>

#include <audiolight/AudioLightMode.h>
#include <audiolight/JsonUtil.h>

class LightningMode : public AudioLightMode {

private:
  enum class State { IDLE, INITIALIZED, RUNNING };
  boolean _refresh = true;

  // TODO: channels to listen on
  uint8_t _threshold = 50; // initially we'll work with a simple threshold level for triggering a strike
                           // in the future this could be take into account the background noise to make
                           // sure a "significant" change is detected, which may eliminate this setting
  uint8_t _flashes = 8;    //the upper limit of flashes per strike

  // STATE...
  State _state = State::IDLE;
  uint8_t _ledstart; // Starting location of a flash
  uint8_t _ledlen; // Length of a flash
  uint16_t _dimmer = 1; // State for dimming initial flash by a factor
  uint8_t _flashCounter = 0;
  uint8_t _numFlashes = 0;

  // pause tracking
  unsigned long _waitStartedAt;
  uint16_t _waitDuration;

public:
  LightningMode(CLEDController *ledController, CRGB *leds, uint16_t numLeds, uint16_t *frequencies)
      : AudioLightMode(ledController, leds, numLeds, frequencies){};
  String getId();
  void tick();
  void enable();
  void updateConfig(JsonObject &root);
  void writeConfig(JsonObject &root);
  boolean isWaitTimeElapsed();
  void resetWaitTime();
};

#endif
