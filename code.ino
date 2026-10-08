const int RF1 = 2;  // Button 1 -> LEFT
const int RF2 = 3;  // Button 2 -> FORWARD
const int RF3 = 4;  // Button 3 -> RIGHT

const int MTR1_IN1 = 10;
const int MTR1_IN2 = 11;

const int MTR2_IN1 = 6;
const int MTR2_IN2 = 9;

void setup() {

  Serial.begin(9600);

  pinMode(RF1, INPUT);
  pinMode(RF2, INPUT);
  pinMode(RF3, INPUT);

  pinMode(MTR1_IN1, OUTPUT);
  pinMode(MTR1_IN2, OUTPUT);

  pinMode(MTR2_IN1, OUTPUT);
  pinMode(MTR2_IN2, OUTPUT);

  stopRobot();
}


void loop() {

  rf1 = digitalRead(RF1);
  rf2 = digitalRead(RF2);
  rf3 = digitalRead(RF3);

  if (rf1 == 1 && rf2 == 1 && rf3 == 1) {
    stopRobot();
  } else if (rf1 == 0 && rf2 == 0 && rf3 == 0) {
    stopRobot();
  } else if (rf1 == 1 && rf2 == 0 && rf3 == 0) {
    turnLeft();
  } else if (rf1 == 0 && rf2 == 1 && rf3 == 0) {
    moveForward();
  } else if (rf1 == 0 && rf2 == 0 && rf3 == 1) {
    turnRight();
  }
}

void moveForward() {

  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, HIGH);

  digitalWrite(MTR2_IN1, LOW);
  digitalWrite(MTR2_IN2, HIGH);
}


void turnLeft() {

  digitalWrite(MTR1_IN1, HIGH);
  digitalWrite(MTR1_IN2, LOW);

  digitalWrite(MTR2_IN1, LOW);
  digitalWrite(MTR2_IN2, HIGH);
}


void turnRight() {

  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, HIGH);

  digitalWrite(MTR2_IN1, HIGH);
  digitalWrite(MTR2_IN2, LOW);
}


void stopRobot() {

  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, LOW);

  digitalWrite(MTR2_IN1, LOW);
  digitalWrite(MTR2_IN2, LOW);
}
