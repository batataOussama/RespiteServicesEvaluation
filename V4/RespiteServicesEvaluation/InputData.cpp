/*
 * InputData.cpp
 *
 *  Created on: 12 mai 2018
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
#include "InputData.h"


using namespace std;

namespace mySpace {




//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------Fonctions principales------------------------------------------------------------------------


//-------------------------------------Debut----------------------------------------------------------------------

void InputData::readData(){


//Les données nécéssaire pour notre population d'aiadnt et des services de répit
	ifstream input("C:/Users/oussama.batata/eclipse-workspace/simulation/dataInput.txt");
	for(unsigned int i = 0; i < 8; i++){
        switch (i){
        case 0 : //Number cluster
    		input>>this->_nbrCluster;
    		break;
        case 1 : //Number Caregiver
        	input>>this->_nbrCaregiverPerCluster;
    		break;
        case 2 : //Number state of burnout
        	input>>this->_nbrStatePerCluster;
    		break;
        case 3 : //Time hiorizon
        	input>>this->_timeHorizon;
    		break;
        case 4 : //Number of respite services
        	input>>this->_nbrServices;
    		break;
        case 5 : //Number of respite services
        	input>>this->_respiteFrequence;
    		break;
        case 6 : //Number replication
        	input>>this->_nbReplication;
    		break;
        case 7 : //Durée maximum d'un soin de répit
        	input>>this->_maxTimeRespite;
    		break;
        }
	}

input.close();


//-------------------------
//Les données nécéssaire pour l'épuisement des aidants
ifstream input2("C:/Users/oussama.batata/eclipse-workspace/simulation/burnoutCaregivers.txt");
for (unsigned int i = 0; i < this->_nbrCluster; i++){
	vector< vector < unsigned int > > temp2;
	for (unsigned int j = 0; j < this->_nbrCaregiverPerCluster; j++ ){
		vector<unsigned int > temp1;
		for (unsigned int k = 0; k < this->_timeHorizon; k++){
			float val;
			input2>>val;
			temp1.push_back(int(val));
		}
		temp2.push_back(temp1);
	}
this->_burnoutCaregivers.push_back(temp2);
}
input2.close();


//-------------------------
//Les données nécéssaire pour la chaîne de Markov

ifstream input3("C:/Users/oussama.batata/eclipse-workspace/simulation/Markovmatrix.txt");
for (unsigned int i = 0; i < this->_nbrCluster; i++){
	vector< vector< vector< float > > > temp3;
	for (unsigned int j = 0; j < this-> _timeHorizon; j++){
		vector< vector< float > > temp2;
		for(unsigned int k = 0; k < this->_nbrStatePerCluster; k++){
			vector< float > temp1;
			for (unsigned int l = 0; l < this->_nbrStatePerCluster; l++){
				float val;
				input3>>val;
				temp1.push_back(val);
			}
		temp2.push_back(temp1);
		}
	temp3.push_back(temp2);
	}
this->_markovChain.push_back(temp3);
}
//-----------------------------



}

//-----------------------------------FIN ---------------------------------------------------------------------



//-------------------------------------Debut----------------------------------------------------------------------

void InputData::print(){
	cout<<"le nombre de clusters est : "<<this->_nbrCluster<<endl;
	cout<<"le d'aidants par cluster est : "<<this->_nbrCaregiverPerCluster<<endl;
	cout<<"le nombre d'états d'épuisement : "<<this->_nbrStatePerCluster<<endl;
	cout<<"Le temps horizon est : "<<this->_timeHorizon<<endl;
	cout<<"le nombre de services de répit : "<<this->_nbrServices<<endl;
	cout<<"la fréquence de répit est : "<<this->_respiteFrequence<<endl;
	cout<<"le nbr de répolications : "<<this->_nbReplication<<endl;
	cout<<"le temps max d'un soin de répit : "<<this->_maxTimeRespite<<endl;



cout<<"matrice de markov--------------"<<endl;

	for (unsigned int i = 0; i < _markovChain.size(); i++){
		for (unsigned int j = 0; j < _markovChain[i].size(); j++){
			for (unsigned int k = 0; k < _markovChain[i][j].size(); k++){
				for (unsigned int l = 0; l < _markovChain[i][j][k].size(); l++){
				cout << this->_markovChain[i][j][k][l] <<" ";
				}
				 cout<<endl;
			}
			cout<<"------------------Time----------------------"<<endl;
		}
		cout<<"############################Cluster#########################"<<endl;
	}

cout<<"matrice des données d'épuisement"<<endl;

for (unsigned int i = 0; i < this->_nbrCluster; i++){
	vector< vector < unsigned int > > temp2;
	for (unsigned int j = 0; j < this->_nbrCaregiverPerCluster; j++ ){
		vector<unsigned int > temp1;
		cout<<"Profile : "<<j+1<<endl;
		for (unsigned int k = 0; k < this->_timeHorizon; k++){
			 cout<<this->_burnoutCaregivers[i][j][k]<<" ";
		}
		cout<<endl;
	}
	cout<<"##########Cluster###########################"<<endl;
}

}
//-----------------------------------FIN ---------------------------------------------------------------------


//	//---------------------------------------Les gets ----------------------------------------------------------------------

//get le nbCluster
unsigned int InputData::getNemberCluster(){
	return this->_nbrCluster;
}

//get le timeHorizon
unsigned int InputData::getTImeHorizon(){
	return this->_timeHorizon;
}

//get le nbStatePerCluster
unsigned int InputData::getNbrStatePerCluster(){
	return this->_nbrStatePerCluster;
}

//getle nbCaregiverPerCluster
unsigned int InputData::getNbrCaregiverPerCluster(){
	return this->_nbrCaregiverPerCluster;
}

//get nbReplications
unsigned int InputData::getNbReplications(){
	return this->_nbReplication;
}

//get le nbServices
unsigned int InputData::getNumberServices(){
	return this->_nbrServices;
}

//get le maximum time in respite
unsigned int InputData::getmaxTimeInRespite(){
	return this->_maxTimeRespite;
}


//get burnout pour aidant par cluster, id, time
float InputData::getBurnoutByIdByTime(unsigned int &idCluster, unsigned int &id, unsigned &time){
	return this->_burnoutCaregivers[idCluster][id][time];
}


//get burnoutVector
vector< vector < vector<float> > > InputData::getBurnoutVector(){
	return this->_burnoutVector;
}

//get respiteVector
vector< vector < vector<float> > > InputData::getRespiteVector(){
	return this->_respiteVector;
}

//get frequenceRespite
float InputData::getRespiteFrequence(){
	return this->_respiteFrequence;
}

//get byurnoutMatrix
vector< vector < vector < vector < float>  > > > InputData::getBurnoutMatrix(){
	return this->_markovChain;
}

//get respiteaMatrix
vector< vector < vector < vector < float>  > > > InputData::getRespiteMatrix(){
	return this->_respiteMatrix;
}
//-----------------------------------------------------------------





} /* namespace mySpace */
