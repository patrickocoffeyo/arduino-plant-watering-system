/**
 * Configuration values.
 */
// This is the numerical value that indicates that the
// pump should not be activated.
const int moistureLevelCap = 20;

// This is a pointer to digital pin #2, this will 
// control the relay that turns the pump on, or off.
const int pumpRelayPin = 2;

// This is a pointer to analog pin #0, this will
// accept the signal from the moisture sensor.
const int moistureSensorPin = A0;

// Named variables that make reading time-related code easy.
const int second = 1000;
const int halfSecond = second / 2;

/**
 * Singletons.
 */
// Stores the value of the moisture sensor when it was
// most recently measured/read.
int moistureLevel = 0;

/**
 * Helper function that turns on the pump.
 */
void turnOnPump() {
  Serial.println("Turning on the pump.");
  digitalWrite(pumpRelayPin, HIGH);
}

/**
 * Helper function that turns on the pump.
 */
void turnOffPump() {
  Serial.println("Turning off the pump.");
  digitalWrite(pumpRelayPin, LOW);
}

/**
 * Helper function writes the moisture level to
 * the serial monitor.
 */
void logMoistureLevel() {
  Serial.print("Moisture level: ");
  Serial.println(moistureLevel);
}

/**
 * Initialization function that sets up the board's
 * pins and initializes the program.
 */
void setup() {
  // This sets up the baud of the board so it can communicate
  // with the serial monitor in the Arduino IDE (code editor).
  Serial.begin(9600);

  // Set the mode of the pump relay pin such that it
  // is an output.
  pinMode(pumpRelayPin, OUTPUT);

  // Turn on the pump for half a second so the relay/board
  // communication is stabilized.
  turnOnPump();
  delay(halfSecond);
}

/**
 * Function that runs repeatedly. The delay at the end
 * of this function adds a delay between each invocation.
 */
void loop() {
  // Read the moisture level from the moisture sensor, and update
  // the moistureLevel singleton. Then, call the log function that
  // outputs the moisture level to the serial monitor.
  moistureLevel = analogRead(moistureSensorPin);
  logMoistureLevel();
  
  // If the moisture level is too high, turn off the pump.
  if (moistureLevel > moistureLevelCap) {
    turnOffPump();
  }
  // If the moisture level is below the cap, turn on the pump.
  else {
    turnOnPump();
  }

  // Wait one second before allowing this loop function to run again.
  delay(second);
}
