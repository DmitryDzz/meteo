# meteo
Home meteo

![Breadboard version](https://cloud.githubusercontent.com/assets/1957839/7219205/5116e61a-e69d-11e4-8fc7-dcfcb2617f8d.jpg)

## Datasheets
### LED displays
One 4-digit 7-segment LED display like [this](http://www.kingbrightusa.com/images/catalog/SPEC/CA56-12SRWA.pdf).

Or four single digit numeric display like [this one](http://files.amperka.ru/datasheets/SC56-11.pdf).

### Sensor
Temperature and humidity sensor [DHT22](https://www.adafruit.com/datasheets/DHT22.pdf).

## Library for DHT22 sensor
https://github.com/DmitryDzz/ArduinoLibraries/tree/master/libraries/DHTlib

This library is http://playground.arduino.cc/Main/DHTLib fork. HumidityInt10 and temperatureInt10 fields where added.

~~https://github.com/ringerc/Arduino-DHT22~~

## Output
Temperature output samples: [ 0.1°], [-0.1°], [ 1.2°], [-1.2°], [12.3°], [-12°], [123°]. For temperatures less than -99° and greater than 999° the output will be [Err°].

Humidity output samples: [ 9.9H], [47.8H], [99.9H], [100H].

Error code samples: [Err5], [Err°].

## Error codes
* Err1: Checksum error
* Err2: Time out error
* Err3: Connect error
* Err4: Ack Low error
* Err5: Ack High error
* Err°: Too long temperature string

## Pins
* DHT22 sensor: A0
* Mercury switch*: A1
* Digit 1 pin (PWM): 3
* Digit 2 pin (PWM): 5
* Digit 3 pin (PWM): 6
* Digit 4 pin (PWM): 9
* Segment A pin: 2
* Segment B pin: 8
* Segment C pin: 10
* Segment D pin: 11
* Segment E pin: 12
* Segment F pin: 7
* Segment G pin: 13
* Segment DecimalPoint pin: 4

(*) Mercury switch is connected to the input pin (INPUT_PULLUP mode) and one of GND pins. In case the switch is connected the display is off by default. It is turned on after shaking the switch for a second. And it is off again after LED_TURNED_ON_DURATION milliseconds.

## Useful constants
* AUTO_START - should be false if mercury switch is connected
* LED_TURNED_ON_DURATION - time in milliseconds the LED display is turned on after shaking
* MODE_DURATION_IN_MILLIS - temperature / humidity pause time
* READ_DELAY_IN_MILLIS - sensor read interval
* COMMON_ANODE_LED - set true for LED with common anode, false for LED with common cathode
* BRIGHTNESS - 0 is min value, 255 - max
* DIGIT_DELAY_IN_MICROSECONDS - delay to light up one digit
