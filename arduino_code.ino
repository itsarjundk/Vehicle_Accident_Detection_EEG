#include <SoftwareSerial.h>
#include <TinyGPS.h>

int state = 0;
#define vibrate_sense 9
float gpslat, gpslon;

TinyGPS gps;
SoftwareSerial sgps(4, 5);
SoftwareSerial sgsm(2, 3);

void setup()
{
  sgsm.begin(9600);
  sgps.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  while (sgps.available())
  {
    int c = sgps.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&gpslat, &gpslon);
    }
  }
      if (digitalRead(vibrate_sense)==HIGH && state == 0) {
      sgsm.print("\r");
      delay(1000);
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      /*Replace XXXXXXXXXX to 10 digit mobile number &
        ZZ to 2 digit country code*/
      sgsm.print("AT+CMGS=\"+917736626642\"\r");
      delay(1000);
      //The text of the message to be sent.
      sgsm.print("ACCIDENT");
      Serial.println("ACCIDENT");
      sgsm.print("Latitude :");
      Serial.println("Latitude :");
      sgsm.println(gpslat, 6);
      Serial.println(gpslat, 6);
      sgsm.print("Longitude:");
      sgsm.println(gpslon, 6);
      Serial.print("Longitude:");
      Serial.println(gpslon, 6);
      sgsm.print("HELP");
      Serial.println("HELP");
      delay(1000);
      sgsm.write(0x1A);
      delay(1000);
      state = 1;
    }
    if (digitalRead(vibrate_sense) == LOW) {
      state = 0;
    }
  }
