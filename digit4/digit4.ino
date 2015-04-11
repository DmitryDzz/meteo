const int DIGIT_DELAY_IN_MICROSECONDS = 500;
const int MODE_DURATION_IN_MILLIS = 2000; // temperature / humidity modes

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

int temperature; // real temperature * 10
int humidity;    // real humidity * 10
long startModeMillis;

enum Mode {
  TEMPERATURE, HUMIDITY
};
Mode mode;

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
  temperature = 234; // 1=0.1, -1=-0.1, 12=1.2, -12=-1.2, 123=12.3, -123=-12, 1234=123, -1234=err, 12345=err, -12345=err
  humidity = 463;
  
  return 0;
}

void setErrorCode(int errorCode) {
  digits[0] = E_SYMBOL;
  digits[1] = R_SYMBOL;
  digits[2] = R_SYMBOL;
  digits[3] = 5;
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

Serial.println(textTemperature);

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
      digits[3] = DEGREE_SYMBOL; //todo add code for temperature overflow error
    }
  } else { // positive
    if (textLength > 3) {
      digits[0] = E_SYMBOL;
      digits[1] = R_SYMBOL;
      digits[2] = R_SYMBOL;
      digits[3] = DEGREE_SYMBOL; //todo add code for temperature overflow error
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
  digits[0] = 4;
  digits[1] = 6;
  digits[2] = 3;
  digits[3] = HUMIDITY_SYMBOL;
  
  decimalPoints[0] = false;
  decimalPoints[1] = true;
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
  mode = TEMPERATURE;
  
  Serial.begin(9600);
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
  
//  delay(1000);
  
  // Draw one current digit on display
  activateDigit(INACTIVE);
  drawDigit(digits[currentDigitIndex], decimalPoints[currentDigitIndex]);
  activateDigit(currentDigitIndex);
  
  // Change current digit
  currentDigitIndex++;
  if (currentDigitIndex >= 4) currentDigitIndex = 0;
  
  delayMicroseconds(DIGIT_DELAY_IN_MICROSECONDS);
}
