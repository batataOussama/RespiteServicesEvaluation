/*
 * Simulation.h
 *
 *  Created on: 5 juil. 2017
 *      Author: Oussama BATATA
 */

#ifndef SIMULATION_SIMULATION_H_
#define SIMULATION_SIMULATION_H_


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "caregiversPopulation.h"
#include "Caregiver.h"
#include "RespiteService.h"
#include "InputData.h"
using namespace std;


namespace mySpace {

class Simulation {
private:
	unsigned int _timeSlots;// Le nombre de pas de temps de notre simulation
	float _randParamRespite;// Le paramètre de notre lois de probabilité quand les caregivers prennent du répit
	unsigned int _nbReplication;// Le nombre de réplication requis pour valider statistiquement notre simulation

	//reuslts
	vector< vector < vector < unsigned int> > > _results;//

    // Pointeurs vers les classes; RespiteService & Caregiver
	caregiversPopulation *_population;
	Caregiver *_caregiver;
    RespiteService *_service;
    InputData *_inputData;

public:
    //Constructeur
    Simulation(caregiversPopulation *population, Caregiver *caregiver, RespiteService *service, InputData *inputData);

    Simulation(InputData *inputData);
//-----------------------------------------------------------------------------------------------------------------------------------
    //----------------------------------------     Fonction principales        -------------------------------------------------
   void generateInstance();
   vector< vector<unsigned int > > simulate();
   void replicate();
   void randomRespiteAssignCaregiver(unsigned int &idCaregiver, unsigned int &idCluster, caregiversPopulation &population);
   void evaluateKpiInRealData(vector< vector<unsigned int> > &realkpi);
   void saveResults();
 //------------------Les gets ------------------------------------------------
   //get timeSlots
   unsigned int getTimeSlots();
   //get randParamRespite
   float getRandParamRespite();



//------------------Les sets ------------------------------------------------
     //set timeSlots
     void setTimeSlots(unsigned int &timeSlots);
     //set randParamRespite
     void setRandParamRespite(float &randParamRespite);


};


//implémentation du constructeur
inline Simulation:: Simulation(caregiversPopulation *population, Caregiver *caregiver, RespiteService *service, InputData *inputData):
 _timeSlots(0), _randParamRespite(0), _nbReplication(0) {this->_population = population, this->_caregiver = caregiver; this->_service = service; this->_inputData = inputData;}

inline Simulation::Simulation(InputData *inputData):
		_timeSlots(0), _randParamRespite(0), _nbReplication(0)  {this->_inputData = inputData;}







} /* namespace mySpace */

#endif /* AGENT_BASED_SIMULATION_SIMULATION_H_ */
