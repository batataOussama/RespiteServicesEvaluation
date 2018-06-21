/*
 * Caregiver.h
 *
 *  Created on: 6 avr. 2017
 *      Author: Oussama BATATA
 */

#ifndef SIMULATION_CAREGIVER_H_
#define SIMULATION_CAREGIVER_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "RespiteService.h"
#include "InputData.h"



using namespace std;

namespace mySpace {

class Caregiver {

private:


    //----- Population de caregivers: ------------------------------------------------------
        unsigned int _nbrCluster;// nombre de cluster d'aidants
	    unsigned int _nbrStatePerCluster;// Nombre d'�tat � instancier pour chaque communaut�(cluster) de notre population
	    vector<unsigned int> _nbrCaregiverPerCluster;//Nombre d'aidant pour chaque cluster
	    unsigned int _timeHorizon; // L'horizon temporelle de notre simulation et des �tats de la cha�ne de Markov
	    //vector< vector<  vector<  vector< float>  >  >  > _markovChain;//la cha�ne des Markov pour l'�puisement des aidants
		//-------------------------------------------------------

    //----- caregiver: ------------------------------------------------------
	    unsigned int _id; //l'Id pour r�ferencier l'aidant (caregiver) et reconnaitre notre aidant (caregiver)
	    unsigned int _idCluster; // Id de la communaut� (cluster) auquel appartient le caregiver (aidant)
		float _burnoutState; // Le niveau d'�puisement (burnout) de l'aidant (caregiver)
		bool _inRespite; // Variable binaire, si elle vaut "0" alors l'aidant (caregiver) n'est pas en r�pit. Sinon, il est en r�pit
		unsigned int _durationWithoutRespite; // Dur�e d'attente sans r�pit
		unsigned int _respiteDuration; // Durr�e des soins de r�pit si ils sont pris
		unsigned int _idRespiteService; // L'Id du service de r�pit
		unsigned int _timeInEmergency;//Le temps pass� pour un aidant en urgence (cette information est n�c�ssaire pour notre KPI)
	//-------------------------------------------------------

  //------------Pointeurs vers d'autres classes
        RespiteService *_respiteService;//Un pointeur vers la classe RespiteService pour gerer l'affectation.
        InputData * _inputData;
public:
    // Constructeur
		// constructeur N_1 : contenant le vectoor o� on stockera la population
	Caregiver(RespiteService *respiteService, InputData *inputData);
	   //2.1 constructeur N_2 : chaque entit�; aidant (caregiver) ajouter dans le vector contenant la population est initialis� par ce constructeur
	Caregiver(unsigned int id, unsigned int idCluster, float burnoutState,
			bool inRespite, unsigned int durationWithoutRespite, unsigned int respiteDuration, unsigned int idRespiteService, unsigned int timeInEmergency, RespiteService *respiteService);
	Caregiver();
////--------------------------------------------------------------------------------------------------------------------------
//	//------------------------Fonction principales----------------------------------------------------------------------


    //Generate MakovMatrix
    void generateMarkovMatrix();

    //Print MakovMatrix
    void printMatrkovMatrix();


    //Assigner un aidant dans un service de r�pit
    void assignCaregiverTorespiteService(unsigned int &idService);

    //Quiter le sirvice de r�pit
    void leaveRespiteService();

    //Update time in emergency
    void updateTimeInEmergency();

   //------------------------
    //Remplir la r�partition de la population sur les niveaux d"�puisement
     void constructRepartitionPopulation();

   //Print la r�partition de la population sur les niveaux d"�puisement
    void printRepartitionPopulation();

    //Sauver en CSV la r�partition de la population sur les niveaux d"�puisement
     void saveRepartitionPopulation();

//---------------------------------
//	//---------------------------------------Les gets ----------------------------------------------------------------------





// Get id
	unsigned int getId();
// Get IdCluster
	unsigned int getIdCluster();
// Get burnoutState
	float getBurnoutState();
// Get inRespite
	bool getInRespite();
// Get durationWithoutRespite
	unsigned int getDurationWithoutRespite();
// Get respiteDuration
	unsigned int getRespiteDUration();
// Get idRespiteService
	unsigned int getIdRespiteService();
// Get TimeInEmergency
	unsigned int getTimeInEmergency();



	//	//---------------------------------------Les sets ----------------------------------------------------------------------

	// Set id
		void seId(unsigned int &id);
	// Set IdCluster
		void setIdCluster(unsigned int &idCluster);
	// Set burnoutState
		void setBurnoutState(float &burnoutState);
	// Set inRespite
		void setInRespite(unsigned int &inRespite);
	// Set durationWithoutRespite
		void setDurationWithoutRespite(unsigned int &durationWithoutRespite);
	// Set respiteDuration
		void setRespiteDUration(unsigned int &respiteDuration);
	// Set idRespiteService
		void setIdRespiteService(unsigned int &idRespiteService);
	// Set timeInEmergency
		void setTimeInEmergency(unsigned int &timeInEmergency);


};

//Implementation du constructeur de class Caregiver initial avec un vector pour stocker toute la population des aidants (caregiver)
inline Caregiver::Caregiver(RespiteService *respiteService,  InputData *inputData):
	_nbrCluster(0), _nbrStatePerCluster(0), _timeHorizon(0) {this->_respiteService = respiteService;this->_inputData = inputData;}

//Dans la m�thode "ajouteraidant" on construit � chaque fois un adiant (caregiver) pour le stocker dans le vector, on appelle ce constructeur ci-dessous !
inline Caregiver::Caregiver(unsigned int id, unsigned int idCluster, float burnoutState,
		bool inRespite,  unsigned int durationWithoutRespite, unsigned int respiteDuration, unsigned int idRespiteService, unsigned int timeInEmergency, RespiteService *respiteService):
		_id(id), _idCluster(idCluster), _burnoutState(burnoutState), _inRespite(inRespite),_durationWithoutRespite(durationWithoutRespite), _respiteDuration(respiteDuration), _idRespiteService(idRespiteService), _timeInEmergency(timeInEmergency) {this->_respiteService = respiteService;}

inline Caregiver::Caregiver():
	_id(0), _idCluster(0),_burnoutState(0), _inRespite(0),_durationWithoutRespite(0), _respiteDuration(0), _idRespiteService(0) {}

} /* namespace mySpace */

#endif /* AGENT_BASED_SIMULATION_CAREGIVER_H_ */
