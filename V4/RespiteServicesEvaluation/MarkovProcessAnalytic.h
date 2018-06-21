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

    unsigned int _timeMaxRespite;//la durée maximal d'un service de répit
    float _respiteFrequence;//la fréquence de répit
    unsigned int _nbrIterationForMarkoProcess;//Le nombre d'itération requis pour calculer la solution analytique
    vector< vector < vector<float> > > _burnoutVector;// La répartition de la population sur les états d'épuisement
    vector< vector < vector <float> > > _respiteVector;//La répartition de la population sur les état de répit
    vector < vector <float> > _respiteFrequenceVector;//La répartition de la population sur les état de répit
    vector< vector < vector < vector < float>  > > > _burnoutMatrix;//La matrice de transition entre les étas d'épuisement
    vector< vector < vector < vector < float>  > > > _respiteMatrix;//La matrice de transition entre les étas de répit

    vector< vector<float> > _kpiResults;//un vector pour stocker nos résultats

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


    //generer les matrice de répit
    void generateRespiteMatrix();

    //adapter la matrice de burnout évolution à la matrice de répit
    void adaptBurnoutMatrix();

   //generer répartition de la population sur les états d'épuisement
    void genrateBurnoutRepartition();

  // generer la répartion de la popularion sur les états de répit
    void generateRespiteRepartition();

 // generer le vecteur des fréquences de répit
    void generateVectorRespiteFrequence();

 // verifier la matrice de Markckov
    void checkMarkovMatrix();

  //Mettre à jour le vecteur d'épuisement
    void updateBurnoutVector();

  //Mettre à jour le vecteur de répit
    void updateRespiteVector();

 //

  // Calculer la répartition stationnaire de notre population
    void stationnaryPolicy();

  //calculer le KPI
    void getKpiResults();


    //récuperer le nb d'aidant en hospitalization
    float getNbHospitalization();

    // recuperer les ressources de répit
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
