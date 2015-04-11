const int DIGIT_DELAY = 500;

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

const byte DIGIT_OFF = 255;
const byte DIGIT_ON = 100; // increase the value to reduce current

const short MINUS = -1;
const short DEGREE = -2;

int currentDigitIndex = 0;
const int INACTIVE = -1;
short digits[4];

int temperature = -23;
int humidity = 46;

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

void drawDigit(short value) {
  switch (value) {
    case DEGREE:
      digitalWrite(SEGMENT_A_PIN, HIGH);
      digitalWrite(SEGMENT_B_PIN, HIGH);
      digitalWrite(SEGMENT_C_PIN, LOW);
      digitalWrite(SEGMENT_D_PIN, LOW);
      digitalWrite(SEGMENT_E_PIN, LOW);
      digitalWrite(SEGMENT_F_PIN, HIGH);
      digitalWrite(SEGMENT_G_PIN, HIGH);
      break;
    case MINUS:
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
  
  digits[0] = MINUS;
  digits[1] = 2;
  digits[2] = 3;
  digits[3] = DEGREE;
}

void loop() {
  activateDigit(INACTIVE);
  drawDigit(digits[currentDigitIndex]);
  activateDigit(currentDigitIndex);
  
  currentDigitIndex++;
  if (currentDigitIndex >= 4) currentDigitIndex = 0;
  
  delayMicroseconds(DIGIT_DELAY);
}
