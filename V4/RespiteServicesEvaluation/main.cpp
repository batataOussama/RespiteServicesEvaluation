/*
 * main.cpp
 *
 *  Created on: 31 mars 2018
 *      Author: Oussama BATATA
 */



#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include<vector>
#include <string>
#include<map>
#include "InputData.h"
#include "caregiversPopulation.h"
#include "Caregiver.h"
#include "RespiteService.h"
#include "Simulation.h"
#include "MarkovProcessAnalytic.h"
#include "Optimization.h"


using namespace std;
using namespace mySpace;

void startSimulation(){


	InputData inputData;
	inputData.readData();
//	inputData.print();

	//-----RespiteServiceClass------------
	RespiteService resp(&inputData);
	resp.generateInstance();
    resp.addRespiteService();
    //resp.print();

    Caregiver caregiver;


    caregiversPopulation population(&caregiver, &resp, &inputData);
    population.generateInstance();
    //population.printInstance();
    population.addCaregiver();
    //population.print();

    cout<<"je vais checker....."<<endl;

    //-------SimulationClass-------------------------------
//    Simulation simulation(&population,&caregiver, &resp, &inputData);
//    simulation.generateInstance();
//    simulation.replicate();
//    simulation.saveResults();
//    population.printInstance();
//    //vector<unsigned int> table = simulation.simulate();

    //------------Markov process

    cout<<"je suis la ----"<<endl;
    MarkovProcessAnalytic markovProcess(&inputData);
    bool valChoose = 1;
    markovProcess.generateInstance(valChoose);
   // markovProcess.printInstance();
//    //markovProcess.checkMarkovMatrix();
////    markovProcess.updateBurnoutVector();
////    markovProcess.updateRespiteVector();
//    markovProcess.stationnaryPolicy();
//    markovProcess.printInstance();
//
//cout<<"voila le calcul du nombre d'hospitalisations"<<endl;
//    float s = markovProcess.getRespiteRessources();
//    cout<<"s : "<<s<<endl;
//    markovProcess.getKpiResults();



    //-------------------------------------------
//
    Optimization optimization(&inputData, &markovProcess);
    optimization.optimize();
//    optimization.generateInitialRespiteFrequence();
//    optimization.evaluateRespiteFrequence();

}

int main() {

cout<<"Hello word"<<endl;

	startSimulation();


  	return 0;

}






