#include <Arduino.h>

int DEVICE_POWER = A2; // Resistance input
int POWERPLANT_POWER = A1; // Resistance input
int VALVE_PIN = 2;
int PUMP_UP_PIN = 3;
int VOLTAGE_SUM_PIN = 4;
int is_pumping = false;
int is_valve_open = false;


int ctr = 0;

void setupRegulation(){
    pinMode(VALVE_PIN, OUTPUT);
    pinMode(PUMP_UP_PIN, OUTPUT);
    pinMode(VOLTAGE_SUM_PIN, OUTPUT);
}
void regulatePower(){
    int powerplant_power = analogRead(POWERPLANT_POWER);
    int device_power = analogRead(DEVICE_POWER);
    if (ctr == 1000){
        Serial.print(powerplant_power);
        Serial.print(";");
        Serial.print(device_power);
        Serial.print(";");
        Serial.print(is_pumping);
        Serial.print(";");
        Serial.println(is_valve_open);
        ctr = 0;
    }

    // if we are using more then producing, then open valve;
    ctr++;
    if(device_power - powerplant_power >= 100){
        digitalWrite(VALVE_PIN, LOW);
        is_valve_open = 1;
    } else if (device_power - powerplant_power <= 90){
        digitalWrite(VALVE_PIN, HIGH);
        is_valve_open = 0;
    }

    if(powerplant_power - device_power >= 100){
        digitalWrite(PUMP_UP_PIN, HIGH);
        is_pumping = 1;
    } else if (powerplant_power - device_power <= 90){
        digitalWrite(PUMP_UP_PIN, LOW);
        is_pumping = 0;
    }
}

void setup() {
    Serial.begin(9600);
    setupRegulation();
}

void loop() {
    regulatePower();

}