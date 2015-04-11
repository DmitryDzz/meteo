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
  
  digitalWrite(DIGIT_1_PIN, HIGH);
  digitalWrite(DIGIT_2_PIN, HIGH);
  digitalWrite(DIGIT_3_PIN, HIGH);
  digitalWrite(DIGIT_4_PIN, LOW);
  digitalWrite(SEGMENT_A_PIN, HIGH);
  digitalWrite(SEGMENT_B_PIN, HIGH);
  digitalWrite(SEGMENT_C_PIN, HIGH);
  digitalWrite(SEGMENT_D_PIN, HIGH);
  digitalWrite(SEGMENT_E_PIN, HIGH);
  digitalWrite(SEGMENT_F_PIN, HIGH);
  digitalWrite(SEGMENT_G_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
