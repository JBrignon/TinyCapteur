/*Fichier Header du moteur de statistique*/
#ifndef statEngine_h
#define statEngine_h
//Definition de la classe statEngine
class statEngine
{
  public :
    //Constructeur
    statEngine();
    statEngine(int precisionStatistique);
    //Fonction qui fait une moyenne sur un tableau de flotant
    float statMoyenne(float *val);
    int getPrecision();
    void setPrecision(int precisionStatistique);
   private:
    //Declaration des variables
    int _precisionStatistique = 1;
};
#endif

