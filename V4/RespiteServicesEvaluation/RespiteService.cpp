/*
 * RespiteService.cpp
 *
 *  Created on: 6 avr. 2017
 *      Author: Oussama BATATA
 */

#include <vector>
#include <stdlib.h>
#include "RespiteService.h"
using namespace std;
namespace mySpace {

double randomUniform1()
{
	return rand()/(double)RAND_MAX;
}

double randomUniform1(double a,double b)
{
	return (b-a)*randomUniform1()+a;
}




vector<RespiteService> listeService;




////---------------------------------------------------------------------------------------------------------------------------------------------
////---------------------------------------------------------------------------------------------------------------------------------------------
////---------------------------------------------------------------------------------------------------------------------------------------------
////-----------------------------------------------------------Fonctions principales------------------------------------------------------------------------


//-------------------------------------Debut----------------------------------------------------------------------


void RespiteService::generateInstance(){
	this->_nbrServices = this->_inputData->getNumberServices();
}
//-------------------------------------FIn----------------------------------------------------------------

//-------------------------------------Debut----------------------------------------------------------------------
void RespiteService::addRespiteService(){

	//unsigned int id; // l'ID du service.
	string typeService; // Le type de service de répit.
	unsigned int nbrBeds; // Nombre de lis dont dispose l'etablissement.
	unsigned int availableBeds; // Nombre de lits disponibles
	unsigned int costRespiteService;// Coût d'une nuit l'etablissement.
    double respiteImpact;//L'importance accordé au service dans le rétablissement de l'aidant(caregiver) après la visite de ce service en question;
    unsigned int durationOfrespite; // la durrée de répit affecté par un service à un aidant

   for(unsigned int i=0;i<this->_nbrServices;i++)
   {
        if (i == 0){
        	typeService = "Hôpital";
        	nbrBeds = 5000;
        	availableBeds = nbrBeds;
        	costRespiteService = 2000;
        	respiteImpact = randomUniform1(1,5);
        	durationOfrespite = randomUniform1(7,21);

        }else{
        	typeService = "Service Répit";
        	nbrBeds = 50;
        	availableBeds = nbrBeds;
        	costRespiteService = 360;
        	respiteImpact = randomUniform1(1,5);
        	durationOfrespite = randomUniform1(1,7);
        }
		//Création du nouveau aidant(caregiver) saisi par l'tilisateur.
        RespiteService service(i, typeService, nbrBeds, availableBeds, costRespiteService, respiteImpact, durationOfrespite);

		//Ajouter l'aidant (caregiver) dans la liste ou Vector initialiement définit
		listeService.push_back(service);

   }
}
//-----------------------------------FIN -------------------------------------------------------------------------

//-------------------------------------Debut---------------------------------------------------------------
RespiteService* RespiteService::getRespiteServiceById(unsigned int &id){
	unsigned int i=0;

	while(i<listeService.size())
	{
		if(listeService[i]._id == id){
			return &listeService[i];
		}
		i++;
	}

	return this;
}
//-----------------------------------FIN -------------------------------------------------------------------------


//-------------------------------------Debut---------------------------------------------------------------
void RespiteService::print(){

if(listeService.size() == 0)
{
	cout<<"the vector is empty, please add service of respite !"<<endl;
	return;
}
cout<<"This is the liste of services!!:"<<endl;
	cout<<"!-------------------------------------------------------------------------------------------------------------------------------------!"<<endl;
	cout<<"!  Id        |    Type Service               |  availableBeds   !"<<endl;
	cout<<"!-------------------------------------------------------------------------------------------------------------------------------------!"<<endl;
unsigned  int i=0;
while( i <listeService.size()){
	cout<<"     ";
	cout<<listeService[i]._id+1 <<"-------------------"	;
	cout<<listeService[i]._typeService <<"-----------------"	;
    cout<<listeService[i]._availableBeds<<"-------------"	;
    cout<<endl;
    i++;
}


}
//-------------------------------FIN -------------------------------------------------------------------------



//--------------------------------Les gets ---------------------------------------------------------

// get les attributs de l'ensemble des services
//get NbrServices
unsigned int RespiteService::getNbrServcies(){
	return this->_nbrServices;
}

unsigned int RespiteService::getNbrBeds(){
   return this->_nbrBeds;
}

unsigned int RespiteService::getAvailableBeds(){
	return this->_availableBeds;
}

unsigned int RespiteService::getCostRespiteService(){
    return this->_costRespiteService;
}

double RespiteService::getRespiteImpact(){
	this->_respiteImpact = randomUniform1(1,2);
	return this->_respiteImpact;
}

unsigned int RespiteService::getDurationOfrespite(){
	this->_durationOfrespite = randomUniform1(7,21);
	return this->_durationOfrespite;
}

string RespiteService::getTypeRespite(){
	return this->_typeService;
}

//------------------Les sets ------------------------------------------------



// set les attributs de l'ensemble des services
//set NbrServices
void RespiteService::setNbrServcies(unsigned int &nbServices){
	this->_nbrServices = nbServices;
}

//set nbrBeds
void RespiteService::setNbrBeds(unsigned int &nbrBeds){
	this->_nbrBeds = nbrBeds;
}

//set availableBeds
void RespiteService::setAvailableBeds(unsigned int &availableBeds){
	this->_availableBeds = availableBeds;
}

//set cost
void RespiteService::setCostRespiteService(unsigned int &cosRespiteService){
	this->_costRespiteService = cosRespiteService;
}

//set impact
void RespiteService::setRespiteImpact(double &respiteImpact){
	this->_respiteImpact = respiteImpact;
}

//set nbrBeds
void RespiteService::setDurationOfrespite(unsigned int &durationofRespite){
	this->_durationOfrespite = durationofRespite;
}


//
} /* namespace mySpace */
