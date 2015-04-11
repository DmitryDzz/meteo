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

Интересный подход для DHT11: питание посадили на цифровой пин и включают только каждые 120 секунд:
http://forum.arduino.cc/index.php?topic=184356.msg1753894#msg1753894

## Ideas
### Output format
Temperature output samples: " 24*" for positive values or "-03*" for negative.

Humidity output samples: "   9H", " 78H", "100H".

Error codes: "Err1", "Err5".

## Error codes
* Err1: BUS Hung
* Err2: Not Present
* Err3: ACK time out
* Err4: Sync Timeout
* Err5: Data Timeout
* Err6: Checksum error
* Err7: Polled to quick
* Err°: Too long temperature string
