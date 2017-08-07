/*Fichier Header de la librairie HCSR04*/
#ifndef PT100_h
#define PT100_h
//Inclusion des librairies externes
#include "Arduino.h"
#include "i2cRegister.h"
#define byte unsigned char
//Constantes
//Declaration des constantes mathematiques pour la PT100
#define A 3.9083E-3
#define B -5.775E-7
//Declaration de la valeur de resistance du pont diviseur
#define R 4.7E3
//Declaration de la resistance de reference de la PT100
#define R0 100.0
//Tension de reference
#define UREF 5
//Declaration des parametre d'amplification
#define R3 470E3
#define R2 12.2E3
//Definition de la classe HCSR04
class PT100
{
  public :
    PT100(int tempPin, i2cRegister *Registre);
    void lectureTemperature();
    void calibrationTemperature();
  private :
    //Declaration du pointeur de Registre
    i2cRegister *_Registre = 0;
    //Declaration du pin temperature
    int _tempPin;
};
#endif
