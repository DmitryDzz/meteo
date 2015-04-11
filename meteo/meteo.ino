#include <DHT22.h>

const long DIGIT_DELAY_IN_MICROSECONDS = 500;
const long MODE_DURATION_IN_MILLIS = 2000; // temperature / humidity modes
const long READ_DELAY_IN_MILLIS = 5000;

const int DHT22_PIN = A0;

const int DIGIT_1_PIN = 3;
const int DIGIT_2_PIN = 5;
const int DIGIT_3_PIN = 6;
const int DIGIT_4_PIN = 9;

const int SEGMENT_A_PIN = 2;
const int SEGMENT_B_PIN = 8;
const int SEGMENT_C_PIN = 10;
const int SEGMENT_D_PIN = 11;
const int SEGMENT_E_PIN = 12;
const int SEGMENT_F_PIN = 7;
const int SEGMENT_G_PIN = 13;
const int SEGMENT_DP_PIN = 4;

const byte DIGIT_OFF = 255;
const byte DIGIT_ON = 0; // increase the value to reduce current

const short MINUS_SYMBOL = -1;
const short DEGREE_SYMBOL = -2;
const short HUMIDITY_SYMBOL = -3;
const short NOTHING_SYMBOL = -4;
const short E_SYMBOL = -5;
const short R_SYMBOL = -6;

int currentDigitIndex = 0;
const int INACTIVE = -1;
short digits[4];
boolean decimalPoints[4];

int temperature = 0; // real temperature * 10
int humidity = 0;    // real humidity * 10
long startModeMillis;
long lastReadingMillis;

enum Mode {
  TEMPERATURE, HUMIDITY
};
Mode mode;

DHT22 sensorDHT22(DHT22_PIN);

void activateDigit(int digit) {
  switch (digit) {
    case 0:
      analogWrite(DIGIT_1_PIN, DIGIT_ON);
      analogWrite(DIGIT_2_PIN, DIGIT_OFF);
      analogWrite(DIGIT_3_PIN, DIGIT_OFF);
      analogWrite(DIGIT_4_PIN, DIGIT_OFF);
      break;
    case 1:
      analogWrite(DIGIT_1_PIN, DIGIT_OFF);
      analogWrite(DIGIT_2_PIN, DIGIT_ON);
      analogWrite(DIGIT_3_PIN, DIGIT_OFF);
      analogWrite(DIGIT_4_PIN, DIGIT_OFF);
      break;
    case 2:
      analogWrite(DIGIT_1_PIN, DIGIT_OFF);
      analogWrite(DIGIT_2_PIN, DIGIT_OFF);
      analogWrite(DIGIT_3_PIN, DIGIT_ON);
      analogWrite(DIGIT_4_PIN, DIGIT_OFF);
      break;
    case 3:
      analogWrite(DIGIT_1_PIN, DIGIT_OFF);
      analogWrite(DIGIT_2_PIN, DIGIT_OFF);
      analogWrite(DIGIT_3_PIN, DIGIT_OFF);
      analogWrite(DIGIT_4_PIN, DIGIT_ON);
      break;
    default:
      analogWrite(DIGIT_1_PIN, DIGIT_OFF);
      analogWrite(DIGIT_2_PIN, DIGIT_OFF);
      analogWrite(DIGIT_3_PIN, DIGIT_OFF);
      analogWrite(DIGIT_4_PIN, DIGIT_OFF);
  }    
}

void drawDigit(short value, boolean hasDecimalPoint) {
  switch (value) {
    case R_SYMBOL:
      digitalWrite(SEGMENT_A_PIN, LOW);
      digitalWrite(SEGMENT_B_PIN, LOW);
      digitalWrite(SEGMENT_C_PIN, LOW);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, HIGH);
      digitalWrite(SEGMENT_F_PIN, LOW);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case E_SYMBOL:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, LOW);
      digitalWrite(SEGMENT_C_PIN, LOW);
      digitalWrite(SEGMENT_D_PIN, HIGH);
      digitalWrite(SEGMENT_E_PIN, HIGH);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case NOTHING_SYMBOL:
      digitalWrite(SEGMENT_A_PIN, LOW);
      digitalWrite(SEGMENT_B_PIN, LOW);
      digitalWrite(SEGMENT_C_PIN, LOW);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, LOW);
      digitalWrite(SEGMENT_G_PIN, LOW);
      break;
    case HUMIDITY_SYMBOL:
      digitalWrite(SEGMENT_A_PIN, LOW);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, HIGH);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case DEGREE_SYMBOL:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, LOW);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case MINUS_SYMBOL:
      digitalWrite(SEGMENT_A_PIN, LOW);
      digitalWrite(SEGMENT_B_PIN, LOW);
      digitalWrite(SEGMENT_C_PIN, LOW);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, LOW);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case 0:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, HIGH);
      digitalWrite(SEGMENT_E_PIN, HIGH);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, LOW);
      break;
    case 1:
      digitalWrite(SEGMENT_A_PIN, LOW);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, LOW);
      digitalWrite(SEGMENT_G_PIN, LOW);
      break;
    case 2:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, LOW);
      digitalWrite(SEGMENT_D_PIN, HIGH);
      digitalWrite(SEGMENT_E_PIN, HIGH);
      digitalWrite(SEGMENT_F_PIN, LOW);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case 3:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, HIGH);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, LOW);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case 4:
      digitalWrite(SEGMENT_A_PIN, LOW);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case 5:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, LOW);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, HIGH);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case 6:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, LOW);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, HIGH);
      digitalWrite(SEGMENT_E_PIN, HIGH);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case 7:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, LOW);
      digitalWrite(SEGMENT_G_PIN, LOW);
      break;
    case 8:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, HIGH);
      digitalWrite(SEGMENT_E_PIN, HIGH);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case 9:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, HIGH);
      digitalWrite(SEGMENT_D_PIN, HIGH);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    default:
      digitalWrite(SEGMENT_A_PIN, LOW);
      digitalWrite(SEGMENT_B_PIN, LOW);
      digitalWrite(SEGMENT_C_PIN, LOW);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, LOW);
      digitalWrite(SEGMENT_G_PIN, LOW);
  }
  digitalWrite(SEGMENT_DP_PIN, hasDecimalPoint ? HIGH : LOW);
}

int readData() {
  const long now = millis();
  if (now - lastReadingMillis > READ_DELAY_IN_MILLIS) {
    lastReadingMillis = now;
    DHT22_ERROR_t errorCode = sensorDHT22.readData();
    temperature = sensorDHT22.getTemperatureCInt();
    humidity = sensorDHT22.getHumidityInt();
    return -errorCode;
  }

// Temperature values' samples and result output:
//   1=0.1, -1=-0.1, 12=1.2, -12=-1.2, 123=12.3, -123=-12, 1234=123, -1234=err, 12345=err, -12345=err
// Himidity values' samples and result output:
//   -1=0.0, 0=0.0, 1=0.1, 12=1.2, 123=12.3, 1000=100, 1234=100

//  temperature = 0;
//  humidity = 0;
  
  return 0;
}

void setErrorCode(int errorCode) {
  digits[0] = E_SYMBOL;
  digits[1] = R_SYMBOL;
  digits[2] = R_SYMBOL;
  digits[3] = -errorCode % 10;
}  

void setTemperature() {
  const boolean isNegative = temperature < 0 ? true : false;
  const int absTemperature = isNegative ? -temperature : temperature;

  String textTemperature = String(absTemperature);
  int textLength = textTemperature.length();
  if (textLength == 0) {
    textTemperature = "00";
    textLength = 2;
  }
  else if (textLength == 1) {
    textTemperature = "0" + textTemperature;
    textLength = 2;
  }

  boolean hasDecimalPoint = true;
  if ((isNegative && (textLength > 2)) || (!isNegative && (textLength > 3))) {
    textTemperature.remove(textLength);
    hasDecimalPoint = false;
    textLength--;
  }
  
  if (isNegative) {
    if (textLength == 2) {
      digits[0] = MINUS_SYMBOL;
      digits[1] = String(textTemperature.charAt(textLength - 2)).toInt();
      digits[2] = String(textTemperature.charAt(textLength - 1)).toInt();
      digits[3] = DEGREE_SYMBOL;
    } else {
      digits[0] = E_SYMBOL;
      digits[1] = R_SYMBOL;
      digits[2] = R_SYMBOL;
      digits[3] = DEGREE_SYMBOL;
    }
  } else { // positive
    if (textLength > 3) {
      digits[0] = E_SYMBOL;
      digits[1] = R_SYMBOL;
      digits[2] = R_SYMBOL;
      digits[3] = DEGREE_SYMBOL;
    } else {
      if (textLength == 2) digits[0] = NOTHING_SYMBOL;
      else digits[0] = String(textTemperature.charAt(textLength - 3)).toInt();
      digits[1] = String(textTemperature.charAt(textLength - 2)).toInt();
      digits[2] = String(textTemperature.charAt(textLength - 1)).toInt();
      digits[3] = DEGREE_SYMBOL;
    }
  }
  
  decimalPoints[0] = false;
  decimalPoints[1] = hasDecimalPoint;
  decimalPoints[2] = false;
  decimalPoints[3] = false;
}

void setHumidity() {
  if (humidity < 0) humidity = 0;
  else if (humidity > 1000) humidity = 1000;

  String textHumidity = String(humidity);
  int textLength = textHumidity.length();
  if (textLength == 0) {
    textHumidity = "00";
    textLength = 2;
  }
  else if (textLength == 1) {
    textHumidity = "0" + textHumidity;
    textLength = 2;
  }

  boolean hasDecimalPoint;
  if (humidity == 1000) {
    digits[0] = 1;
    digits[1] = 0;
    digits[2] = 0;
    digits[3] = HUMIDITY_SYMBOL;
    hasDecimalPoint = false;
  } else {
    if (textLength == 2) digits[0] = NOTHING_SYMBOL;
    else digits[0] = String(textHumidity.charAt(textLength - 3)).toInt();
    digits[1] = String(textHumidity.charAt(textLength - 2)).toInt();
    digits[2] = String(textHumidity.charAt(textLength - 1)).toInt();
    digits[3] = HUMIDITY_SYMBOL;
    hasDecimalPoint = true;
  }
  
  decimalPoints[0] = false;
  decimalPoints[1] = hasDecimalPoint;
  decimalPoints[2] = false;
  decimalPoints[3] = false;
}

void setup() {
  pinMode(DIGIT_1_PIN, OUTPUT);
  pinMode(DIGIT_2_PIN, OUTPUT);
  pinMode(DIGIT_3_PIN, OUTPUT);
  pinMode(DIGIT_4_PIN, OUTPUT);

  pinMode(SEGMENT_A_PIN, OUTPUT);
  pinMode(SEGMENT_B_PIN, OUTPUT);
  pinMode(SEGMENT_C_PIN, OUTPUT);
  pinMode(SEGMENT_D_PIN, OUTPUT);
  pinMode(SEGMENT_E_PIN, OUTPUT);
  pinMode(SEGMENT_F_PIN, OUTPUT);
  pinMode(SEGMENT_G_PIN, OUTPUT);
  pinMode(SEGMENT_DP_PIN, OUTPUT);
  
  analogWrite(DIGIT_1_PIN, DIGIT_OFF);
  analogWrite(DIGIT_2_PIN, DIGIT_OFF);
  analogWrite(DIGIT_3_PIN, DIGIT_OFF);
  analogWrite(DIGIT_4_PIN, DIGIT_OFF);
  digitalWrite(SEGMENT_A_PIN, HIGH);
  digitalWrite(SEGMENT_B_PIN, HIGH);
  digitalWrite(SEGMENT_C_PIN, HIGH);
  digitalWrite(SEGMENT_D_PIN, HIGH);
  digitalWrite(SEGMENT_E_PIN, HIGH);
  digitalWrite(SEGMENT_F_PIN, HIGH);
  digitalWrite(SEGMENT_G_PIN, HIGH);
  digitalWrite(SEGMENT_DP_PIN, HIGH);
  
  startModeMillis = millis();
  lastReadingMillis = startModeMillis;
  mode = TEMPERATURE;
}

void loop() {
  // Read data from sensor
  int errorCode = readData();
  if (errorCode < 0) {
    // Fill digits array
    setErrorCode(errorCode);
  } else {
    // Check mode duration and change the mode if it's time to
    const long now = millis();
    if (now - startModeMillis > MODE_DURATION_IN_MILLIS) {
      startModeMillis = now;
      if (mode == TEMPERATURE) mode = HUMIDITY;
      else mode = TEMPERATURE;
    }
    
    // Fill digits array
    if (mode == TEMPERATURE) setTemperature();
    else setHumidity();
  }
  
  // Draw one current digit on display
  activateDigit(INACTIVE);
  drawDigit(digits[currentDigitIndex], decimalPoints[currentDigitIndex]);
  activateDigit(currentDigitIndex);
  
  // Change current digit
  currentDigitIndex++;
  if (currentDigitIndex >= 4) currentDigitIndex = 0;
  
  delayMicroseconds(DIGIT_DELAY_IN_MICROSECONDS);
}
