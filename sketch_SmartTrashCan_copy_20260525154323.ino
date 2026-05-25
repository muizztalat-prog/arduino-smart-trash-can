#include <Servo.h>
#include <IRremote.h>

const int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

const int controlPin1 = 2;
const int controlPin2 = 3;
const int controlPin3 = 10;
const int controlPin4 = 12;

const int servoPin = 11;
const int trigPin = 8;
const int echoPin = 9;
Servo servoMotor;

int buzzer = 6;
int LED = 4;

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn();
    irrecv.blink13(true);

    pinMode(controlPin1, OUTPUT);
    pinMode(controlPin2, OUTPUT);
    pinMode(controlPin3, OUTPUT);
    pinMode(controlPin4, OUTPUT);

    servoMotor.attach(servoPin);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(buzzer, OUTPUT);
    pinMode(LED, OUTPUT);
}

void forward() {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
    digitalWrite(controlPin3, HIGH);
    digitalWrite(controlPin4, LOW);
}

void backward() {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
    digitalWrite(controlPin3, LOW);
    digitalWrite(controlPin4, HIGH);
}

void right() {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
    digitalWrite(controlPin3, LOW);
    digitalWrite(controlPin4, LOW);
}

void left() {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
    digitalWrite(controlPin3, HIGH);
    digitalWrite(controlPin4, LOW);
}

void stopMotor() {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
    digitalWrite(controlPin3, LOW);
    digitalWrite(controlPin4, LOW);
}

void buzzerTone() {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
}

float getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    float duration = pulseIn(echoPin, HIGH);
    float cm =  duration/74/2;  // Convert to cm
    return cm;
}

void loop() {
    float cm = getDistance();

    if (cm < 5) {
        digitalWrite(LED, HIGH);
        buzzerTone();
        servoMotor.write(150);
       delay (3000);
    } else {
        digitalWrite(LED, LOW);
        servoMotor.write(0);
        delay(15);
    }

    Serial.print("Distance: ");
    Serial.print(cm);
    Serial.println(" cm");

    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        irrecv.resume();

        if (results.value == 0x20D350AF) { // Down button
            backward();
              digitalWrite(buzzer,LOW);
     digitalWrite(LED,LOW);

        } else if (results.value == 0x20D3609F) { // Up button
            forward();
              digitalWrite(buzzer,LOW);
     digitalWrite(LED,LOW);

        } else if (results.value == 0x20D3C23D) { // Right button
            right();
              digitalWrite(buzzer,LOW);
     digitalWrite(LED,LOW);

        } else if (results.value == 0x20D3807F) { // Left button
            left();
              digitalWrite(buzzer,LOW);
     digitalWrite(LED,LOW);

        } else if (results.value == 0x20D340BF) { // Stop button
            stopMotor();
              digitalWrite(buzzer,LOW);
     digitalWrite(LED,LOW);

        }
    }
}


