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
    //-----Les donn�es de la population de caregivers : ------------------------------------------------------
        unsigned int _nbrCluster;// nombre de cluster d'aidants
	    unsigned int _nbrStatePerCluster;// Nombre d'�tat � instancier pour chaque communaut�(cluster) de notre population
	    unsigned int _nbrCaregiverPerCluster;//Nombre d'aidant pour chaque cluster
	    unsigned int _timeHorizon; // L'horizon temporelle de notre simulation et des �tats de la cha�ne de Markov
	    vector< vector< vector< unsigned int > > > _burnoutCaregivers;// les donn�es d'�puisement de l'aidants
	    vector< vector<  vector<  vector< float>  >  >  > _markovChain;//la cha�ne des Markov pour l'�puisement des aidants
		//-------------------------------------------------------


	    // Les donn�es pour construire un ensemble de services de r�pit plus un h�pital
	    unsigned int _nbrServices;//Nombre de services de r�pit + l'h�pital
        unsigned int _maxTimeRespite;//le temps maximum qu'un aidnat peux prendre pour un soin de r�pit


       // Les donn�es de notre simulation
	    float _respiteFrequence;// La fr�quence pour prendre le r�pit des aidants.
	    unsigned int _nbReplication;//Le nbr de r�plications requis pour valider statistiquement notre simulation


	    //Les donn�es de la cha�ne de Markov analytitque
	    vector< vector < vector<float> > > _burnoutVector;// La r�partition de la population sur les �tats d'�puisement
	    vector< vector < vector <float> > > _respiteVector;//La r�partition de la population sur les �tat de r�pit

	    vector< vector < vector < vector < float>  > > > _burnoutMatrix;//La matrice de transition entre les �tas d'�puisement
	    vector< vector < vector < vector < float>  > > > _respiteMatrix;//La matrice de transition entre les �tas de r�pit


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
	    //get Burnout de chaque  aidant � chaque instanct ...!
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
