//
// Automated Sliding Window Based on Ambient Air Quality
// Microcontroller : ESP32
// Sensor	: MQ Gas Sensor
// Motor Driver	: L298N
//

//	Pin Definitions

// Gas Sensor Analog Pin
const int gasSensorPin = 34; // ADC pin

// Motor Driver Pins const int IN1 = 26; const int IN2 = 27;
const int ENA = 25;	// PWM pin

//	System Parameters

int gasValue = 0;
int gasThreshold = 1800;	// Adjust based on calibration bool windowOpen = false;		// Tracks window state
//	Setup Function

void setup()
{
Serial.begin(115200);
 
pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);

pinMode(gasSensorPin, INPUT);

// Ensure motor is stopped initially digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); analogWrite(ENA, 0);
}

//	Main Loop

void loop()
{
// Read Gas Sensor Value
gasValue = analogRead(gasSensorPin);

Serial.print("Gas Sensor Value: "); Serial.println(gasValue);

//	Air Quality Check

if (gasValue < gasThreshold && !windowOpen)
{
// Air is Safe -> Open Window openWindow();
windowOpen = true; delay(3000);	// Stability Delay
}
else if (gasValue >= gasThreshold && windowOpen)
{
// Air is Polluted -> Close Window closeWindow();
windowOpen = false; delay(3000);	// Stability Delay
}

delay(1000); // Sensor reading interval
}

//	Motor Functions

void openWindow()
{
Serial.println("Opening Window...");
 
digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
analogWrite(ENA, 200); // Speed control (0–255)

delay(5000); // Motor rotation time (adjust as per window length)

stopMotor();
}

void closeWindow()
{
Serial.println("Closing Window...");

digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, 200);

delay(5000); // Motor rotation time

stopMotor();
}

void stopMotor()
{
digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); analogWrite(ENA, 0);
}
