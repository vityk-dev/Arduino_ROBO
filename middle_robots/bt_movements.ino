#include <SoftwareSerial.h>
// ------------ PINY ------------
//piny bluetooth
int rx = 2;
int tx = 3;

//piny silnikow
int motor_left_pin1 = 4;
int motor_left_pin2 = 5;
int motor_right_pin1 = 6;
int motor_right_pin2 = 7;

// ------------ ZMIENNE ------------
SoftwareSerial bt(rx, tx);
char data; // zmienna do ktorej przepisujemy nasze komendy z bluetooth
int car_speed = 100;

// ------------ FUNKCJE ------------
void forward() {
  //lewy silnik
  digitalWrite(motor_left_pin1, LOW);
  analogWrite(motor_left_pin2, 1.2*car_speed); //dostosuj 1.2 tak aby predkosc byla w miare rowna
  //prawy silnik
  digitalWrite(motor_right_pin1, LOW);
  analogWrite(motor_right_pin2, 1*car_speed); //dostosuj 1.2 tak aby predkosc byla w miare rowna
}
void backward() {
  //lewy silnik
  digitalWrite(motor_left_pin1, HIGH);
  analogWrite(motor_left_pin2, 1.2*car_speed); //dostosuj 1.2 tak aby predkosc byla w miare rowna
  //prawy silnik
  digitalWrite(motor_right_pin1, HIGH);
  analogWrite(motor_right_pin2, 1.2*car_speed); //dostosuj 1.2 tak aby predkosc byla w miare rowna
}
void right() {
  //lewy silnik
  digitalWrite(motor_left_pin1, HIGH);
  analogWrite(motor_left_pin2, 1.2*car_speed); //dostosuj 1.2 tak aby predkosc byla w miare rowna
  //prawy silnik
  digitalWrite(motor_right_pin1, LOW);
  analogWrite(motor_right_pin2, 0); //jezeli nie dziala sprobuj dac tutaj 255
}
void left() {
  //lewy silnik
  digitalWrite(motor_left_pin1, LOW);
  analogWrite(motor_left_pin2, 0); //jezeli nie dziala sprobuj dac tutaj 255
  //prawy silnik
  digitalWrite(motor_right_pin1, HIGH);
  analogWrite(motor_right_pin2, 1.2*car_speed); //dostosuj 1.2 tak aby predkosc byla w miare rowna
}
void stp() {
  //lewy silnik
  digitalWrite(motor_left_pin1, LOW);
  analogWrite(motor_left_pin2, 0); //jezeli nie dziala sprobuj dac tutaj 255
  //prawy silnik
  digitalWrite(motor_right_pin1, LOW);
  analogWrite(motor_right_pin2, 0); //jezeli nie dziala sprobuj dac tutaj 255
}

// ------------ PROGRAM GLOWNY ------------

void setup() {
  //predkosc bluetooth
  bt.begin(9600);
  
  //pinmody dla silnikow
  for(int i = motor_left_pin1; i <= motor_right_pin2; i++) {
    pinMode(i, OUTPUT); 
  }
}

void loop() {
  if(bt.available()) { //sprawdzamy czy bluetooth dostepny
    data = bt.read();
    if(data == 'S'){
      stp();
    }
    else if(data == 'F'){
      forward();
    }
    else if(data == 'B'){
      backward();
    }
    else if(data == 'L'){
      left();
    }
    else if(data == 'R'){
      right();
    }
  }
}
