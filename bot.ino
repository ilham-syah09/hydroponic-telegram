#include "CTBot.h"
#include <Stepper.h>
#define relay D4
CTBot myBot;
String ssid = "password";
String pass = "12345678";
String token = "1861406766:AAF9ldwPDgZTXTxmdHzr-XuvyuVdilG5YHw";
const int id = 665475263;

const int stepsPerRevolution = 360;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 14, 12, 13, 15);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }
  myStepper.setSpeed(50);
  pinMode(relay, OUTPUT);
}

void loop() {
  TBMessage msg;
  if (myBot.getNewMessage(msg))
  {
    if (msg.text.equalsIgnoreCase("on"))
    {
      Serial.println("Relay menyala");
      digitalWrite(relay, HIGH);
      delay(2000);
      Serial.println("clockwise");
      myStepper.step(stepsPerRevolution);
      delay(1000);
      Serial.println("clockwise");
      myStepper.step(stepsPerRevolution);
      delay(1000);
      Serial.println("clockwise");
      myStepper.step(stepsPerRevolution);
      delay(1000);
      Serial.println("clockwise");
      myStepper.step(stepsPerRevolution);
      delay(1000);
      Serial.println("counterclockwise");
      myStepper.step(-stepsPerRevolution);
      delay(1000);
      Serial.println("counterclockwise");
      myStepper.step(-stepsPerRevolution);
      delay(1000);
      Serial.println("counterclockwise");
      myStepper.step(-stepsPerRevolution);
      delay(1000);
      Serial.println("counterclockwise");
      myStepper.step(-stepsPerRevolution);
      delay(1000);
      myBot.sendMessage(msg.sender.id, "SEDANG MENYIRAM");
    }
    else if (msg.text.equalsIgnoreCase("off"))
    {
      digitalWrite(relay, LOW);
      myBot.sendMessage(msg.sender.id, "TIDAK MENYIRAM");
    }
    else 
    {
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". ON/OFF UNTUK KONTROL LAMPU DAN SUHU UNTUK MONITOR SUHU.";
      myBot.sendMessage(msg.sender.id, reply);             // and send it
    }
  }
  delay(1000);
}
