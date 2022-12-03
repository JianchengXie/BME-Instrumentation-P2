#include <Arduino.h>
#include <TinyMPU6050.h>

/*
 *  Constructing MPU-6050
 */
MPU6050 mpu (Wire);
double AngInitialX;
double AngInitialY;
double AngInitialZ;
int eye_LR_threshold = 20;
int eye__UD_threshold = 20;
int move_threshold = 20;

void PrintGets() {
    // Show angles based on both gyroscope and accelerometer
  if (AngInitialX == 0) {
    AngInitialX = mpu.GetAngX();
    AngInitialY = mpu.GetAngY();
    AngInitialZ = mpu.GetAngZ();
  }
  double AngX = mpu.GetAngX();
  double AngY = mpu.GetAngY();
  double AngZ = mpu.GetAngZ();
  Serial.println(AngInitialX);
  Serial.println(AngInitialY);
  Serial.println(AngInitialZ);
  if (AngX > (AngInitialX + eye__UD_threshold)) {
    Serial.println("looking up");
  }
  else if (AngX < (AngInitialX - eye__UD_threshold)) {
    Serial.println("looking down");
  }
  if (AngY > (AngInitialY + move_threshold)) {
    Serial.println("moving right");
  }
  else if (AngY < (AngInitialY - move_threshold)) {
    Serial.println("moving left");
  }
  if (AngZ > (AngInitialZ + eye_LR_threshold)) {
    Serial.println("looking left");
  }
  else if (AngZ < (AngInitialZ - eye_LR_threshold)) {
    Serial.println("looking right");
  }
  Serial.println(AngX);
  Serial.println(AngY);
  Serial.println(AngZ);
  Serial.println();
}

void setup() {
  // Initialization
  mpu.Initialize();

  // Calibration
  Serial.begin(115200);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");
}

void loop() {
  mpu.Execute();
  PrintGets();
}
