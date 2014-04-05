// VoltageSensor.ino

// analog to mV conversion
// arduino outputs 5V over the analog 1024 so we have
// 5V/1024 or 0.0049V = 4.9mV/analog unit
#define MV_TO_ANALOG	4.9

// from AttoPilot docs
// http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Current/DC%20Voltage%20and%20Current%20Sense%20PCB%20with%20Analog%20Output.pdf
#define SENSOR_180_MV_TO_VOLT	63.69
#define SENSOR_90_MV_TO_VOLT	63.69	
#define SENSOR_13_MV_TO_VOLT	242.3

#define SENSOR_180_MV_TO_CURRENT	18.30
#define SENSOR_90_MV_TO_CURRENT	36.60	
#define SENSOR_13_MV_TO_CURRENT	73.20

// adjust this to whatever you are comfortable with
#define LOW_LIPO_VOLTAGE		11.0


void setup() {
	pinMode(8, OUTPUT);
	digitalWrite(8, LOW);	
	Serial.begin(9600);
	Serial.println("Beginning Voltage Sensor Reading");
}

void loop() {
	// get the analog output from the sensor
	float raw_V = analogRead(A0);

	// convert analog arduino units to mV units 
	float raw_mV = raw_V * MV_TO_ANALOG;

	// convert mV units to sensor values for voltage
	float v_sensor = raw_mV / SENSOR_180_MV_TO_VOLT;

	// get the analog output from the sensor
	float raw_I = analogRead(A1);

	// convert analog arduino units to mV units 
	float raw_i_mV = raw_I * MV_TO_ANALOG;

	// convert mV units to sensor values for current
	float i_sensor = raw_i_mV / SENSOR_180_MV_TO_CURRENT;

	// voltage is too low so sound alarm
	if(v_sensor < LOW_LIPO_VOLTAGE)
	{
		digitalWrite(8, HIGH);
	}

	Serial.print(v_sensor);
	Serial.print('\t');
	Serial.println(i_sensor);


	delay(100);
}