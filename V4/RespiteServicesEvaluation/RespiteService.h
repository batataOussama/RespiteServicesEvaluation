/*
 * RespiteService.h
 *
 *  Created on: 6 avr. 2017
 *      Author: Oussama BATATA
 */

#ifndef SIMULATION_RESPITESERVICE_H_
#define SIMULATION_RESPITESERVICE_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "InputData.h"

using namespace std;

namespace mySpace {

class RespiteService {
private:
	// Les attributs de chaque service de répit
	unsigned int _id; // l'ID du service.
	string _typeService; // Le type de service de répit.
	unsigned int _nbrBeds; // Nombre de lis dont dispose l'etablissement.
	unsigned int _availableBeds; // Nombre de lits disponibles
	unsigned int _costRespiteService;// Coût d'une nuit l'etablissement.
    double _respiteImpact;//L'importance accordé au service dans le rétablissement de l'aidant(caregiver) après la visite de ce service en question;
    unsigned int _durationOfrespite; // la durrée de répit affecté par un service à un aidant
    //------------------------------------------------------------------------------------
    // Les attributs pour construire un ensemble de services de répit plus un hôpital
    unsigned int _nbrServices;//Nombre de services de répit + l'hôpital

    //----------------pointeur vers data
    InputData *_inputData;

public:
	//Constructeur
    //---------------
	//   Constructueur 1 : Pour initialiser tout les services de répit
	RespiteService(InputData *inputData);
	//    Constructeur 2 : Pour instancier chaque service de répit
	RespiteService(unsigned int id, string typeService, unsigned int nbrBeds, unsigned int availableBeds, unsigned int costRespiteService, double respiteImpact, unsigned int durationOfrespite);
	//    Constructeur 3 :
	RespiteService();




//    //--------------------------------------------------------------------------------------------------------------------------
//    	//------------------------Fonction principales----------------------------------------------------------------------


	void generateInstance();

	//Fonction : instancier chaque service de répit + hôpital
	void addRespiteService();

	// Récuperer un service de répit par on id
	RespiteService* getRespiteServiceById(unsigned int &id);
	// afficher les services de répit
	void print();
//
//    //Update Occupation
//    void updateOccupation();
//
//    // Affecter une durée de répit à un aidant
//    unsigned int affectDurationToCaregiver();
//    //------------------------------------------------------------------------------------------------------------------------------
//
//
//
//--------------------------------------------------------------------------------------------------------------------
//------------------Les gets ------------------------------------------------


	// get les attributs de l'ensemble des services
	//get NbrServices
    unsigned int getNbrServcies();

//get nbrBeds
unsigned int getNbrBeds();
//get availableBeds
unsigned int getAvailableBeds();
//get nbrBeds
unsigned int getCostRespiteService();
//get nbrBeds
double getRespiteImpact();
//get nbrBeds
unsigned int getDurationOfrespite();
//get Type Service par nom
string getTypeRespite();



//
// //--------------------------------------------------------------------------------------------------------------------
	//    	//------------------Les sets ------------------------------------------------

// set les attributs de l'ensemble des services
//set NbrServices
void setNbrServcies(unsigned int &nbServices);

//set nbrBeds
void setNbrBeds(unsigned int &nbrBeds);
//set availableBeds
void setAvailableBeds(unsigned int &availableBeds);
//set nbrBeds
void setCostRespiteService(unsigned int &cosRespiteService);
//set nbrBeds
void setRespiteImpact(double &respiteImpact);
//set nbrBeds
void setDurationOfrespite(unsigned int &durationofRespite);


//

};

//Implementation du constructeur de class RespiteService initial avec un vector pour stocker toute les services
//Dans la méthode "ajouterServiceRepit" on construit à chaque fois un service de répit pour le stocker dans le vector, on appelle ce constructeur ci-dessous !
inline RespiteService::	RespiteService(InputData *inputData):
   _nbrServices (0) {this->_inputData = inputData;}

inline RespiteService::RespiteService(unsigned int id, string typeService, unsigned int nbrBeds, unsigned int availableBeds,
		unsigned int costRespiteService, double respiteImpact, unsigned int durationOfrespite):
   _id(id), _typeService(typeService), _nbrBeds(nbrBeds), _availableBeds(availableBeds), _costRespiteService(costRespiteService), _respiteImpact(respiteImpact), _durationOfrespite(durationOfrespite){}
//Constructeur par defaut
inline RespiteService::RespiteService():
		_nbrServices(0){}

} /* namespace mySpace */

#endif /* AGENT_BASED_SIMULATION_RESPITESERVICE_H_ */
