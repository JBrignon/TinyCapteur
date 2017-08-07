//Inclusion du header
#include "PT100.h"
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
//Declaration du constructeur
PT100::PT100(int tempPin, i2cRegister *Registre)
{
  _tempPin = tempPin;
  _Registre = Registre;
}
void PT100::lectureTemperature()
{
  //Lecture de l'entrée analogique
  float US = (analogRead(_tempPin)*(UREF/1023.0));
  //Conversion de la tension
  float U2 = (US*R2)/(R2+R3); 
  //Calcul de la resistance
  float PT100 = (U2*R)/(5-U2);
  //Calcul de la temperature suivant les caracteristique de la PT100 et enregistrement dans le registre
  _Registre->storeFloat(0x00,_Registre->readFloat(0x03) + (sqrt(A*A+4*B*((PT100/R0)-1))-A)/(2*B));
}
void PT100::calibrationTemperature()
{
  //Calcul et enregistrement de l'offset dans le registre
  _Registre->storeFloat(0x03,0);
  lectureTemperature();
  _Registre->storeFloat(0x03,(_Registre->readFloat(0x02))-(_Registre->readFloat(0x00)));
  //On nettoie le registre de config
  _Registre->storeInt(0x02,0);
}

