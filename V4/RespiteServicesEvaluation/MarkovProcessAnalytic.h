/*
 * MarkovProcessAnalytic.h
 *
 *  Created on: 2 avr. 2018
 *      Author: Oussama BATATA
 */

#ifndef MARKOVPROCESSANALYTIC_H_
#define MARKOVPROCESSANALYTIC_H_



#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "InputData.h"
#include "Caregiver.h"
#include "caregiversPopulation.h"
#include "RespiteService.h"



using namespace std;


namespace mySpace {

class MarkovProcessAnalytic {

private:

    unsigned int _timeMaxRespite;//la dur�e maximal d'un service de r�pit
    float _respiteFrequence;//la fr�quence de r�pit
    unsigned int _nbrIterationForMarkoProcess;//Le nombre d'it�ration requis pour calculer la solution analytique
    vector< vector < vector<float> > > _burnoutVector;// La r�partition de la population sur les �tats d'�puisement
    vector< vector < vector <float> > > _respiteVector;//La r�partition de la population sur les �tat de r�pit
    vector < vector <float> > _respiteFrequenceVector;//La r�partition de la population sur les �tat de r�pit
    vector< vector < vector < vector < float>  > > > _burnoutMatrix;//La matrice de transition entre les �tas d'�puisement
    vector< vector < vector < vector < float>  > > > _respiteMatrix;//La matrice de transition entre les �tas de r�pit

    vector< vector<float> > _kpiResults;//un vector pour stocker nos r�sultats

    //Pointeur
    InputData *_inputData;//pointeur vers la classe inputData




public:
    // Constructeur 1
    MarkovProcessAnalytic(InputData *inputData);
    // Constructeur 2: pour faire l'optimisation
    MarkovProcessAnalytic(InputData *inputData, vector < vector <float> > respiteFrequenceVector);
    //Constructeur 3
    MarkovProcessAnalytic();


    //generer l'instance
    void generateInstance(bool &valchoose);

    //print instance
    void printInstance();


    //generer les matrice de r�pit
    void generateRespiteMatrix();

    //adapter la matrice de burnout �volution � la matrice de r�pit
    void adaptBurnoutMatrix();

   //generer r�partition de la population sur les �tats d'�puisement
    void genrateBurnoutRepartition();

  // generer la r�partion de la popularion sur les �tats de r�pit
    void generateRespiteRepartition();

 // generer le vecteur des fr�quences de r�pit
    void generateVectorRespiteFrequence();

 // verifier la matrice de Markckov
    void checkMarkovMatrix();

  //Mettre � jour le vecteur d'�puisement
    void updateBurnoutVector();

  //Mettre � jour le vecteur de r�pit
    void updateRespiteVector();

 //

  // Calculer la r�partition stationnaire de notre population
    void stationnaryPolicy();

  //calculer le KPI
    void getKpiResults();


    //r�cuperer le nb d'aidant en hospitalization
    float getNbHospitalization();

    // recuperer les ressources de r�pit
    float getRespiteRessources();

};


inline MarkovProcessAnalytic::MarkovProcessAnalytic(InputData * inputData):
	   _timeMaxRespite(0), _respiteFrequence(0), _nbrIterationForMarkoProcess(0) {this->_inputData = inputData;}

inline MarkovProcessAnalytic::MarkovProcessAnalytic(InputData * inputData, vector < vector <float> > respiteFrequenceVector):
	   _timeMaxRespite(0), _respiteFrequence(0), _nbrIterationForMarkoProcess(0), _respiteFrequenceVector(respiteFrequenceVector) {this->_inputData = inputData;}

inline MarkovProcessAnalytic::MarkovProcessAnalytic():
	   _timeMaxRespite(0), _respiteFrequence(0),  _nbrIterationForMarkoProcess(0) {}
} /* namespace mySpace */

#endif /* MARKOVPROCESSANALYTIC_H_ */
