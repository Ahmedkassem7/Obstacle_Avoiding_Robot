// Define constants
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENB 6
#define Speed 130
#define DISTANCE_THRESHOLD_FORWARD 25
#define DISTANCE_THRESHOLD_SIDE 25

// Ultrasonic sensor pins
const int trig_forward = 8;
const int echo_forward = 9;
const int trig_right = 10;
const int echo_right = 11;
const int trig_left = 12;
const int echo_left = 13;

// Function prototypes
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void stopCar();
int measureDistance(int trigPin, int echoPin);

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trig_forward, OUTPUT);
  pinMode(echo_forward, INPUT);
  pinMode(trig_right, OUTPUT);
  pinMode(echo_right, INPUT);
  pinMode(trig_left, OUTPUT);
  pinMode(echo_left, INPUT);
}

void loop() {
  int leftDistance = measureDistance(trig_left, echo_left);
  int middleDistance = measureDistance(trig_forward, echo_forward);
  int rightDistance = measureDistance(trig_right, echo_right);

  avoidObstacle(leftDistance, middleDistance, rightDistance);

  delay(100);  // Adjust as needed
}

// Ultrasonic distance measurement function
int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float distance = pulseIn(echoPin, HIGH);
  delay(10);

  distance = distance / 29 / 2;
  return (int)distance;
}

// Function to avoid obstacles
void avoidObstacle(int leftDist, int middleDist, int rightDist) {
  stopCar();
  delay(100);
  if (middleDist <= DISTANCE_THRESHOLD_FORWARD && rightDist <= DISTANCE_THRESHOLD_SIDE && leftDist <= DISTANCE_THRESHOLD_SIDE) {
    stopCar();
    delay(150);
    moveBackward();
    delay(70);
  }
  else {
    if (middleDist <= DISTANCE_THRESHOLD_FORWARD) {
      stopCar();
      delay(100);
      moveBackward();
      delay(50);
      if (rightDist <= DISTANCE_THRESHOLD_SIDE ) {
        moveBackward();
        delay(20);
        turnLeft();
        delay(750);
      }
       else {
        turnRight();
        delay(700);
      }

    }
    else {
      stopCar();
      delay(150);
      moveForward();
      delay(100);

    }
  }
}
// Movement functions
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, Speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, Speed);
  Serial.println("ROBOT_MOVING_FORWARD");
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, Speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, Speed);
  Serial.println("ROBOT_MOVING_BACKWARD" );
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, Speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, Speed);
  Serial.println("ROBOT_MOVING_RIGHT");
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, Speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, Speed);
  Serial.println("ROBOT_MOVING_LEFT");
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  Serial.println("ROBOT_STOP");
}


