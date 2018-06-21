/*
 * Simulation.cpp
 *
 *  Created on: 1 avr. 2018
 *      Author: Oussama BATATA
 */






#include<ctime>

#include <algorithm>    // std::random_shuffle
#include <cstdlib>

#include "Simulation.h"
#include "RespiteService.h"
#include "Caregiver.h"
#include "InputData.h"
#include "caregiversPopulation.h"

namespace  mySpace{



double randomUniform()
{
	return rand()/(double)RAND_MAX;
}

double randomUniform(double a,double b)
{
	return (b-a)*randomUniform()+a;
}





//------------------Les Fonction principales ------------------------------------------------


//------------------------------------------------Debut-----------------------------------
void Simulation::generateInstance(){

	this->_timeSlots = this->_inputData->getTImeHorizon();
	this->_randParamRespite = this->_inputData->getRespiteFrequence();
	this->_nbReplication = this->_inputData->getNbReplications();

}
//------------------------------------------------Fin-----------------------------------

//------------------------------------------------Debut-----------------------------------
void Simulation::evaluateKpiInRealData( vector< vector<unsigned int> > &realkpi){

//    vector<unsigned int > caregiverPerCluster(this->_inputData->getNbrCaregiverPerCluster(), 0);
//    vector< unsigned int > tableOfDurationInEmergency(this->_inputData->getNemberCluster(), caregiverPerCluster);

    //vector< vector<unsigned int> > secondKpi = realkpi;
	for (unsigned int i = 0; i < this->_inputData->getNemberCluster(); i++){
		for (unsigned int j = 0; j < this->_population->getNbrCaregiverPerCluster(i); j++){
			for (unsigned int k = 0; k < this->_timeSlots; k++){
				 if (this->_inputData->getBurnoutByIdByTime(i, j, k) > 3){
                     realkpi[i][k]+=1;
				 }
			}
		}
	}

}
//------------------------------------------------Fin-----------------------------------






//------------------------------------------------Debut-----------------------------------
vector<vector<unsigned int > > Simulation::simulate(){


	//-----RespiteServiceClass------------
	RespiteService resp(this->_inputData);
	resp.generateInstance();
    resp.addRespiteService();
    //resp.print();

    Caregiver caregiver;


    caregiversPopulation population(&caregiver, &resp, this->_inputData);
    population.generateInstance();
    //population.printInstance();
    population.addCaregiver();
    //population.print();

  //-------------------------------------------------------------------

    cout<<"fin de mon inside simulation"<<endl;
    vector<unsigned int> kpiSimul(this->_timeSlots,0);//kpi par simulation
    vector< vector< unsigned int > > KpiSimulation(this->_inputData->getNemberCluster(), kpiSimul);


	for (unsigned int i = 0; i < this->_timeSlots-1; i++){
		//population.print();

		for (unsigned int j = 0; j < population.getNbrCluser(); j++){

			//-------------Kpi------------------
			//cout<<"prélever l indicateur de performance"<<endl;
			KpiSimulation[j][i] =  population.getNumberOfCaregiverInEmergency(j);
		   //-----------------KPI-----------------
			Caregiver *caregiver;//instancier un pointeur ver la classer cluster pour récuprer chaque adiant de la populaiton (de chaque cluster)
			//RespiteService *service;//instancier un pointeur vers la classer RespiteService pour assigner l'aidant le service de répit dans la suite

			for (unsigned int k = 0; k < population.getNbrCaregiverPerCluster(j); k++){
                 caregiver = population.getCaregiverByTwoId(k, j);// récupérer chaque aidant de chaque cluster

                 //Mettre à jour la duréee de l'aidant en urgence si cet aidant se trouve en état d'urgence
                 caregiver->updateTimeInEmergency();
                 //Situation de l'aidant en répit------------------------------------------
                 if (caregiver->getInRespite()){// SI l'aidant est en répit
                     if(caregiver->getRespiteDUration() == 0){// SI la durée de répit est finis
                    	 caregiver->leaveRespiteService();// alors l'aidant quitte le service de répit
                     }
                     else{// Si la durée n'est pas encore fini
                          unsigned int time = caregiver->getRespiteDUration();
                          time--;
                          caregiver->setRespiteDUration(time); // Remetre à jours la duré de répit
                     }
                 }//---------------------------------------------------------------------------

                 // Situation de l'aidant sant répit----------------------------------------------
                 else{// Si l'aidant n'est pas en répit

                	 // L'aidant qui n'est pas en répit; a chaque pas de temps a une chance de prendre du répit ou même hospitaliser son patient  si il est tres épuisé!!!
                	  //unsigned int id = caregiver->getId();
                      //this->randomRespiteAssignCaregiver(id, j, population);
                	 //-----------------------------------------------------------------

                       if(caregiver->getInRespite()== 0){
                           //Mettre à jout la durée de l'aidant sans répit---------

                      	 unsigned int time = caregiver->getDurationWithoutRespite();
                      	 time++;
                      	 caregiver->setDurationWithoutRespite(time);
                      	 //------------------------------------------------------

                      	  //Mettre à jours l'état de l'aidant au pas de temps actuel--------
                      	 population.updateState(j, k, i);
                      	 //-----------------------------------------------------------------
                       }

                 }
			}
		}

	}

//cout<<"ma simulationd donne ------"<<endl;
//for(unsigned int i = 0; i < KpiSimulation.size(); i++){
//	for(unsigned int j = 0; j < KpiSimulation[i].size(); j++){
//		cout<<KpiSimulation[i][j]<<" ";
//	}
//	cout<<endl;
//}

cout<<"ma simulationd donne ------"<<endl;

return KpiSimulation;

}


//-----------------------------------------------------------Fin-------------------------------------


//-----------------------------------------------------------Debut------------------------------------

void Simulation::replicate(){
	for (unsigned int i = 0; i < this->_nbReplication; i++){
         this->_results.push_back(this->simulate());
         cout<<"##########################################"<<endl;
         cout<<"##########################################"<<endl;
	}

	for (unsigned int i = 0; i < this->_results.size(); i++){
		for(unsigned int j = 0; j < this->_results[i].size(); j++){
			for(unsigned int k = 0; k < this->_results[i][j].size(); k++){
				cout<<this->_results[i][j][k]<<" ";
			}
			cout<<endl;
			cout<<"Cluster ----"<<endl;
		}

		cout<<"##########################################"<<endl;
		cout<<"##########################################"<<endl;
		cout<<"fin répolication-------------------"<<endl;
	}
	vector<unsigned int> kpiReal(this->_timeSlots, 0);// kpi des données réels
	vector< vector <unsigned int> > kpiRealData(this->_inputData->getNemberCluster(), kpiReal);
	this->evaluateKpiInRealData(kpiRealData);
		cout<<"la réalité ---------------"<<endl;

    for(unsigned int i = 0; i < kpiRealData.size(); i++){
		for (unsigned int j = 0; j < this->_timeSlots; j++){
			cout<<kpiRealData[i][j]<<" ";
		}
		cout<<endl;
    }
this->_results.push_back(kpiRealData);
		cout<<"verification"<<endl;
		cout<<"size in simulation : "<<this->_results.size()<<endl;
		cout<<"size in réalité : "<<kpiReal.size()<<endl;

}


//-----------------------------------------------------------Fin-------------------------------------


//-----------------------------------------------------------Debut------------------------------------

void Simulation::randomRespiteAssignCaregiver(unsigned int &idCaregiver, unsigned int &idCluster, caregiversPopulation &population){
	Caregiver *caregiver;
	caregiver = population.getCaregiverByTwoId(idCaregiver, idCluster);
	double randVal = randomUniform(0,1);

	if(float(randVal) <= this->_randParamRespite){// Si l'aidant peut prendre du répit alors :
   		randVal = randomUniform(1, this->_service->getNbrServcies());// on choisir un des services de répit pour affecter l'aidant ; on remarqhe qu'on commence de 1 pour ne pas compter l'hoptal (l'hopital est en position 0)
   		unsigned int ind = randVal;
   		caregiver->assignCaregiverTorespiteService(ind);//assigner l'aidant au service de répit id
	}
	else if(caregiver->getBurnoutState() == population.getNbrStatePerCluster()){// Si l'aidant ne reçoit pas de répit et dans un état avancé d'épuisement on l'affecte àl'hopital
		    unsigned int ind = 0;// prendre la position de l'hôpital
           // caregiver->assignCaregiverTorespiteService(ind);// l'hopital est en position 0
	}
}


//-----------------------------------------------------------Fin-------------------------------------



//-----------------------------------------------------------Debut------------------------------------
void Simulation::saveResults(){
	 string const monFichier("C:/Users/oussama.batata/eclipse-workspace/simulation/results.txt");
	 ofstream monflux(monFichier.c_str());

	 for(unsigned int i = 0; i < this->_results.size(); i++){
		 for(unsigned int j = 0; j < this->_results[i].size(); j++){
			 for(unsigned int k = 0; k < this->_results[i][j].size(); k++){
				 monflux<<this->_results[i][j][k]<<" ";
			 }
		 }
	 }

}

//-----------------------------------------------------------Fin-------------------------------------


//------------------Les gets ------------------------------------------------
   //get timeSlots
unsigned int Simulation::getTimeSlots(){
	return this->_timeSlots;
}
   //get randParamRespite
float Simulation::getRandParamRespite(){
	return this->_randParamRespite;
}



//------------------Les sets ------------------------------------------------
     //set timeSlots
void Simulation::setTimeSlots(unsigned int &timeSlots){
	this->_timeSlots = timeSlots;
}
     //set randParamRespite
void Simulation::setRandParamRespite(float &randParamRespite){
	this->_randParamRespite = randParamRespite;
}


}/* namespace mySpace */
