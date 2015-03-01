// -----------------
// Read temperature
// -----------------

// Create a variable that will store the temperature value

double temperature = 0.0;

void setup()
{
  // Register a Spark variable here
  Spark.variable("temperature", & temperature, DOUBLE);

  // Connect the temperature sensor to A7 and configure it
  // to be an input
  pinMode(A7, INPUT);
}

void loop()
{
  int reading = 0;
  double voltage = 0.0;

  // Keep reading the sensor value so when we make an API
  // call to read its value, we have the latest one
  reading = analogRead(A7);

  // The returned value from the Core is going to be in the range from 0 to 4095
  // Calculate the voltage from the sensor reading
  voltage = (reading * 3.3) / 4095;

  // Calculate the temperature and update our static variable
  temperature = (voltage - 0.5) * 100;
  
  // Google API needs it in a string, so make it a string
  String temp = String(temperature);
  
  // This is the bit that pushes it to Spark, which sends it to IFTTT, which sends it to Google Spreadsheets. No lie. This is it.
  Spark.publish("temperature", temp);
  
  delay(600000);

}