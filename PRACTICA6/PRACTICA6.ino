#include <SparkFun_ADXL345.h>


#include <Wire.h>
#include <SparkFun_ADXL345.h>
#include <LedControl.h>

//Directivasd de Preprocesado
#define DIN 12
#define CLK 11
#define CS 10

//Variables
float ex, ez;
float promedio;

//Animaciones
byte derecha5[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000010,
  B00000010,
  B00000000,
  B00000000,
  B00000000
};

byte derecha4[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000110,
  B00000110,
  B00000000,
  B00000000,
  B00000000
};

byte derecha3[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000100,
  B00000100,
  B00000000,
  B00000000,
  B00000000
};

byte derecha2[] = {
  B00000000,
  B00000000,
  B00000000,
  B00001100,
  B00001100,
  B00000000,
  B00000000,
  B00000000
};

byte derecha1[] = {
  B00000000,
  B00000000,
  B00000000,
  B00001000,
  B00001000,
  B00000000,
  B00000000,
  B00000000
};

byte centro[] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
};

byte izquierda1[] = {
  B00000000,
  B00000000,
  B00000000,
  B00010000,
  B00010000,
  B00000000,
  B00000000,
  B00000000
};

byte izquierda2[] = {
  B00000000,
  B00000000,
  B00000000,
  B00110000,
  B00110000,
  B00000000,
  B00000000,
  B00000000
};

byte izquierda3[] = {
  B00000000,
  B00000000,
  B00000000,
  B00100000,
  B00100000,
  B00000000,
  B00000000,
  B00000000
};

byte izquierda4[] = {
  B00000000,
  B00000000,
  B00000000,
  B01100000,
  B01100000,
  B00000000,
  B00000000,
  B00000000
};

byte izquierda5[] = {
  B00000000,
  B00000000,
  B00000000,
  B01000000,
  B01000000,
  B00000000,
  B00000000,
  B00000000
};

//Constructores
LedControl matriz = LedControl(DIN, CLK, CS, 1);
ADXL345 nivel = ADXL345();

//Funciones
void RepresentarMatriz(byte *Datos);
void medicion();
void niveles();

void setup() {
  Serial.begin(9600);
  matriz.shutdown(0, false);
  matriz.setIntensity(0, 10); // La valores estan entre 1 y 15
  matriz.clearDisplay(0);
  nivel.powerOn();
  nivel.setRangeSetting(8);       //Definir el rango
}

void loop() {
  medicion();
  niveles();
}

void medicion() {
  int suma = 0;
  int x, y, z;
  nivel.readAccel(&x, &y, &z);
  ex = x * 0.0039;
  ez = z * 0.0039;
  float divi = ex / ez;
  promedio = atan(divi) * 57.296;
}

void niveles() {
  Serial.println(promedio);

  if ((promedio < -60) && (promedio >= -90)) {
    RepresentarMatriz(derecha5);
  }

  if ((promedio < -45) && (promedio >= -60)) {
    RepresentarMatriz(derecha4);
  }

  if ((promedio < -30) && (promedio >= -45)) {
    RepresentarMatriz(derecha3);
  }

  if ((promedio < -15) && (promedio >= -30)) {
    RepresentarMatriz(derecha2);
  }

  if ((promedio < -5) && (promedio >= -15)) {
    RepresentarMatriz(derecha1);
  }

  if ((promedio >= -5) && (promedio <= 5)) {
    RepresentarMatriz(centro);
  }

  if ((promedio > 5) && (promedio <= 15)) {
    RepresentarMatriz(izquierda1);
  }

  if ((promedio > 15) && (promedio <= 30)) {
    RepresentarMatriz(izquierda2);
  }

  if ((promedio > 30) && (promedio <= 45)) {
    RepresentarMatriz(izquierda3);
  }

  if ((promedio > 45) && (promedio <= 60)) {
    RepresentarMatriz(izquierda4);
  }

  if ((promedio > 60) && (promedio <= 90)) {
    RepresentarMatriz(izquierda5);
  }

  if (promedio > 90) {
    RepresentarMatriz(izquierda5);
    RepresentarMatriz(derecha5);
  }
}

void RepresentarMatriz(byte *Datos) { //Representa los bytes de datos para una matriz de 8x8
  //Llamar animación :  RepresentarMatriz(Mensaje_n,time);
  for (int i = 0; i < 8; i++) {
    matriz.setColumn(0, i, Datos[7 - i]);
  }
}
