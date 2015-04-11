# meteo
Home meteo

## Datasheets
### LED displays
One 4-digit 7-segment LED display like [this](http://www.kingbrightusa.com/images/catalog/SPEC/CA56-12SRWA.pdf).

Or four single digit numeric display like [this one](http://files.amperka.ru/datasheets/SC56-11.pdf).

### Sensor
Temperature and humidity sensor [DHT22](https://www.adafruit.com/datasheets/DHT22.pdf).

## Libraries for DHT22 sensor

https://github.com/ringerc/Arduino-DHT22

http://playground.arduino.cc/Main/DHTLib (?)

## Output
Temperature output samples: " 0.1°", "-0.1°", " 1.2°", "-1.2°", "12.3°", "-12°", "123°". For temperatures less than 99° and greater than 999° the output will be "Err°".

Humidity output samples: " 9.9H", "47.8H", "99.9H", "100H".

Error codes: "Err5", "Err°".

## Error codes
* Err1: BUS hung
* Err2: Sensor is not present
* Err3: ACK time out
* Err4: Sync Timeout
* Err5: Data Timeout
* Err6: Checksum error
* Err7: Polled to quick
* Err°: Too long temperature string
