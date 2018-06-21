/*
 * caregiversPopulation.cpp
 *
 *  Created on: 24 mai 2018
 *      Author: oussama.batata
 */

#include "caregiversPopulation.h"
#include "Caregiver.h"

namespace mySpace {



double randomUniformm()
{
	return rand()/(double)RAND_MAX;
}

double randomUniformm(double a,double b)
{
	return (b-a)*randomUniformm()+a;
}


// Fonctions principales


//-----------------------------------debut ---------------------------------------------------------------------
void caregiversPopulation::generateInstance(){

	 this->_nbrCluster = this->_inputData->getNemberCluster();// nombre de cluster d'aidants
    this->_nbrStatePerCluster = this->_inputData->getNbrStatePerCluster();// Nombre d'état à instancier pour chaque communauté(cluster) de notre population
	 this->_timeHorizon = this->_inputData->getTImeHorizon(); // L'horizon temporelle de notre simulation et des états de la chaîne de Markov
     this->_markovChain = this->_inputData->getBurnoutMatrix();
	 for (unsigned int i = 0; i < this->_nbrCluster; i++){//Le nombre d'aidants par cluster
		 this->_nbrCaregiverPerCluster.push_back(this->_inputData->getNbrCaregiverPerCluster());
	}
}

void caregiversPopulation::printInstance(){
	cout<<"le nombre de clusters est : "<<this->_nbrCluster<<endl;
	cout<<"le d'aidants par cluster est : "<<endl;
	 for (unsigned int i = 0; i < this->_nbrCluster; i++){//Le nombre d'aidants par cluster
		 cout<<this->_nbrCaregiverPerCluster[i]<<" ";
		}
	 cout<<endl;

	cout<<"le nombre d'états d'épuisement : "<<this->_nbrStatePerCluster<<endl;
	//cout<<"le nombre de services de répit : "<<this->_nbrServices<<endl;
	cout<<"size is : "<<this->_markovChain[0][0][0].size()<<endl;
	cout<<"ma matrice -----------------------------------------"<<endl;
		for (unsigned int i = 0; i < this->_markovChain.size(); i++){
			for (unsigned int j = 0; j < this->_markovChain[i].size()-115; j++){
				for (unsigned int k = 0; k < this->_markovChain[i][j].size(); k++){
					for (unsigned int l = 0; l < this->_markovChain[i][j][k].size(); l++){
					     cout<<this->_markovChain[i][j][k][l]<< "   ";
					}
					cout<<endl;
				}
				cout<<"----------Time horizon-----------------------------------"<<endl;
			}
			cout<<"--------------------Cluster--------------------------------------------"<<endl;
		}
}
//-----------------------------------FIN ---------------------------------------------------------------------

//-------------------------------------Debut----------------------------------------------------------------------
void caregiversPopulation::addCaregiver(){
//		unsigned int id; //l'Id pour réferencier l'aidant (caregiver) et reconnaitre notre aidant (caregiver)
//		unsigned int idCluster; // Id de la communauté (cluster) auquel appartient le caregiver (aidant)
		float burnoutState; // Le niveau d'épuisement (burnout) de l'aidant (caregiver)
		bool inRespite; // Variable binaire, si elle vaut "0" alors l'aidant (caregiver) n'est pas en répit. Sinon, il est en répit
		unsigned int durationWithoutRespite; // Durée d'attente sans répit
		unsigned int respiteDuration; // Durrée des soins de répit si ils sont pris
		unsigned int idRespiteService; // L'Id du service de répit
		unsigned int timeInEmergency; // Le temps passé pour un aidant dans un état en urgence
		RespiteService *service = this->_respiteService; // pointeur vers la classe RespiteService

	for(unsigned int i=0; i < this->_nbrCluster; i++){
		vector<Caregiver> temp;
		for(unsigned int j=0; j < this->_nbrCaregiverPerCluster[i]; j++){
			unsigned int time = 0;
            burnoutState = this->_inputData->getBurnoutByIdByTime(i, j, time);
            inRespite = 0;//Initialisé sans répit
            durationWithoutRespite = 0;
            respiteDuration = 0;
            idRespiteService = 0;
            timeInEmergency = 0;
		    Caregiver car(j, i, burnoutState, inRespite, durationWithoutRespite, respiteDuration, idRespiteService,timeInEmergency,  service);
			temp.push_back(car);
		}
   this->_listeCaregiver.push_back(temp);
	}
}
//-----------------------------------FIN ---------------------------------------------------------------------

//-------------------------------------DEBUT---------------------------------------------------------------
Caregiver* caregiversPopulation::getCaregiverByTwoId(unsigned int &id, unsigned int &idCluster){

	unsigned int i=0;

	while(i< this->_listeCaregiver[idCluster].size())
	{

		if(this->_listeCaregiver[idCluster][i].getId() == id){
			return &this->_listeCaregiver[idCluster][i];
		}
		i++;
	}
	return this->_caregiver;
}
//-------------------------------------FIN -------------------------------------------------------------------------


//-------------------------------------DEBUT---------------------------------------------------------------
void caregiversPopulation::updateState(unsigned int &idCluster, unsigned int &id, unsigned int &timePeriode){
	unsigned int line = int(this->_listeCaregiver[idCluster][id].getBurnoutState()) -1;
   double valRand = randomUniformm(0,1);
//   cout<<"le burnout est :"<<line<<endl;
//   cout<<"ma valeur rand est :  "<<valRand<<endl;
   double s = 0;
   unsigned int i = 0;
//   cout<<"id cluster est : "<<idCluster<<endl;
//   cout<<"timePeriode est : "<<timePeriode<<endl;
//   cout<<"line est : "<<line<<endl;
//   cout<<"la linge ....."<<endl;
   while(i < this->_markovChain[idCluster][timePeriode][line].size()){
//	   cout<<"ici #####"<<endl;
	   s+=this->_markovChain[idCluster][timePeriode][line][i];
   	if(valRand <= s){
   		float val = float(i+1);
   		this->_listeCaregiver[idCluster][id].setBurnoutState(val);
//   		cout<<"le burnout a retourner est :"<<float(i+1)<<endl;
   		return;
   	}
   	i++;
   }
}
//-------------------------------------FIsN -------------------------------------------------------------------------



//--------------------------------DEBUT-----------------------------------------------------------------------
void caregiversPopulation::print(){
	if(this->_listeCaregiver.size()==0)
	{
		cout<<"The vector is empty, please add caregiver ! "<<endl;
		return;
	}
	cout<<"voici la liste des aidants (caregivers)!!:"<<endl;
	cout<<"!-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------!"<<endl;
	cout<<"!    Id Cluster   |    Id          |    burnoutState       |      inRespite     |       nbrState       |      attentrMax      |    duree attente réel  |     duree en répit    |    Oef du répit     !"<<endl;
	cout<<"!-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------!"<<endl;

  unsigned int i = 0;
  while(i<this->_listeCaregiver.size()){
	     for(unsigned int j=0; j < this->_listeCaregiver[i].size(); j++){
		cout<<"    ";
		cout<<this->_listeCaregiver[i][j].getIdCluster()+1<<"  ----------      ";
		cout<<this->_listeCaregiver[i][j].getId()+1<<"  ----------    ";
		cout<<this->_listeCaregiver[i][j].getBurnoutState()<<"       ----------      ";
		cout<<this->_listeCaregiver[i][j].getInRespite()<<"       ----------      ";
		cout<<endl;
  }
cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

  i++;
  }
}

//-----------------------------------FIN -------------------------------------------------------------------------




// Get les attributs de la population

unsigned int caregiversPopulation::getNbrCluser(){
	return this->_nbrCluster;
}

unsigned int caregiversPopulation::getNbrStatePerCluster(){
     return this->_nbrStatePerCluster;
}
unsigned int caregiversPopulation::getNbrCaregiverPerCluster(unsigned int &ind){
	return this->_nbrCaregiverPerCluster[ind];
}
unsigned int caregiversPopulation::getTimeHorizon(){
	return this->_timeHorizon;
}


// Get le nombre d'aidant en état d'urgence
unsigned int caregiversPopulation::getNumberOfCaregiverInEmergency(unsigned int &idCLuster){
	unsigned int nbCaregiverEmergency = 0;
	for (unsigned int i = 0; i < this->_listeCaregiver.size(); i ++){
		for (unsigned int j = 0; j < this->_listeCaregiver[i].size(); j ++){
             if (this->_listeCaregiver[i][j].getBurnoutState() > 3 && i == idCLuster){
                 nbCaregiverEmergency+=1;

             }
		}
	}
	return nbCaregiverEmergency;
}

//	//---------------------------------------Les sets ----------------------------------------------------------------------

//-----------------------------------------------------------------



} /* namespace mySpace */
