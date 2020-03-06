#include <Arduino.h>

unsigned long previousMicros = 0;
//definicion de pines
const int pinMotor1 = 14; // 28BYJ48 - In1
const int pinMotor2 = 12; // 28BYJ48 - In2
const int pinMotor3 = 13; // 28BYJ48 - In3
const int pinMotor4 = 15; // 28BYJ48 - In4
class StepMotor
{
private:
    //definicion variables
    int motorSpeed = 1000; // variable para determinar la velocidad
    // 800 maxima - minima 1000 o mas
    int contadorPasos = 0;     // contador para los pasos
    int pasosPorVuelta = 4076; // pasos para una vuelta completa
    bool clockWiseDirection = true;

    const int cantidadPasos = 8;
    const int tablaPasos[8] = {B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001};
    void writeOutputs(int paso)
    {
        digitalWrite(pinMotor1, bitRead(tablaPasos[paso], 0));
        digitalWrite(pinMotor2, bitRead(tablaPasos[paso], 1));
        digitalWrite(pinMotor3, bitRead(tablaPasos[paso], 2));
        digitalWrite(pinMotor4, bitRead(tablaPasos[paso], 3));
    }

public:
    StepMotor()
    {
        pinMode(pinMotor1, OUTPUT);
        pinMode(pinMotor2, OUTPUT);
        pinMode(pinMotor3, OUTPUT);
        pinMode(pinMotor4, OUTPUT);

        digitalWrite(pinMotor1, HIGH);
        digitalWrite(pinMotor2, LOW);
        digitalWrite(pinMotor3, HIGH);
        digitalWrite(pinMotor4, LOW);
    }

    void clockWise()
    {
        contadorPasos++;
        if (contadorPasos >= cantidadPasos)
            contadorPasos = 0;
        writeOutputs(contadorPasos);
    }
    void counterClockWise()
    {
        contadorPasos--;
        if (contadorPasos < 0)
            contadorPasos = cantidadPasos - 1;
        writeOutputs(contadorPasos);
    }
    void handleMotor()
    {
        unsigned long currentMicros = micros();
        if (currentMicros - previousMicros > motorSpeed)
        {
            previousMicros = currentMicros;
            if (clockWiseDirection)
            {
                clockWise();
            }
            else
            {
                counterClockWise();
            }
        }
    }
    void changeDirection()
    {
        clockWiseDirection = !clockWiseDirection;
    }
};