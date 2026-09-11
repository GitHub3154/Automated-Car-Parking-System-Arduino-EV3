// =====================================================
// 3 Ultrasonic Sensors + 1 Buzzer + RGB Warning LEDs
// Same buzzer frequency, faster beeping when closer
// =====================================================

// ---------- Ultrasonic Sensor 1 ----------
const int trig1 = 9;
const int echo1 = 10;

// ---------- Ultrasonic Sensor 2 ----------
const int trig2 = 5;
const int echo2 = 6;

// ---------- Ultrasonic Sensor 3 ----------
const int trig3 = 2;
const int echo3 = 3;

// ---------- Buzzer ----------
const int buzzerPin = 13;

// ---------- LEDs ----------
const int redLED = A5;
const int yellowLED = A4;
const int greenLED = A3;

// Same frequency for every distance
const int buzzerFrequency = 2000;

// -----------------------------------------------------
// Read distance from an ultrasonic sensor
// -----------------------------------------------------
long readDistance(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // 30 ms timeout prevents the program getting stuck
  long duration = pulseIn(echoPin, HIGH, 30000);

  // No echo received
  if (duration == 0) {
    return 999;
  }

  long distance = duration * 0.034 / 2;

  return distance;
}

// -----------------------------------------------------
// Setup
// -----------------------------------------------------
void setup() {

  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  Serial.begin(9600);
}

// -----------------------------------------------------
// Main loop
// -----------------------------------------------------
void loop() {

  // Read all 3 sensors
  long distance1 = readDistance(trig1, echo1);
  delay(10);

  long distance2 = readDistance(trig2, echo2);
  delay(10);

  long distance3 = readDistance(trig3, echo3);

  // Find the CLOSEST object
  long closestDistance = min(distance1, min(distance2, distance3));

  // Print distances
  Serial.print("Sensor 1: ");
  Serial.print(distance1);
  Serial.print(" cm   ");

  Serial.print("Sensor 2: ");
  Serial.print(distance2);
  Serial.print(" cm   ");

  Serial.print("Sensor 3: ");
  Serial.print(distance3);
  Serial.print(" cm   ");

  Serial.print("Closest: ");
  Serial.print(closestDistance);
  Serial.println(" cm");


  // Turn all LEDs off first
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);


  // ===================================================
  // RED - VERY CLOSE
  // 0 to 20 cm
  // ===================================================

  if (closestDistance <= 20) {

    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    // Same 2000 Hz frequency
    // Very fast beeping
    tone(buzzerPin, buzzerFrequency);

    delay(150);

    noTone(buzzerPin);

    delay(50);
  }


  // ===================================================
  // YELLOW - MEDIUM DISTANCE
  // 21 to 50 cm
  // ===================================================

  else if (closestDistance <= 50) {

    digitalWrite(yellowLED, HIGH);

    // Same frequency
    // Faster beeping than green
    tone(buzzerPin, buzzerFrequency);

    delay(150);

    noTone(buzzerPin);

    delay(200);
  }


  // ===================================================
  // GREEN - FAR
  // 51 to 100 cm
  // ===================================================

  else if (closestDistance <= 100) {

    digitalWrite(greenLED, HIGH);

    // Same frequency
    // Slow beeping
    tone(buzzerPin, buzzerFrequency);

    delay(100);

    noTone(buzzerPin);

    delay(600);
  }


  // ===================================================
  // MORE THAN 100 cm
  // No warning
  // ===================================================

  else {

    noTone(buzzerPin);

    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);

    delay(100);
  }
}