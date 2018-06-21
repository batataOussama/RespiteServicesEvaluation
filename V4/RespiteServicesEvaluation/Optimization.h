/*
 * Optimization.h
 *
 *  Created on: 8 juin 2018
 *      Author: oussama.batata
 */

#ifndef OPTIMIZATION_H_
#define OPTIMIZATION_H_


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "InputData.h"
#include "Caregiver.h"
#include "caregiversPopulation.h"
#include "RespiteService.h"
#include "MarkovProcessAnalytic.h"


using namespace std;


namespace mySpace {

class Optimization {

private:



//-----------------------------Elements nécéssaire pour l'heristique de recherche local---------------------------------
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------


	//Lfréquence de répit qu'on désire optimiser
	vector < vector <float> > _respiteFrequenceVector;//vecteur fréquence répit qu'on veut optimiser
    float _evaluation; // l'évaluation de notre vecteur de fréquence répit
    float _respiteRessourcesSolFinal; // les resspources répit de la solution final
    //-----------------------------------------------------------------------------------------

    //attribut de la solution voisine dans une structure de voisinage
    vector < vector <float> > _solutionVoisine;//solution dans une structure de voisinage
    float _evaluationSolVoisine; // évaluation de la solutiuon voisine 'nbr hospitalization'
    float _respiteRessourcesSolVoisine; // les ressources de répit consomé avec la solution voisine



    // attributs de la meillure solution sur une structure de voisinage
    vector < vector <float> > _bestSolutionVoisine;//Meilleure solution dnas une structure de voisinage
    float _evaluationBestSolution; // évaluation de la meilleure solutiuon par voisin,age  'nbr hospitalization'
    float _respiteRessourcesBestSolution; // les ressources de répit consomé avec la meilleure solution sur le voissinage
    //-------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------


//-------------------------contrainte de notre problème d'optimisation ----------------------------------------------
    //contraintes
    float _ressourcesConstraint; // Le nombre de ressources de répit à ne pas dépaser
    //-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------


	//Pointeurs
	InputData *_inputData; //pointeur vers la class inputDatat pour récuperer des donées
	MarkovProcessAnalytic *_markovProcessAnalytic; //pointeur vers la class MarkovProcesAnalytic pour l'optimiser


public:

	//constructeur ;
	Optimization(InputData *inputData, MarkovProcessAnalytic *markovProcessAnalytic);

      void generateInitialRespiteFrequence(); //pour trouver la solution initial(fréquence de répitinitial) de notre optim
      void evaluateRespiteFrequence(vector< vector<float> > &solToEvaluate, float &ressourcesSol, float&evalSol); // pour evaluer la solution (fréquence de répit)
      void optimize(); //la fonction qui lance l'optimisation
      void localSearch();
      void perturberSolution();// pour s'extraire de l'optimum local  on perturbe la solution localement optimal....


};

inline Optimization::Optimization(InputData *inputData, MarkovProcessAnalytic *markovProcessAnalytic): _evaluation(0), _ressourcesConstraint(2000),
		_evaluationSolVoisine(0), _respiteRessourcesSolVoisine(0), _respiteRessourcesSolFinal(0), _evaluationBestSolution(0), _respiteRessourcesBestSolution(0) {this->_inputData = inputData; this->_markovProcessAnalytic = markovProcessAnalytic;}


} /* namespace mySpace */

#endif /* OPTIMIZATION_H_ */
