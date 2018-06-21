/*
 * Caregiver.cpp
 *
 *  Created on: 6 avr. 2017
 *      Author: Oussama BATATA
 */

#include <vector>
#include <stdlib.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <numeric>
#include <math.h>
#include <map>
#include "Caregiver.h"
using namespace std;
namespace mySpace {

vector< vector<  vector<  vector< float>  >  >  > markovChain;//la chaîne des Markov pour l'épuisement des aidants
vector< vector<Caregiver> > listeCaregiver;



vector< vector<unsigned int > > repartitionPopulationOversStates;

double randomUnifor()
{
	return rand()/(double)RAND_MAX;
}

double randomUnifor(double a,double b)
{
	return (b-a)*randomUnifor()+a;
}




//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------Fonctions principales------------------------------------------------------------------------










//-----------------------------------Début -------------------------------------------------------------------------

void Caregiver::assignCaregiverTorespiteService(unsigned int &idService){
     cout<<"suis je en affectationn répit "<<endl;
	RespiteService *service;
	unsigned int id = idService;
	service  = this->_respiteService->getRespiteServiceById(id); //Récuper le service de répit avec son id

	if (service->getAvailableBeds() > 0 ){
		this->_inRespite = 1;
		unsigned int nbLits = service->getAvailableBeds()-1;//get le nombre de lits disponible
        service->setAvailableBeds(nbLits); //décrémenter le nombre de lits disponibles
        unsigned int respiteDuration = service->getDurationOfrespite();
        this->_durationWithoutRespite = respiteDuration;

        cout<<"je suis dans la matison de répit ......"<<endl;
	}


}

//-----------------------------------FIN -------------------------------------------------------------------------

//-----------------------------------Début -------------------------------------------------------------------------

void Caregiver::leaveRespiteService(){


	unsigned int idService = this->_idRespiteService;//Récuprérer l'id du service de répit que l'aidant va quitter
	RespiteService *service; //instancier un pointeur ver la class RespiteService
	service = this->_respiteService->getRespiteServiceById(idService);// Voia la service de répit que l'aidant va quitter
	//------------Remettre à jour le nombre de lits
	unsigned int nbrBeds = service->getAvailableBeds() +1;
	service->setAvailableBeds(nbrBeds);

   //---------------------------------------------------------------

	//---------------------------Impact du servide de répit sur l'état d'épusiement de l'aidant
	double impact = service->getRespiteImpact();
	this->_burnoutState-=impact; // Voila l'impact du service de répit en valeur rajouté sur l'épuisement de l'aidant
	this->_burnoutState = round(this->_burnoutState);
	    //régulation du niveau d'épuisement
	     if(this->_burnoutState < 0){
	    	 this->_burnoutState = 0;
	     }
	//---------------------------------------------------------------------------------------------

	//quiter le service de répit passer à l'état sans répit
	this->_inRespite = 0;
}

//-----------------------------------FIN -------------------------------------------------------------------------





//-----------------------------------Début -------------------------------------------------------------------------

void Caregiver::updateTimeInEmergency(){
	if(this->_burnoutState > float(3)){
		this->_timeInEmergency++;
	}
}
//-----------------------------------FIN -------------------------------------------------------------------------



//-----------------------------------Debut -------------------------------------------------------------------------
//print different information over repartitiion population

void Caregiver::constructRepartitionPopulation(){
	for (unsigned int i = 0; i < this->_nbrCluster; i++){
		vector<unsigned int > temp(this->_nbrStatePerCluster, 0);
		for (unsigned int j = 0; j < this->_nbrCaregiverPerCluster[i]; j++){
			unsigned int state = listeCaregiver[i][j].getBurnoutState();
			 temp[state]++;
		}
		repartitionPopulationOversStates.push_back(temp);
	}
}


void Caregiver::printRepartitionPopulation(){
	for (unsigned int i =0; i < repartitionPopulationOversStates.size(); i++){
		for(unsigned int j = 0; j < repartitionPopulationOversStates[i].size(); j++){
			cout<<repartitionPopulationOversStates[i][j]<<"  ";
		}
		cout<<endl;
	}
}


void Caregiver::saveRepartitionPopulation(){

	 string const monFichier("C:/Users/Oussama BATATA/workspace/results.txt");
	 ofstream monflux(monFichier.c_str());

	 for(unsigned int i = 0; i < repartitionPopulationOversStates.size(); i++){
		 monflux<<"Cluster"<<i+1<<";   ";
		 for(unsigned int j = 0; j < repartitionPopulationOversStates[i].size(); j++){
			 monflux<<repartitionPopulationOversStates[i][j]<<" "<<";";
		 }
		 monflux<<endl;
	 }


}
//-----------------------------------FIN -------------------------------------------------------------------------

//	//---------------------------------------Les gets ----------------------------------------------------------------------




// Get id
unsigned int Caregiver::getId(){
	return this->_id;
}
// Get IdCluster
unsigned int Caregiver::getIdCluster(){
	return this->_idCluster;
}
// Get burnoutState
float Caregiver::getBurnoutState(){
	return this->_burnoutState;
}
// Get inRespite
bool Caregiver::getInRespite(){
	return this->_inRespite;
}
// Get durationWithoutRespite
unsigned int Caregiver::getDurationWithoutRespite(){
	return this->_durationWithoutRespite;
}
// Get respiteDuration
unsigned int Caregiver::getRespiteDUration(){
	return this->_respiteDuration;
}
// Get idRespiteService
unsigned int Caregiver::getIdRespiteService(){
	return this->_idRespiteService;
}
// Get TimeInEmergency
unsigned int Caregiver::getTimeInEmergency(){
	return this->_timeInEmergency;
}



	// Get id
void Caregiver::seId(unsigned int &id){
	this->_id = id;
}
	// Set IdCluster
void Caregiver::setIdCluster(unsigned int &idCluster){
	this->_idCluster = idCluster;
}
	// Set burnoutState
void Caregiver::setBurnoutState(float &burnoutState){
	this->_burnoutState = burnoutState;
}
	// Set inRespite
void Caregiver::setInRespite(unsigned int &inRespite){
	this->_inRespite = inRespite;
}
	// Set durationWithoutRespite
void Caregiver::setDurationWithoutRespite(unsigned int &durationWithoutRespite){
	this->_durationWithoutRespite = durationWithoutRespite;
}
	// Set respiteDuration
void Caregiver::setRespiteDUration(unsigned int &respiteDuration){
	this->_respiteDuration = respiteDuration;
}
	// Set idRespiteService
void Caregiver::setIdRespiteService(unsigned int &idRespiteService){
	this->_idRespiteService = idRespiteService;
}
// Set TimeInEmergency
void Caregiver::setTimeInEmergency(unsigned int &timeInEmergency){
	this->_timeInEmergency = timeInEmergency;
}

} /* namespace mySpace */
