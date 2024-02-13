
#define M_L_dir_pin 7
#define M_R_dir_pin 8
#define M_L_pwm_pin 9
#define M_R_pwm_pin 10
#define led_pin 4

#include <LiquidCrystal.h>
const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define opA_R 24  
#define opB_R 2   

#define opA_L 23  
#define opB_L 3   
#define M_forward 0
#define M_return 1

const float steps_per_cm = 40 / 13.0;         
const float steps_per_degree_R = 10 / 1000.0;  
const float steps_per_degree_L = 10 / 1000.0;  
const int y_speed = 100;                       
const int x_speed = 100;                      

String message = "";
String command = "";
String value = "";

int forward_or_return = M_forward;
int on_or_off = LOW;  
String wheel_to_turn = "";
float T_steps = 0;

int counter_R = 0;  
int counter_L = 0;  
int cStateA_R, cStateA_L;
int lastStateA_R, lastStateA_L;

  void setup() {
  pinMode(opA_R, INPUT);
  pinMode(opB_R, INPUT);
  pinMode(opA_L, INPUT);
  pinMode(opB_L, INPUT);
  pinMode(led_pin,  opB_R);
  lastStateA_R = digitalRead(opA_R);
  lastStateA_L = digitalRead(opA_L);
  Serial.begin(9600);
  while (!Serial) {
    ;  
  }
  Serial.println("Write some command: someValue to serial monitor");
  lcd.begin(20, 4);
}

  void loop() {
  while (Serial.available() > 0) {
    message = Serial.readStringUntil('\n');
    
    command = message.substring(0, message.indexOf(":"));
    value = message.substring(message.indexOf(":") + 1);

    Serial.print("\nCommand: ");
    Serial.print(command);
    Serial.print("\tValue: ");
    Serial.println(value);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Command: ");
    lcd.print(command);
    lcd.setCursor(0, 1);
    //lcd.print("Value: ");
    lcd.println(value);
    
    if (command == "LED") {
      if (value == "ON")
        on_or_off = HIGH;
      else if (value == "OFF")
        on_or_off = LOW;
    }
    else if (command == "Move") {
      counter_R = 0;
      float distance = value.toFloat();
      T_steps = abs(steps_per_cm * distance);

      if (distance > 0) {
        forward_or_return = M_forward;
        Serial.print("M_forward");
      } else if (distance < 0) {
        forward_or_return = M_return;
        Serial.print("M_return");
      }
    }
    else if (command == "Turn") {
      counter_R = 0;
      counter_L = 0;
      float angular = value.toFloat();

      if (angular > 0) {
        T_steps = abs(steps_per_degree_L * angular);
        wheel_to_turn = "left";
        Serial.print("Turn_right");
      } else if (angular < 0) {
        T_steps = abs(steps_per_degree_R * angular);
        wheel_to_turn = "right";
        Serial.print("Turn_left");
      }
    }
    Serial.print("\tT_steps: ");
    Serial.println(T_steps);
  }
  
  digitalWrite(led_pin, on_or_off);
 
  if (command == "Move") {
    if (counter_R < T_steps) {
      digitalWrite(M_R_dir_pin, forward_or_return);
      Serial.print("hi");
      digitalWrite(M_L_dir_pin, forward_or_return);
      analogWrite(M_L_pwm_pin, y_speed);
      analogWrite(M_R_pwm_pin, y_speed);
    } else {
      analogWrite(M_L_pwm_pin, 0);
      analogWrite(M_R_pwm_pin, 0);
    }
  }
  
  else if (command == "Turn" && wheel_to_turn == "left") {
    if (counter_L < T_steps) {
      digitalWrite(M_L_dir_pin, M_forward);
      analogWrite(M_L_pwm_pin, x_speed);
    } else {
      analogWrite(M_L_pwm_pin, 0);
    }
  } else if (command == "Turn" && wheel_to_turn == "right") {
    if (counter_R < T_steps) {
      digitalWrite(M_R_dir_pin, M_forward);
      analogWrite(M_R_pwm_pin, x_speed);
    } else {
      analogWrite(M_R_pwm_pin, 0);
    }
  }
  
  cStateA_L = digitalRead(opA_L);
  if (cStateA_L != lastStateA_L && cStateA_L == 1) {
    counter_L++;
    Serial.print("Left counter: ");
    Serial.print(counter_L);
  }
  lastStateA_L = cStateA_L;
  delay(1);

  cStateA_R = digitalRead(opA_R);
  if (cStateA_R != lastStateA_R && cStateA_R == 1) {
    counter_R++;
    Serial.print("Right counter: ");
    Serial.println(counter_R);
  }
  lastStateA_R = cStateA_R;
  delay(1);
}