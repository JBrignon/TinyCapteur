//Inclusion du header
#include "statEngine.h"
//Declaration du constructeur
statEngine::statEngine()
{
  _precisionStatistique = 1; 
}
statEngine::statEngine(int precisionStatistique)
{
  _precisionStatistique = precisionStatistique;
}
//Fonction moyenne
float statEngine::statMoyenne(float *val)
{
  float moyenne = 0;
  for(int i=0; i<_precisionStatistique; i++)
  {
    moyenne += val[i];
  }
  return(moyenne/_precisionStatistique);
}
void statEngine::setPrecision(int precisionStatistique)
{
  _precisionStatistique = precisionStatistique;
}
int statEngine::getPrecision()
{
  return _precisionStatistique;
}

