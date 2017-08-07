/*Capteur de niveau d'eau et temperature i2c via AtTiny - Julien BRIGNON - 2017*/
#include <TinyWireS.h>
#include "i2cRegister.h"
#include "HCSR04.h"
#include "PT100.h"
#define byte unsigned char
//Declaration des constantes de l'i2c
i2cRegister Registre;
#define i2c_addr 0x04
//Declaration des objets PT100 et HCSR04
PT100 capteurTemperature(3,&Registre);
HCSR04 capteurNiveau(1,4,&Registre);
//Modification de la taille du buffer i2c
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 64 )
#endif
//Declaration de la variable globale de navigation registre
byte CURRENT_REGISTER = 0x00;
//Fonction lorque l'on appel le tiny via i2c
void i2cRequest()
{
  //Actualisation du registre : Temperature
  capteurTemperature.lectureTemperature();
  //Actualisation du registre : Niveau
  capteurNiveau.lectureNiveau();
  //On recupere le MSB et le LSB du registre courant dans un tableau
  byte val[2];
  Registre.getOctet(CURRENT_REGISTER,val);
  //Envoi les valeurs
  TinyWireS.send(val[0]);
  TinyWireS.send(val[1]);
}
//Fonction lors de la reception d'un signal i2c
void i2cReceive(unsigned int available_bytes)
{
   //Le premier byte recu modifie le registre courant
   CURRENT_REGISTER = TinyWireS.receive();
   //On regarde si l'on souhaite simplement changer de registre ou alors ecrire
   available_bytes--;
   if(!available_bytes)
   {
     return;
   }
   else
   {
     byte MSB = TinyWireS.receive();
     byte LSB = TinyWireS.receive();
     Registre.setOctet(CURRENT_REGISTER,MSB,LSB);
     if(CURRENT_REGISTER == 2)
     {
       capteurTemperature.calibrationTemperature();
     }
     //On sauvegarde le registre en EEPROM
     Registre.saveEEPROM();
   }
}
//Initialisation du MCU
void setup() 
{
  //Initialisation des pins Trigger/Echo pour le capteur ultrasons
  pinMode(4,INPUT);
  pinMode(1,OUTPUT);
  //Initialisation du pin pour la sonde PT100
  pinMode(3,INPUT);
  //Initialisation du registre i2c depuis l'EEPROM
  Registre.readEEPROM();
  //Initialisation de l'i2c en esclave
  TinyWireS.begin(i2c_addr);
  //Definition des fonctions evenement i2c
  TinyWireS.onRequest(i2cRequest);
  TinyWireS.onReceive(i2cReceive);
}
//Boucle Principale
void loop() 
{
  //i2c
  TinyWireS_stop_check();
}
