/*
 * InputData.h
 *
 *  Created on: 12 mai 2018
 *      Author: Oussama BATATA
 */

#ifndef INPUTDATA_H_
#define INPUTDATA_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace mySpace {

class InputData {
private:
    //-----Les données de la population de caregivers : ------------------------------------------------------
        unsigned int _nbrCluster;// nombre de cluster d'aidants
	    unsigned int _nbrStatePerCluster;// Nombre d'état à instancier pour chaque communauté(cluster) de notre population
	    unsigned int _nbrCaregiverPerCluster;//Nombre d'aidant pour chaque cluster
	    unsigned int _timeHorizon; // L'horizon temporelle de notre simulation et des états de la chaîne de Markov
	    vector< vector< vector< unsigned int > > > _burnoutCaregivers;// les données d'épuisement de l'aidants
	    vector< vector<  vector<  vector< float>  >  >  > _markovChain;//la chaîne des Markov pour l'épuisement des aidants
		//-------------------------------------------------------


	    // Les données pour construire un ensemble de services de répit plus un hôpital
	    unsigned int _nbrServices;//Nombre de services de répit + l'hôpital
        unsigned int _maxTimeRespite;//le temps maximum qu'un aidnat peux prendre pour un soin de répit


       // Les données de notre simulation
	    float _respiteFrequence;// La fréquence pour prendre le répit des aidants.
	    unsigned int _nbReplication;//Le nbr de réplications requis pour valider statistiquement notre simulation


	    //Les données de la chaîne de Markov analytitque
	    vector< vector < vector<float> > > _burnoutVector;// La répartition de la population sur les états d'épuisement
	    vector< vector < vector <float> > > _respiteVector;//La répartition de la population sur les état de répit

	    vector< vector < vector < vector < float>  > > > _burnoutMatrix;//La matrice de transition entre les étas d'épuisement
	    vector< vector < vector < vector < float>  > > > _respiteMatrix;//La matrice de transition entre les étas de répit


public:
    //Constructeur
	//InputData(unsigned int nbrCluster, unsigned int nbrStatePerCluster, unsigned int nbrCaregiverPerCluster, unsigned int timeHorizon, unsigned int nbrServices, double respiteFrequence);
	InputData();
	//virtual ~InputData();


	////--------------------------------------------------------------------------------------------------------------------------
	//	//------------------------Fonction principales----------------------------------------------------------------------

	void readData();
	void print();



	////--------------------------------------------------------------------------------------------------------------------------
	//	//------------------------Les gets----------------------------------------------------------------------

	    //get le nbCluster
	    unsigned int getNemberCluster();
	    //get le timeHorizon
	    unsigned int getTImeHorizon();
	    //get le nbStatePerCluster
	    unsigned int getNbrStatePerCluster();
	    //getle nbCaregiverPerCluster
	    unsigned int getNbrCaregiverPerCluster();
        //get le nbServices
	    unsigned int getNumberServices();
	    //get le maximum time in respite
	    unsigned int getmaxTimeInRespite();
        //get nbReplications
	    unsigned int getNbReplications();
	    //get Burnout de chaque  aidant à chaque instanct ...!
	    float getBurnoutByIdByTime(unsigned int &idCluster, unsigned int &id, unsigned &time);



	    //get burnoutVector
	    vector< vector < vector<float> > > getBurnoutVector();
	    //get respiteVector
	    vector< vector < vector<float> > > getRespiteVector();
	    //get frequenceRespite
	    float getRespiteFrequence();
	    //get byurnoutMatrix
	    vector< vector < vector < vector < float>  > > > getBurnoutMatrix();
	    //get respiteaMatrix
		vector< vector < vector < vector < float>  > > > getRespiteMatrix();



};



//inline InputData::InputData(unsigned int nbrCluster, unsigned int nbrStatePerCluster, unsigned int nbrCaregiverPerCluster, unsigned int timeHorizon, unsigned int nbrServices, double respiteFrequence):
//		_nbrCluster(nbrCluster), _nbrStatePerCluster(nbrStatePerCluster), _nbrCaregiverPerCluster(nbrCaregiverPerCluster), _timeHorizon(timeHorizon), _nbrServices(0),  _respiteFrequence(0){}

inline InputData::InputData():
		_nbrCluster(0), _nbrStatePerCluster(0), _nbrCaregiverPerCluster(0), _timeHorizon(0), _nbrServices(0),  _respiteFrequence(0), _nbReplication(0), _maxTimeRespite(0) {}
} /* namespace mySpace */

#endif /* INPUTDATA_H_ */
