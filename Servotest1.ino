#include <Servo.h>
// #define led1 6
#define xPin 4
#define yPin 5
int sensorValue1 = 0;
int sensorValue2 = 0;
Servo servo_x;
Servo servo_y;
int angle_xpl;
int angle_ypl;
int angle_x, angle_y, x_data, y_data;
String pyData;
void attach_servo() {
  servo_x.attach(xPin);
  servo_y.attach(yPin);
}
int swsetzero = 12;
int swzerost = 0;

void setup() {
  pinMode(swsetzero, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);

  attach_servo();
  servo_x.write(95);
  servo_y.write(0);

  Serial.begin(2000000);
  Serial.setTimeout(1);
}
void loop() {
  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  if (digitalRead(swsetzero) == 0) {
    if (swzerost == 0) {
      // Serial.println("set zero!");
      digitalWrite(6, LOW);
      swzerost = 1;

    } else {
      // Serial.println("1");
      digitalWrite(6, HIGH);
      swzerost = 0;
    }
    // delay(250);
  }
  if (swzerost == 0) {
    angle_xpl = sensorValue1 * (0.175953);  //0-180
    angle_ypl = sensorValue2 * (0.175953);  //0-140
    // Serial.println(angle_xpl);
    servo_x.write(angle_xpl);
    servo_y.write(angle_ypl);
  }

  if (swzerost == 1) {
    // while (!Serial.available())
    //   ;
    if (Serial.available() > 0) {
      pyData = Serial.readString();
      x_data = pyData.substring(0, pyData.indexOf(" ")).toInt();
      y_data = pyData.substring(pyData.indexOf(" ") + 1).toInt();
      angle_x = map(x_data, 0, 640, 45, 135);
      angle_y = map(y_data, 0, 480, 90, 180);
      angle_x = angle_x + sensorValue1 * (0.175953);
      angle_y = angle_y + sensorValue2 * (0.175953);
      Serial.println();
      servo_x.write(angle_x);
      servo_y.write(angle_y);
      Serial.flush();
    }
  }
}