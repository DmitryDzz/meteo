#include "mercury_switch.h"

int mPin;
long mShakeDuration;
const long mCheckingDuration = 500;
long mSwitchOnDuration;
int previousValue = LOW;
long mAwakingTime;
long mTurnedOnTime;

enum State { SLEEPING, AWAKING, CHECKING, TURNED_ON } mState = SLEEPING;

MercurySwitch::MercurySwitch(int pin, long shakeDuration, long switchOnDuration) {
  mPin = pin;
  mShakeDuration = shakeDuration;
  mSwitchOnDuration = switchOnDuration;
  pinMode(mPin, INPUT_PULLUP);
}

boolean MercurySwitch::isOn() {
  this->update(millis());
  return mState == TURNED_ON;
}

void MercurySwitch::update(long millis) {
  int value = digitalRead(mPin);
  
  if (mState == SLEEPING) {
    if (value != previousValue) {
      mState = AWAKING;
      mAwakingTime = millis;
    }
  } else if (mState == AWAKING) {
    if (millis >= mAwakingTime + mShakeDuration) {
      mState = CHECKING;
    }
  } else if (mState == CHECKING) {
    if (value != previousValue) {
      mState = TURNED_ON;
      mTurnedOnTime = millis;
    } else if (millis >= mAwakingTime + mShakeDuration + mCheckingDuration) {
      mState = SLEEPING;
    }
  } else if (mState == TURNED_ON) {
    if (millis >= mTurnedOnTime + mSwitchOnDuration) {
      mState = SLEEPING;
    }
  }

  previousValue = value;
}
