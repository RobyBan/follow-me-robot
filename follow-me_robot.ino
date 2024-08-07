#define trigPinL 5
#define echoPinL 6
#define trigPinM 7
#define echoPinM 8
#define trigPinR 9
#define echoPinR 10

#define ENA 3
#define ENB 11
#define IN1 2
#define IN2 4
#define IN3 12
#define IN4 13

long duration;
int distanceM, distanceL, distanceR;

void setup() {
  pinMode(trigPinM, OUTPUT);
  pinMode(echoPinM, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Measure distance from the middle sensor
  distanceM = measureDistance(trigPinM, echoPinM);
  // Measure distance from the left sensor
  distanceL = measureDistance(trigPinL, echoPinL);
  // Measure distance from the right sensor
  distanceR = measureDistance(trigPinR, echoPinR);

  // Debugging prints
  Serial.print("Middle Distance: ");
  Serial.println(distanceM);
  Serial.print("Left Distance: ");
  Serial.println(distanceL);
  Serial.print("Right Distance: ");
  Serial.println(distanceR);

  // Determine robot behavior based on middle sensor
  if (distanceM <= 10) {
    driveBackward();
  } else if (distanceM <= 20) {
    stop();
  } else if (distanceM < 50) {
    driveForward();
  } else if (distanceM > 50) {
    stop();
  }

  // Additional checks for left and right sensors
  if (distanceM > 50 && distanceL < 50) {
    stopLeft();
    driveRight();
  } else if (distanceM > 50 && distanceR < 50) {
    stopRight();
    driveLeft();
  } 
  
  if (distanceL < 10) {
    stop();
  }

  if (distanceR < 10) {
    stop();
  }

  delay(100);
}

int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void driveForward() {
  analogWrite(ENA, 180);  // Set speed for left motors
  analogWrite(ENB, 180);  // Set speed for right motors
  digitalWrite(IN1, HIGH); // Set direction for left motors
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Set direction for right motors
  digitalWrite(IN4, LOW);
}

void driveSlower() {
  analogWrite(ENA, 120);  // Set speed for left motors
  analogWrite(ENB, 120);  // Set speed for right motors
  digitalWrite(IN1, HIGH); // Set direction for left motors
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Set direction for right motors
  digitalWrite(IN4, LOW);
}

void driveBackward() {
  analogWrite(ENA, 180);  // Set speed for left motors
  analogWrite(ENB, 180);  // Set speed for right motors
  digitalWrite(IN1, LOW);  // Set direction for left motors
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  // Set direction for right motors
  digitalWrite(IN4, HIGH);
}

void stop() {
  analogWrite(ENA, 0);  // Stop left motors
  analogWrite(ENB, 0);  // Stop right motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopLeft() {
  analogWrite(ENA, 0);  // Stop motor A
}

void stopRight() {
  analogWrite(ENB, 0);  // Stop motor A
}

void driveLeft() {
  analogWrite(ENA, 0);  // Set speed for left motors
  analogWrite(ENB, 255);  // Set speed for right motors
  digitalWrite(IN1, HIGH); // Set direction for left motors
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); // Set direction for right motors
  digitalWrite(IN4, LOW);
}

void driveLeftBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255);  // Control speed
}

void driveRight() {
  analogWrite(ENA, 255);  // Set speed for left motors
  analogWrite(ENB, 0);  // Set speed for right motors
  digitalWrite(IN1, LOW); // Set direction for left motors
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Set direction for right motors
  digitalWrite(IN4, LOW);
}