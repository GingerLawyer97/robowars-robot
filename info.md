### Code to check for the Motor pins:

MTR1 Channel -> Pins D10 and D11

MTR2 Channel -> Pins D6 and D9

```C++
void setup() {
  // Initialize Serial Communication
  Serial.begin(9600);
  Serial.println("--- Starting Motor Test ---");

  // Configure motor driver pins as outputs
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {

  // Pins D10 & D11
  Serial.println("Pins D10 (HIGH) and D11 (LOW)... [MTR1 Channel]...");
  digitalWrite(10, HIGH); digitalWrite(11, LOW);
  delay(2000); 
  stopAll(); 
  delay(1000);

  // Pins D6 & D9
  Serial.println("Pins D6 (HIGH) and D9 (LOW) [MTR2 Channel]...");
  digitalWrite(6, HIGH); digitalWrite(9, LOW);
  delay(2000); 
  stopAll(); 
  delay(1000);

  Serial.println("--- Cycle Complete. Restarting... ---");
  delay(1000);
}

void stopAll() {
  digitalWrite(3, LOW);  digitalWrite(5, LOW);
  digitalWrite(6, LOW);  digitalWrite(9, LOW);
  digitalWrite(10, LOW); digitalWrite(11, LOW);
}
```

Bring TV remote.

Check Hex Codes for infrared transmission.

Check which pin is connected to the IR sensors.

### Code to check Hex code:

```C++
#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 2; // Signal wire connected to D2

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Sensor connected via jumpers! Press remote buttons...");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Pressed Hex Code: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
  }
}
```

### Movement Testing:

```C++
// STEMROBO Dual Motor Control with IR Remote
// Pin Assignments:
// MTR1 (Left Motor): D10, D11
// MTR2 (Right Motor): D6, D9

const int MTR1_IN1 = 10;
const int MTR1_IN2 = 11;
const int MTR2_IN1 = 6;
const int MTR2_IN2 = 9;

void setup() {
  pinMode(MTR1_IN1, OUTPUT);
  pinMode(MTR1_IN2, OUTPUT);
  pinMode(MTR2_IN1, OUTPUT);
  pinMode(MTR2_IN2, OUTPUT);
  
  stopRobot(); // Keep motors stopped at startup
}

void loop() {
  // Movement testing sequence without IR sensor:
  moveForward();
  delay(2000);

  turnLeft();
  delay(1000);

  turnRight();
  delay(1000);

  moveBackward();
  delay(2000);

  stopRobot();
  delay(3000);
}

// --- ROBOT MOVEMENT FUNCTIONS ---

void moveForward() {
  digitalWrite(MTR1_IN1, HIGH);
  digitalWrite(MTR1_IN2, LOW);
  digitalWrite(MTR2_IN1, HIGH);
  digitalWrite(MTR2_IN2, LOW);
}

void moveBackward() {
  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, HIGH);
  digitalWrite(MTR2_IN1, LOW);
  digitalWrite(MTR2_IN2, HIGH);
}

void turnLeft() {
  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, HIGH); // Left motor spins backward
  digitalWrite(MTR2_IN1, HIGH); // Right motor spins forward
  digitalWrite(MTR2_IN2, LOW);
}

void turnRight() {
  digitalWrite(MTR1_IN1, HIGH); // Left motor spins forward
  digitalWrite(MTR1_IN2, LOW);
  digitalWrite(MTR2_IN1, LOW);
  digitalWrite(MTR2_IN2, HIGH); // Right motor spins backward
}

void stopRobot() {
  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, LOW);
  digitalWrite(MTR2_IN1, LOW);
  digitalWrite(MTR2_IN2, LOW);
}
```

### Movement with IR Remote Code (basically final code):

```C++
#include <IRremote.hpp>

// --- PIN DEFINITIONS ---
const int IR_RECEIVE_PIN = 2; // Connected to IR1/IR2 signal header (D2)

// Motor 1 (Left Motor)
const int MTR1_IN1 = 10;      
const int MTR1_IN2 = 11;

// Motor 2 (Right Motor)
const int MTR2_IN1 = 6;       
const int MTR2_IN2 = 9;

// --- IR REMOTE BUTTON HEX CODES (PLACEHOLDERS) ---
// Replace these 0x00000000 values with your scanned values from Serial Monitor
const uint32_t IR_CODE_FORWARD  = 0x12345678; 
const uint32_t IR_CODE_BACKWARD = 0x87654321; 
const uint32_t IR_CODE_LEFT     = 0xA1B2C3D4; 
const uint32_t IR_CODE_RIGHT    = 0xD4C3B2A1; 
const uint32_t IR_CODE_STOP     = 0x00FF00FF; 

void setup() {
  Serial.begin(9600);

  // Initialize motor pins as outputs
  pinMode(MTR1_IN1, OUTPUT);
  pinMode(MTR1_IN2, OUTPUT);
  pinMode(MTR2_IN1, OUTPUT);
  pinMode(MTR2_IN2, OUTPUT);

  // Ensure motors start off
  stopRobot();

  // Start the IR Receiver
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Robot Ready! Awaiting IR commands...");
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t receivedCode = IrReceiver.decodedIRData.decodedRawData;

    // Print received code to Serial Monitor for verification
    Serial.print("Received Hex Code: 0x");
    Serial.println(receivedCode, HEX);

    // Process movement commands
    if (receivedCode == IR_CODE_FORWARD) {
      moveForward();
      Serial.println("Action: Moving Forward");
    } 
    else if (receivedCode == IR_CODE_BACKWARD) {
      moveBackward();
      Serial.println("Action: Moving Backward");
    } 
    else if (receivedCode == IR_CODE_LEFT) {
      turnLeft();
      Serial.println("Action: Turning Left");
    } 
    else if (receivedCode == IR_CODE_RIGHT) {
      turnRight();
      Serial.println("Action: Turning Right");
    } 
    else if (receivedCode == IR_CODE_STOP) {
      stopRobot();
      Serial.println("Action: Stopped");
    }

    IrReceiver.resume(); // Ready to receive the next signal
  }
}

// --- MOVEMENT FUNCTIONS ---

void moveForward() {
  digitalWrite(MTR1_IN1, HIGH);
  digitalWrite(MTR1_IN2, LOW);
  digitalWrite(MTR2_IN1, HIGH);
  digitalWrite(MTR2_IN2, LOW);
}

void moveBackward() {
  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, HIGH);
  digitalWrite(MTR2_IN1, LOW);
  digitalWrite(MTR2_IN2, HIGH);
}

void turnLeft() {
  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, HIGH); // Left motor reverses
  digitalWrite(MTR2_IN1, HIGH); // Right motor moves forward
  digitalWrite(MTR2_IN2, LOW);
}

void turnRight() {
  digitalWrite(MTR1_IN1, HIGH); // Left motor moves forward
  digitalWrite(MTR1_IN2, LOW);
  digitalWrite(MTR2_IN1, LOW);  // Right motor reverses
  digitalWrite(MTR2_IN2, HIGH);
}

void stopRobot() {
  digitalWrite(MTR1_IN1, LOW);
  digitalWrite(MTR1_IN2, LOW);
  digitalWrite(MTR2_IN1, LOW);
  digitalWrite(MTR2_IN2, LOW);
}
```

All ts is jst for the movement still need the weapon systems.
