#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const int touchSensorPin = 14; // Pin for touch sensor
bool taskDone = false; // Tracks if the task is marked done

void setup() {
  Serial.begin(9600);
  pinMode(0, OUTPUT); //Left-Upper
  pinMode(16, OUTPUT); //Left-Lower

  pinMode(13, OUTPUT); //Right-Upper
  pinMode(12, OUTPUT); //Right-lower

  pinMode(15, OUTPUT); //Buzzer


  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

int bcdToDecimal(int bcd) {
  return (bcd >> 4) * 10 + (bcd & 0x0F); // Convert BCD to decimal
}

void loop() {
  DateTime now = rtc.now();
  int currentHour = bcdToDecimal(now.hour());
  int currentMinute = bcdToDecimal(now.minute());

  Serial.print(currentHour);
  Serial.println(currentMinute);
  
  if (currentMinute >= 20 && currentMinute <= 36 && !taskDone) {
    digitalWrite(13, HIGH); // Turn on LEDs
    digitalWrite(16, HIGH);
    digitalWrite(0, HIGH);
    digitalWrite(12, HIGH);

    digitalWrite(15, HIGH);
  } else {
    digitalWrite(13, LOW); // Turn off LEDs
    digitalWrite(16, LOW);
    digitalWrite(0, LOW);
    digitalWrite(12, LOW);

    digitalWrite(15, LOW);
  }

  if (digitalRead(touchSensorPin) == HIGH) {
    Serial.println("\nTask marked as done!");
    taskDone = true; // Mark task as done
  }
  Serial.print("..");
  // digitalWrite(16, HIGH);

  // if (currentMinute != 20) {
  //   taskDone = false;
  // }
  if (currentMinute >= 33) {
    taskDone = false;
  }

  delay(1000);
}
