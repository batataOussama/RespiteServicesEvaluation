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



//-----------------------------Elements n�c�ssaire pour l'heristique de recherche local---------------------------------
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------


	//Lfr�quence de r�pit qu'on d�sire optimiser
	vector < vector <float> > _respiteFrequenceVector;//vecteur fr�quence r�pit qu'on veut optimiser
    float _evaluation; // l'�valuation de notre vecteur de fr�quence r�pit
    float _respiteRessourcesSolFinal; // les resspources r�pit de la solution final
    //-----------------------------------------------------------------------------------------

    //attribut de la solution voisine dans une structure de voisinage
    vector < vector <float> > _solutionVoisine;//solution dans une structure de voisinage
    float _evaluationSolVoisine; // �valuation de la solutiuon voisine 'nbr hospitalization'
    float _respiteRessourcesSolVoisine; // les ressources de r�pit consom� avec la solution voisine



    // attributs de la meillure solution sur une structure de voisinage
    vector < vector <float> > _bestSolutionVoisine;//Meilleure solution dnas une structure de voisinage
    float _evaluationBestSolution; // �valuation de la meilleure solutiuon par voisin,age  'nbr hospitalization'
    float _respiteRessourcesBestSolution; // les ressources de r�pit consom� avec la meilleure solution sur le voissinage
    //-------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------


//-------------------------contrainte de notre probl�me d'optimisation ----------------------------------------------
    //contraintes
    float _ressourcesConstraint; // Le nombre de ressources de r�pit � ne pas d�paser
    //-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------


	//Pointeurs
	InputData *_inputData; //pointeur vers la class inputDatat pour r�cuperer des don�es
	MarkovProcessAnalytic *_markovProcessAnalytic; //pointeur vers la class MarkovProcesAnalytic pour l'optimiser


public:

	//constructeur ;
	Optimization(InputData *inputData, MarkovProcessAnalytic *markovProcessAnalytic);

      void generateInitialRespiteFrequence(); //pour trouver la solution initial(fr�quence de r�pitinitial) de notre optim
      void evaluateRespiteFrequence(vector< vector<float> > &solToEvaluate, float &ressourcesSol, float&evalSol); // pour evaluer la solution (fr�quence de r�pit)
      void optimize(); //la fonction qui lance l'optimisation
      void localSearch();
      void perturberSolution();// pour s'extraire de l'optimum local  on perturbe la solution localement optimal....


};

inline Optimization::Optimization(InputData *inputData, MarkovProcessAnalytic *markovProcessAnalytic): _evaluation(0), _ressourcesConstraint(2000),
		_evaluationSolVoisine(0), _respiteRessourcesSolVoisine(0), _respiteRessourcesSolFinal(0), _evaluationBestSolution(0), _respiteRessourcesBestSolution(0) {this->_inputData = inputData; this->_markovProcessAnalytic = markovProcessAnalytic;}


} /* namespace mySpace */

#endif /* OPTIMIZATION_H_ */
