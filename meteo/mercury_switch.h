#ifndef mercury_switch_h
#define mercury_switch_h

#include <Arduino.h>

class MercurySwitch {
  public:
    MercurySwitch(int pin, long shakeDuration, long switchOnDuration);
    boolean isOn();
  private:
    void update(long millis);
};

#endif
