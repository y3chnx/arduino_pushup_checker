// Smart Push-Up Counter 

const int trigPin = 9;
const int echoPin = 10;
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int buzzerPin = 8;

long duration;
float distanceCm;
bool pushUpCounted = false; 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  

  setColor(255, 255, 255); 
  
  Serial.println("Push-Up Counter Started");
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  duration = pulseIn(echoPin, HIGH);

  // Convert time to distance in cm
  distanceCm = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // --- Push-Up Logic ---
  
  if (distanceCm > 0 && distanceCm < 10) {
    // Target reached (< 10cm): Turn RGB Green
    setColor(255, 0, 255); // (Red OFF, Green ON, Blue OFF)
    
    // Play confirmation chime once
    if (!pushUpCounted) {
      tone(buzzerPin, 1000); 
      delay(80);
      tone(buzzerPin, 1500); 
      delay(120);
      noTone(buzzerPin);
      
      pushUpCounted = true; 
    }
  } 
  else {
    // Not in zone (>= 10cm): Turn RGB OFF completely
    setColor(255, 255, 255);     
    noTone(buzzerPin);     
    
    // Reset when moving back up
    if (distanceCm >= 12) {
      pushUpCounted = false;
    }
  }

  delay(50); 
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
