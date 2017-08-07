//Inclusion du header
#include "HCSR04.h"
//Inclusion des librairies externes
#include "Arduino.h"
#include "i2cRegister.h"
#define byte unsigned char
//Declaration du constructeur
HCSR04::HCSR04(int triggerPin, int echoPin, i2cRegister *Registre)
{
  _triggerPin = triggerPin;
  _echoPin = echoPin;
  _Registre = Registre;
}
float HCSR04::rawDistance()
{
  //On envoie une requete sur le Trigger
  digitalWrite(_triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(_triggerPin,LOW);
  //On recupere le resultat
  unsigned long signalLength = pulseIn(_echoPin,HIGH);
  //On converti en distance
  float distance = (signalLength*getSoundSpeed())/2;
  //Sauvegarde le registre
  _Registre->storeFloat(0x05,distance);
  //Retour d'information
  return distance;
}
float HCSR04::getSoundSpeed()
{
  //On calcule la vitesse du son en fonction de la temperature (en m.s^(-1))
  float SoundSpeed = 20.05*sqrt(_Registre->readFloat(0x00)+273.15);
  //On retourne la vitesse en mm.uS^(-1)
  return SoundSpeed/1000;
}
void HCSR04::lectureNiveau()
{
  _Registre->storeFloat(0x01,100.0-(rawDistance()*(100.0/(_Registre->readFloat(0x04)))));
}

