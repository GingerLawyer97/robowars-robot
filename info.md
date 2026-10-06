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

