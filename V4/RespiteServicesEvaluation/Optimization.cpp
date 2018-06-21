/*
 * Optimization.cpp
 *
 *  Created on: 8 juin 2018
 *      Author: oussama.batata
 */


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


#include "Optimization.h"

namespace mySpace {



float currentEvaluation = 0;
float respiteRessources = 0;

double randomUniformOpt()
{
	return rand()/(double)RAND_MAX;
}

double randomUniformOpt(double a,double b)
{
	return (b-a)*randomUniformOpt()+a;
}



//-----------------------------------------------------Debut----------------------------------

void Optimization::generateInitialRespiteFrequence(){


	for(unsigned int j = 0; j < this->_inputData->getNemberCluster(); j++){
		vector<float>temp1;
		for(unsigned int k = 0; k < this->_inputData->getNbrStatePerCluster(); k++){
            temp1.push_back(float(0)/float(this->_inputData->getmaxTimeInRespite()*(k+1)));
		}
		this->_respiteFrequenceVector.push_back(temp1);
	}

}

//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------
void Optimization::evaluateRespiteFrequence(vector< vector<float> > &solToEvaluate, float &ressourcesSol, float &evalSol){

	MarkovProcessAnalytic markovProcessAnalytic(this->_inputData, solToEvaluate);

    bool valChoose = 0;
	 cout<<"je suis ici dans l'évalulation"<<endl;
	 for (unsigned int i = 0; i < solToEvaluate.size(); i++){
		 for(unsigned int j = 0; j < solToEvaluate[i].size(); j++){

			 cout<<solToEvaluate[i][j]<<" | ";
		 }
		 cout<<"--Cluster---";
	 }
	 cout<<endl;
	    //markovProcessAnalytic.printInstance();
    markovProcessAnalytic.generateInstance(valChoose);

    //markovProcessAnalytic.printInstance();
    markovProcessAnalytic.stationnaryPolicy();
    //markovProcessAnalytic.printInstance();
    evalSol = markovProcessAnalytic.getNbHospitalization();
    ressourcesSol = markovProcessAnalytic.getRespiteRessources();

//    cout<<"nbHospitalization : "<<evalSol<<endl;
//    cout<<"nbHospitalization en aidants est : "<<evalSol*this->_inputData->getNemberCluster()*this->_inputData->getNbrStatePerCluster()<<endl;
//    cout<<"nbRespiteRessources : "<<ressourcesSol<<endl;
//    cout<<"nbRespiteRessources en aidants est : "<<ressourcesSol*this->_evaluation*this->_inputData->getNemberCluster()*this->_inputData->getNbrStatePerCluster()<<endl;
}
//-----------------------------------------------------Fin----------------------------------



//-----------------------------------------------------Debut----------------------------------

void Optimization::localSearch(){


	this->_solutionVoisine = this->_respiteFrequenceVector;
    cout<<"###############################"<<endl;
	cout<<"itération N   :   "<<0<<endl;
	cout<<"----------solution initial"<<endl;
   for(unsigned int i = 0; i < this->_respiteFrequenceVector.size(); i++){
	   for(unsigned int j = 0; j < this->_respiteFrequenceVector[i].size(); j++){
		   cout<<this->_respiteFrequenceVector[i][j]<<" "<<" | ";
	   }
	   cout<<"##########";
   }
   cout<<"###############################"<<endl;


	for(unsigned int i = 0; i < this->_inputData->getNemberCluster(); i++){

		for(unsigned int j = 0; j < this->_inputData->getNbrStatePerCluster()-1; j++){
//			if (_solutionVoisine[j][i] > 0){
////				cout<<"avant d'appliquer structure de voisinnage : " <<_solutionVoisine[j][i]<<endl;
//			}
            this->_solutionVoisine[i][j] += (float(0.25)/float(this->_inputData->getmaxTimeInRespite()*(i+1)));
//			if (_solutionVoisine[j][i] > 0){
//				cout<<"apres avoir appliquer structure de voisinnage : " <<_solutionVoisine[j][i]<<endl;
//			}
			this->evaluateRespiteFrequence(this->_solutionVoisine, this->_respiteRessourcesSolVoisine,this->_evaluationSolVoisine);
			cout<<"evaluation de cette sol est : "<<this->_evaluationSolVoisine<<endl;
			cout<<"contraintes ressources est : "<<this->_respiteRessourcesSolVoisine<<endl;
			cout<<"###############################"<<endl;
	        if (this->_evaluationSolVoisine < this->_evaluation && this->_respiteRessourcesSolVoisine < this->_ressourcesConstraint){
	        	this->_bestSolutionVoisine = this->_solutionVoisine;
	        	this->_evaluation = this->_evaluationSolVoisine;
	        	this->_respiteRessourcesSolFinal = this->_respiteRessourcesSolVoisine;

	        }
	        this->_solutionVoisine = this->_respiteFrequenceVector;


		}


	    cout<<"###############################"<<endl;
		cout<<"itération N   :   "<<i+1<<endl;
		cout<<"----------solution voisine"<<i+1<<endl;
//	   for(unsigned int i = 0; i < this->_respiteFrequenceVector.size(); i++){
//		   for(unsigned int j = 0; j < this->_respiteFrequenceVector[i].size(); j++){
//			   cout<<this->_solutionVoisine[i][j]<<" "<<" | ";
//		   }
//		   cout<<endl;
//	   }




	}

	if (this->_bestSolutionVoisine.size() != 0){
		this->_respiteFrequenceVector = this->_bestSolutionVoisine;
	}


    cout<<"###############################"<<endl;
	cout<<"----------solution optimum "<<endl;
	cout<<"la taile de ma solution est la suivante"<<this->_respiteFrequenceVector.size()<<endl;
   for(unsigned int i = 0; i < this->_respiteFrequenceVector.size(); i++){
	   for(unsigned int j = 0; j < this->_respiteFrequenceVector[i].size(); j++){
		   cout<<this->_respiteFrequenceVector[i][j]<<" "<<" | ";
	   }
	   cout<<"###";
   }
   cout<<endl;
   cout<<"###############################"<<endl;
cout<<"Ma solution finale est : "<<this->_evaluation<<endl;
cout<<"les ressources finaux sont "<<this->_respiteRessourcesSolFinal<<endl;

}

//-----------------------------------------------------Fin----------------------------------


//-----------------------------------------------------Debut----------------------------------
void Optimization::perturberSolution(){


}

//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------

void Optimization::optimize(){

    cout<<"voila la contrainte répit"<<this->_ressourcesConstraint<<endl;
	this->generateInitialRespiteFrequence();
	this->evaluateRespiteFrequence(this->_respiteFrequenceVector, this->_respiteRessourcesSolFinal, this->_evaluation);
    float currentEvaluation = this->_evaluation;
	cout<<"les ressources de répit sont : "<<this->_respiteRessourcesSolFinal<<endl;
	unsigned int i = 0;

while(i < 50){
	cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
	this->localSearch();
    if(currentEvaluation < this->_evaluation){
    	cout<<"perturbation"<<endl;
    }
    else{
    	currentEvaluation = this->_evaluation;
    }
    cout<<"Fin de Itération-------------------------------- : "<<i+1<<endl;
	i++;
}


//	for(unsigned int i = 0; i < this->_respiteFrequenceVector.size(); i++){
//
//		for(unsigned int j = 0; j < this->_respiteFrequenceVector[i]; j++){
//
//
//		}
//	}

}

//-----------------------------------------------------Fin----------------------------------



} /* namespace mySpace */
