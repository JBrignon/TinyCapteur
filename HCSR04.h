/*Fichier Header de la librairie HCSR04*/
#ifndef HCSR04_h
#define HCSR04_h
//Inclusion des librairies externes
#include "Arduino.h"
#include "statEngine.h"
#include "i2cRegister.h"
#define byte unsigned char
//Definition de la classe HCSR04
class HCSR04
{
  public :
    HCSR04(int triggerPin, int echoPin, int pause, int precisionStatistique, i2cRegister *Registre);
    float mesureDistance();
    float rawDistance();
    float getSoundSpeed();
    void lectureNiveau();
  private :
    //Declaration du pointeur de registre
    i2cRegister *_Registre = 0;
    //Declaration des caracteristiques du capteur
    int _triggerPin;
    int _echoPin;
    int _pause;
    //Declaration de l'objet statistique
    statEngine _Stat;
    int _precisionStatistique;
};
#endif
