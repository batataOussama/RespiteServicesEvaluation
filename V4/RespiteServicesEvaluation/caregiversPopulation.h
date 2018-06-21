/*
 * caregiversPopulation.h
 *
 *  Created on: 24 mai 2018
 *      Author: oussama.batata
 */

#ifndef CAREGIVERSPOPULATION_H_
#define CAREGIVERSPOPULATION_H_


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "RespiteService.h"
#include "InputData.h"
#include "Caregiver.h"
using namespace std;

namespace mySpace {

class caregiversPopulation {
private:
    //----- Population de caregivers: ------------------------------------------------------
        unsigned int _nbrCluster;// nombre de cluster d'aidants
	    unsigned int _nbrStatePerCluster;// Nombre d'état à instancier pour chaque communauté(cluster) de notre population
	    vector<unsigned int> _nbrCaregiverPerCluster;//Nombre d'aidant pour chaque cluster
	    unsigned int _timeHorizon; // L'horizon temporelle de notre simulation et des états de la chaîne de Markov
	    vector< vector<  vector<  vector< float>  >  >  > _markovChain;//la chaîne des Markov pour l'épuisement des aidants
	    vector< vector<Caregiver> > _listeCaregiver;//liste pour contenir tout les aidants
		//-------------------------------------------------------

	    //------------Pointeurs vers d'autres classes
	    RespiteService *_respiteService;//Un pointeur vers la classe RespiteService pour gerer l'affectation.
	    InputData * _inputData;
	    Caregiver *_caregiver;

public:
	    // Constructeur
			// constructeur N_1
		caregiversPopulation(Caregiver *caregiver, RespiteService *respiteService, InputData *inputData);
		// constructeur N_2
		caregiversPopulation();

	///



	// Fonctions principales
    void generateInstance();
    void printInstance();

	//Ajouter les aidants dans la population
    void addCaregiver();

    // Récupérer l'aidant par son indice
    Caregiver* getCaregiverByTwoId(unsigned int &id, unsigned int &idCluster);

    //Update State
        void updateState(unsigned int &idCluster, unsigned int &id, unsigned int &timePeriode);

    // Print table of caregivers population
    void print();



    // Get les attributs de la population

unsigned int getNbrCluser();
unsigned int getNbrStatePerCluster();
unsigned int getNbrCaregiverPerCluster(unsigned int &ind);
unsigned int getTimeHorizon();

   //un get special pour notre iducateur de performance
   // Get le nombre d'aidant en état d'urgence
unsigned int getNumberOfCaregiverInEmergency(unsigned int &idCLuster);
//-----------------------------------------------------------------

};


//Implementation du constructeur N_1
inline caregiversPopulation::caregiversPopulation(Caregiver *caregiver, RespiteService *respiteService,  InputData *inputData):
	_nbrCluster(0), _nbrStatePerCluster(0), _timeHorizon(0) {this->_caregiver = caregiver, this->_respiteService = respiteService;this->_inputData = inputData;}

//Implementation du constructeur N_2
inline caregiversPopulation::caregiversPopulation():
		_nbrCluster(0), _nbrStatePerCluster(0), _timeHorizon(0)  {}

} /* namespace mySpace */

#endif /* CAREGIVERSPOPULATION_H_ */
