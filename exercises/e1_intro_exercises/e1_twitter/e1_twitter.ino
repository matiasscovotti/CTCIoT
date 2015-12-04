

//Libraries for the Yúns connection
#include <Bridge.h>// communication between the ATmega32U4(the arduino) and the AR9331 (Linux side)
#include <HttpClient.h> //Creates a HTTP client on Linux.

HttpClient client; // the HTTP client

int buttonPin = 2;    // the number of the button pin

int buttonState = 0;   // variable for reading the button status
int buttonSwitch = 0; // variable for Switching the button on and off
int buttonPushed = 0; // variable for checking if the button been pushed or not

// this is the message to Twitter, change it to whatever you want
String twitterMessage = "Hello Twitter World, from Team X!";

//counter for the number of tweets that have been sent
int numberofTweets = 0;

unsigned long int callurlTimer = 0; //  url timer
unsigned long int callurlDelay = 10000; // url delay. 1000=1 sec

void setup() {
  // configure the 13 pin as a OUTPUT
  pinMode(13, OUTPUT);


  // Blink once with the led on pin 13 when the connection is ready
  digitalWrite(13, LOW);
  Bridge.begin(); //starts the Bridge
  digitalWrite(13, HIGH);



  // initialize the button pin as an input:
  pinMode(buttonPin, INPUT);

  // configure the serial
  Serial.begin(9600);

  while (!Serial);// waits for the serial monitor to open
}

void loop() {

  // read the state of the button value:
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && buttonSwitch == LOW) { //button is pushed
    buttonPushed = 1;
  }

  // to slow down the amount of calls to the url
  if (callurlTimer + callurlDelay < millis()) {

    if (buttonPushed == 1) {
      //Setup for the content of the URL/web address
      String twitterAddress = "http://verkstad.cc/iot/mmx/code/twitter/code/sendTweet.php?pass=Schl400ch3R.&message=";
      String url = "";

      //add the number of the tweet
      twitterMessage += ",Tweet ";
      numberofTweets++; //add one to the tweet counter
      twitterMessage += numberofTweets;

      twitterMessage = urlEncode(twitterMessage); // This sets the message to put in the url'

      url = twitterAddress + twitterMessage;  // join the address and the message
      client.get(url); // sends the url to the client

      Serial.println("Tweet sent");
      buttonPushed = 0; // reset the buttonPushed'
    }
    callurlTimer = millis();// sets callurlTimer to be millis()/the time the arduino been on
  }

  buttonSwitch = buttonState; // sets the buttonstate to the buttonswitch

  delay(250); // small delay
}

//small function to change the text to url format
String urlEncode(String s) {
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == ' ') s[i] = '+';
  }
  return s;
}

