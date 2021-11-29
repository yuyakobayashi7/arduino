#include <AccelStepper.h>
AccelStepper stepper(1, 8, 9);//s d
AccelStepper stepper2(1, 10, 11);

int i = 0;
int count = 0;

void setup() {
  stepper.setMaxSpeed(400);
  stepper2.setMaxSpeed(400);
  Serial.begin(9600);
}
double ans = 0;
void loop() {
  int right;
  int left ;
  //int a;
  int i, v;
  int s = 18;//センサー間の距離
  int val[9];
  double molecule = 0;
  double denominator = 0;
  int b[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; //
  int x[9] = { -4 * s, -2 * s, 0, 2 * s, 4 * s};
  int rightx = 20;
  int leftx = 20;


  for (i = 0; i < 5; i++) {
    val[i] = analogRead(i);
    if (val[i] >= 900) {
      molecule += b[i] * 0.5 *  x[i];  //bi反応したセンサーの数 × xi(センサーの距離に応じた重み)
      denominator += b[i];// 反応したセンサーの数
    }
  }
  ans = molecule / denominator;

  //Serial.println(ans);

  right = (ans * rightx);
  left =  (ans * leftx);
  //Serial.print(right);
  //Serial.print("   ");
  //Serial.println(left);

  if (ans > 0) {
    left = left * 1.3;
    right = right * 0.2;
  }
  if (ans < 0) {
    right = right * -1.3;
    left = left * -0.2;
  }
  if (ans == 0) {
    right = right + 600;
    left = left + 600;
  }

  //Serial.print(right);
  //Serial.print("   ");
  //Serial.println(left);

  stepper.setSpeed (-right);
  stepper2.setSpeed(left);
  stepper.runSpeed();
  stepper2.runSpeed();
}
