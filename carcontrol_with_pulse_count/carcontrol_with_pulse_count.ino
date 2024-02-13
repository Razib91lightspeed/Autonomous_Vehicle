#define M_forward         0
#define M_return          1
#define M_L_dir_pin       7
#define M_R_dir_pin       8
#define M_L_pwm_pin       9
#define M_R_pwm_pin       10
#define rstbtn            19


volatile int buttonPin = 19;
const int x_pin = A0, y_pin = A1;
int y_speed = 0;
int x_speed = 0; //turning speed

#define outputA 24     //CLK to D24
#define outputB 2     //DT to D2
volatile long right_wheel_pulse_count = 0;
// include the library code:
#include <LiquidCrystal.h>

const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int counter = 0;// amount of pulses
int currentStateA;
int lastStateA;
String currentDir = "";
const double distance = 50;
const float pi = 3.14; // Pi value
const int R = 2;  //Radius of the wheel from center to edge
int N = 0; //number of steps for one rotation
int n = 170;// this value is known from N
unsigned long lastButtonPress = 0;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(M_L_dir_pin, OUTPUT);
  pinMode(M_R_dir_pin, OUTPUT);
  pinMode(M_L_pwm_pin, OUTPUT);
  pinMode(M_R_pwm_pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(outputB), right_wheel_pulse, RISING);
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  // Setup Serial Monitor
  Serial.begin(9600);

  // Set encoder pins as inputs
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(outputB , INPUT_PULLUP);
  // Read the initial state of outputA
  lastStateA = digitalRead(outputA);

}

void loop()
{
  if (analogRead(y_pin) > 533)
  {
    digitalWrite(M_R_dir_pin, M_forward);
    digitalWrite(M_L_dir_pin, M_forward);
    y_speed = (analogRead(y_pin) / 512.0) * 255 - 255;
  }
  else if (analogRead(y_pin) < 490) {
    digitalWrite(M_R_dir_pin, M_return);
    digitalWrite(M_L_dir_pin, M_return);
    y_speed = -(analogRead(y_pin) / 512.0) * 255 + 255;
  }
  else {
    y_speed = 0;
  }
  analogWrite(M_L_pwm_pin, y_speed);
  analogWrite(M_R_pwm_pin, y_speed);

  if (analogRead(x_pin) < 490) {
    digitalWrite(M_R_dir_pin, HIGH);
    digitalWrite(M_L_dir_pin, LOW);
    x_speed = -(analogRead(x_pin) / 512.0) * 255 + 255;
    analogWrite(M_R_pwm_pin, x_speed);
  }
  else if (analogRead(x_pin) > 533)
  {
    digitalWrite(M_R_dir_pin, LOW);
    digitalWrite(M_L_dir_pin, HIGH);
    x_speed = (analogRead(x_pin) / 512.0) * 255 - 255;
    analogWrite(M_L_pwm_pin, x_speed);
  }
  else {
    x_speed = 0;
  }



  currentStateA = digitalRead(outputA);

  if (currentStateA != lastStateA  && currentStateA == 1) {

    if (digitalRead(outputB) != currentStateA) {
      counter --;
      currentDir = "ACW";
    }
    else {
      counter ++;
      currentDir = "CW ";
    }

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Total counter: ");
    Serial.print(counter);// counter for one round is the steps number
    Serial.print("| Average");
    Serial.println(((2 * pi * R) / distance) * counter);

    lcd.setCursor(0, 0);
    lcd.print("Dir: ");
    lcd.setCursor(5, 0);
    lcd.print(currentDir);

    lcd.setCursor(0, 1);
    lcd.print("total: ");
    lcd.setCursor(12, 1);
    lcd.print(counter);

    lcd.setCursor(0, 2);
    lcd.print("average: ");
    lcd.setCursor(12, 2);
    N = ((2 * pi * R) / distance) * counter;
    lcd.print(N);
  }
  lastStateA = currentStateA;
  delay(1);

  if (digitalRead(rstbtn) == LOW) {
    counter = 0;

    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
    }
    lastButtonPress = millis();
  }
  Serial.print(" Pulses: ");
  Serial.println(right_wheel_pulse_count);
}

void right_wheel_pulse() {
  right_wheel_pulse_count++;
}