int green_pin = 2;
int yellow_pin = 3;
int red_pin = 4;

int sensor_pin = A0;

int low_threshold_voltage = 4.0;
int medium_threshold_voltage = 6.0;

int interval_off_ms = 500;
int interval_on_ms = 200;

int measurements = 10;

int voltage_division_factor = 11;
float input_normalization_factor = 204.6;

void setup() {
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  float voltage_sum = 0;

  for (int i = 0; i < measurements; i++) {
    float sensorValue = analogRead(sensor_pin);
    float volt = (sensorValue / input_normalization_factor) * voltage_division_factor;
    voltage_sum += volt;
  }

  float volt_result = voltage_sum / measurements;
  
  Serial.println(volt_result);

  if (volt_result >= medium_threshold_voltage) {
    green_on();
  } else if (volt_result < medium_threshold_voltage && volt_result >= low_threshold_voltage) {
    yellow_on();
  } else {
    red_on();
  }
  delay(interval_on_ms);
  all_off();
  delay(interval_off_ms);
}

void green_on() {
  digitalWrite(green_pin, HIGH);
  digitalWrite(yellow_pin, LOW);
  digitalWrite(red_pin, LOW);

}

void yellow_on() {
  digitalWrite(green_pin, LOW);
  digitalWrite(yellow_pin, HIGH);
  digitalWrite(red_pin, LOW);

}

void red_on() {
  digitalWrite(green_pin, LOW);
  digitalWrite(yellow_pin, LOW);
  digitalWrite(red_pin, HIGH);
}

void all_off() {
  digitalWrite(green_pin, LOW);
  digitalWrite(yellow_pin, LOW);
  digitalWrite(red_pin, LOW);
}
