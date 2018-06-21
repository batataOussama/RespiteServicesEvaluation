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

vector< vector<  vector<  vector< float>  >  >  > markovChain;//la cha�ne des Markov pour l'�puisement des aidants
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










//-----------------------------------D�but -------------------------------------------------------------------------

void Caregiver::assignCaregiverTorespiteService(unsigned int &idService){
     cout<<"suis je en affectationn r�pit "<<endl;
	RespiteService *service;
	unsigned int id = idService;
	service  = this->_respiteService->getRespiteServiceById(id); //R�cuper le service de r�pit avec son id

	if (service->getAvailableBeds() > 0 ){
		this->_inRespite = 1;
		unsigned int nbLits = service->getAvailableBeds()-1;//get le nombre de lits disponible
        service->setAvailableBeds(nbLits); //d�cr�menter le nombre de lits disponibles
        unsigned int respiteDuration = service->getDurationOfrespite();
        this->_durationWithoutRespite = respiteDuration;

        cout<<"je suis dans la matison de r�pit ......"<<endl;
	}


}

//-----------------------------------FIN -------------------------------------------------------------------------

//-----------------------------------D�but -------------------------------------------------------------------------

void Caregiver::leaveRespiteService(){


	unsigned int idService = this->_idRespiteService;//R�cupr�rer l'id du service de r�pit que l'aidant va quitter
	RespiteService *service; //instancier un pointeur ver la class RespiteService
	service = this->_respiteService->getRespiteServiceById(idService);// Voia la service de r�pit que l'aidant va quitter
	//------------Remettre � jour le nombre de lits
	unsigned int nbrBeds = service->getAvailableBeds() +1;
	service->setAvailableBeds(nbrBeds);

   //---------------------------------------------------------------

	//---------------------------Impact du servide de r�pit sur l'�tat d'�pusiement de l'aidant
	double impact = service->getRespiteImpact();
	this->_burnoutState-=impact; // Voila l'impact du service de r�pit en valeur rajout� sur l'�puisement de l'aidant
	this->_burnoutState = round(this->_burnoutState);
	    //r�gulation du niveau d'�puisement
	     if(this->_burnoutState < 0){
	    	 this->_burnoutState = 0;
	     }
	//---------------------------------------------------------------------------------------------

	//quiter le service de r�pit passer � l'�tat sans r�pit
	this->_inRespite = 0;
}

//-----------------------------------FIN -------------------------------------------------------------------------





//-----------------------------------D�but -------------------------------------------------------------------------

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
