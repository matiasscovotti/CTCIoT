

// treshhold for the sensor to know its in oil or not
int oilTreshhold = 0;

int oilControl0 = 0 ; // for skipping errors from sensor0
int oilControl1 = 0 ; // for skipping errors from sensor1
int oilControl2 = 0 ; // for skipping errors from sensor2
int oilControl3 = 0 ; // for skipping errors from sensor3

int oilControlltreshhold = 5; // number of times that the sensor will skip a higher then 0 value, in case of errors

unsigned long int callurlTimer = 0; //  url timer
unsigned long int callurlDelay = 5000; // url delay. 1000=1 sec



void setup() {


  // configure the serial
  Serial.begin(9600);

  while (!Serial); // waits for the serial monitor to open
}

void loop() {

  // Take in the value from the sensor
  int sensor0 = analogRead(0);// from analog sensor 0
  int sensor1 = analogRead(1);// from analog sensor 1
  int sensor2 = analogRead(2);// from analog sensor 2
  int sensor3  = analogRead(3);// from analog sensor 3

  // variables for the detection of oil
  int oilDetected0 = 0;
  int oilDetected1 = 0;
  int oilDetected2 = 0;
  int oilDetected3 = 0;


  //----------------------------------
  //Sensor 0
  //----------------------------------

  // code for checking errors form the oil sensor

  if (sensor0  == oilTreshhold) {
    // add to the oilControl if the sensor at the treshhold
    oilControl0++;
  } else {
    // subtract from the oilControl if the sensor at anything else
    oilControl0 = oilControl0 - 1;
    if (oilControl0 < 0)
    {
      //keeps the value from going under 0
      oilControl0 = 0;
    }
  }
  // if the sensor value is the same as the treshhold, then oil is detected
  if (sensor0 == oilTreshhold &&  oilControl0 >= oilControlltreshhold) {
    oilDetected0 = 1; //oil is dectected
    oilControl0 = 0; //reset the oil control
  }

  //----------------------------------
  //Sensor 1
  //----------------------------------
  // code for checking errors form the oil sensor
  if (sensor1  == oilTreshhold) {
    // add to the oilControl if the sensor at the treshhold
    oilControl1++;
  } else {
    // subtract from the oilControl if the sensor at anything else
    oilControl1 = oilControl1 - 1;
    if (oilControl1 < 0)
    {
      //keeps the value from going under 0
      oilControl1 = 0;
    }
  }
  // if the sensor value is the same as the treshhold, then oil is detected
  if (sensor1 == oilTreshhold &&  oilControl1 >= oilControlltreshhold) {
    oilDetected1 = 1; //oil is dectected
    oilControl1 = 0; //reset the oil control
  }

  //----------------------------------
  //Sensor 2
  //----------------------------------
  // code for checking errors form the oil sensor
  if (sensor2  == oilTreshhold) {
    // add to the oilControl if the sensor at the treshhold
    oilControl2++;
  } else {
    // subtract from the oilControl if the sensor at anything else
    oilControl2 = oilControl2 - 1;
    if (oilControl2 < 0)
    {
      //keeps the value from going under 0
      oilControl2 = 0;
    }
  }
  // if the sensor value is the same as the treshhold, then oil is detected
  if (sensor2 == oilTreshhold &&  oilControl2 >= oilControlltreshhold) {
    oilDetected2 = 1; //oil is dectected
    oilControl2 = 0; //reset the oil control
  }

  //----------------------------------
  //Sensor 3
  //----------------------------------
  // code for checking errors form the oil sensor
  if (sensor3  == oilTreshhold) {
    // add to the oilControl if the sensor at the treshhold
    oilControl3++;
  } else {
    // subtract from the oilControl if the sensor at anything else
    oilControl3 = oilControl3 - 1;
    if (oilControl3 < 0)
    {
      //keeps the value from going under 0
      oilControl3 = 0;
    }
  }
  // if the sensor value is the same as the treshhold, then oil is detected
  if (sensor3 == oilTreshhold &&  oilControl3 >= oilControlltreshhold) {
    oilDetected3 = 1; //oil is dectected
    oilControl3 = 0; //reset the oil control
  }



  // to slow down the amount of calls to the url
  if (callurlTimer + callurlDelay < millis()) {
    //string for all the sensors statuses
    String oilStatus = "";

    //change the massage depending on the sensors
    // check all the sensors for oil
    if (oilDetected0 == 1 || oilDetected1 == 1 || oilDetected2 == 1 || oilDetected3 == 1 ) {
      oilStatus = "Oil detected" ;
    }
    else {
      oilStatus = "No oil detected ";
    }

    // add together the sensors that have detected oil
    String oilDetected = "";
    if (oilDetected0 == 1)oilDetected += "on sensor0 ";
    if (oilDetected1 == 1)oilDetected += "on sensor1 ";
    if (oilDetected2 == 1)oilDetected += "on sensor2 ";
    if (oilDetected3 == 1)oilDetected += "on sensor3 ";

    // get the status of all the sensors
    oilStatus += oilDetected;


    //add up all of the sensor value, the higher value the better
    int oilSensor = sensor0 + sensor1 + sensor2 + sensor3;
    // prints the current oilStatus in the serial montitor
    Serial.print(oilStatus);
    Serial.print(" Total value form all of the sensors: ");
    Serial.println(oilSensor);


    callurlTimer = millis(); // sets callurlTimer to be millis()/the time the arduino been on

    // resets the oildetected
    oilDetected0 = 0;
    oilDetected1 = 0;
    oilDetected2 = 0;
    oilDetected3 = 0;

  }



  delay(100);
}



