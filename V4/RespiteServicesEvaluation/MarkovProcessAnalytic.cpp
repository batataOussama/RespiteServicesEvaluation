/*
 * MarkovProcessAnalytic.cpp
 *
 *  Created on: 2 avr. 2018
 *      Author: Oussama BATATA
 */

#include "MarkovProcessAnalytic.h"


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

using namespace std;

namespace mySpace {


//je vais créer un vecteur pour stocker les valeurs mise à jours de l'épuisement des aiadnts

vector< vector < vector <float> > > burnoutTemp;
vector< vector< vector <float> > > respiteTemp;
//-----------------------------------------------------Fonction principales----------------------------------

//-----------------------------------------------------Debut----------------------------------

void MarkovProcessAnalytic::generateInstance(bool &valchoose){

// dans cette fonction on fait que récupérer les données importé de la classe inputData .....


	this->_timeMaxRespite = this->_inputData->getmaxTimeInRespite();
	this->_burnoutMatrix = this->_inputData->getBurnoutMatrix();
	this->_respiteFrequence = this->_inputData->getRespiteFrequence();



	   if(valchoose){
		   this->generateVectorRespiteFrequence();
		   cout<<"je générer le vector fréquence de répit"<<endl;
	   }

	//if(this->_respiteFrequence > 0){
		this->generateRespiteMatrix();
		this->adaptBurnoutMatrix();
	//}
   this->genrateBurnoutRepartition();
   this->generateRespiteRepartition();
}
//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------

void MarkovProcessAnalytic::adaptBurnoutMatrix(){
///La matrice des probailité de transition est importé avec les probailité de transition entre les états d'épuisement
	// Aprés la constructuion de la matriuce de état de répit pn doit merger les deux matrices
	// De ce fait on doit ajuter les probalutés et adapter la matrice des états de birbout de manière ; proba état burnout + proba état répit = 1
	// C'est les régles stochatique de la matrice de markàov


	for (unsigned int i = 0; i < this->_burnoutMatrix.size(); i++){
		for(unsigned int j = 0; j < this->_burnoutMatrix[i].size(); j++){
			for(unsigned int k =0; k < this->_burnoutMatrix[i][j].size(); k++){
				for(unsigned int l = 0; l < this->_burnoutMatrix[i][j][k].size(); l++){

					if(j == this->_burnoutMatrix[i].size() -1){
						this->_burnoutMatrix[i][j][k][l] = 0;// au denier pas de temps tout les aidant préne du répit et les prpobas répit + 1 ==> proba burnout = 0
					}
					else{
						this->_burnoutMatrix[i][j][k][l]-= this->_burnoutMatrix[i][j][k][l]*this->_respiteFrequenceVector[i][k]*(this->_timeMaxRespite*(k+1));//on réduit les probas burnnout au pourcentage pour équilibrer avec proba répit
					}
				}
			}
		}
	}
}
//-----------------------------------------------------Fin----------------------------------


//-----------------------------------------------------Debut----------------------------------

void MarkovProcessAnalytic::generateRespiteMatrix(){

	// on constuit ma ùatrice de répit à partir du vectuer contennat tout les fréquences de répit pour les aidants

//	cout<<"je rentre à la matrice de répit en création"<<endl;
	for (unsigned int i = 0; i < this->_burnoutMatrix.size(); i++){// boucle sur les clusters
//		cout<<"boucler sur cluster"<<endl;
		vector< vector < vector<float> > >temp; //vector temporaire pour stocker les donneés
		for(unsigned int j = 0; j < this->_burnoutMatrix[i].size(); j++){//boucle sur le temps
//			cout<<"biucler sur les pas de temps"<<endl;
			vector < vector<float> >temp1; //un autre vector temp pour stocker les données
			for(unsigned int k = 0; k < this->_burnoutMatrix[i][j].size(); k++){//boucle sur le nbr d'états dépuisement
//				cout<<"boucler sur les états d'épuisement"<<endl;
				vector<float> temp2; // le dernier vector enfin
				for(unsigned int b = 0; b <this->_timeMaxRespite; b++){
					for(unsigned int l = 0; l < this->_burnoutMatrix[i][j].size(); l++){
						if (l <= k){
							if (j == this->_burnoutMatrix[i].size()-1){
								temp2.push_back(float(1)/float((k+1)*(this->_timeMaxRespite)));
							}
							else{
//								cout<<"je beugue ici ???"<<endl;
//								cout<<"le répit à assigner"<<this->_respiteFrequenceVector[i][k]<<endl;
								temp2.push_back(this->_respiteFrequenceVector[i][k]);
							}
						  }

					}
				}
               temp1.push_back(temp2);
			}
			temp.push_back(temp1);
		}
     this->_respiteMatrix.push_back(temp);
	}
}


//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------

void MarkovProcessAnalytic::printInstance(){
    //fonction pour verifier mon instance


	cout<<"le temps max d'un soin de répit : "<<this->_timeMaxRespite<<endl;
	cout<<"la fréquence de répit est : "<<this->_respiteFrequence<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
   cout<<"la matrice du burnout est la suivante : "<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
	for (unsigned int i = 0; i < this->_burnoutMatrix.size(); i++){// boucle sur les clusters
		for(unsigned int j = this->_burnoutMatrix[i].size()-3; j < this->_burnoutMatrix[i].size(); j++){//boucle sur le temps
			for(unsigned int k = 0; k < this->_burnoutMatrix[i][j].size(); k++){//boucle sur le nbr d'états dépuisement
				for(unsigned int l = 0; l < this->_burnoutMatrix[i][j][k].size(); l++){
                   cout<<this->_burnoutMatrix[i][j][k][l]<<" ";
				    }
				cout<<endl;
				}
		       cout<<"-----------------time-------------time"<<endl;
			}
		cout<<" ######################  cluster ####################################"<<endl;
		}


	   cout<<"------------------------------------------------------------------------"<<endl;
	   cout<<"la matrice du répit est la suivante : "<<endl;
	   cout<<"------------------------------------------------------------------------"<<endl;
	for (unsigned int i = 0; i < this->_respiteMatrix.size(); i++){// boucle sur les clusters
		for(unsigned int j = this->_respiteMatrix[i].size()-3; j < this->_respiteMatrix[i].size(); j++){//boucle sur le temps
			for(unsigned int k = 0; k < this->_respiteMatrix[i][j].size(); k++){//boucle sur le nbr d'états dépuisement
				for(unsigned int l = 0; l < this->_respiteMatrix[i][j][k].size(); l++){
                    cout<<this->_respiteMatrix[i][j][k][l]<<" ";
				    }
				cout<<endl;
				}
		       cout<<"-----------------time-------------time"<<endl;
			}
		cout<<" ######################  cluster ####################################"<<endl;
		}



	   cout<<"------------------------------------------------------------------------"<<endl;
	   cout<<"le vecteur du burnout est le suivant : "<<endl;
	   cout<<"------------------------------------------------------------------------"<<endl;

	   for(unsigned int i = 0; i < this->_burnoutVector.size(); i++){
		   for(unsigned int j = 0; j < this->_burnoutVector[i].size(); j++){
			   for(unsigned int k = 0; k < this->_burnoutVector[i][j].size(); k++){
				   cout<<this->_burnoutVector[i][j][k]<<endl;
			   }

			   cout<<"------------------------Time--------------------"<<endl;
		   }
		   cout<<"-------------------Cluster--------------------"<<endl;
	   }



	   cout<<"------------------------------------------------------------------------"<<endl;
	   cout<<"le vecteur de fréquence de répit est le suivant : "<<endl;
	   cout<<"------------------------------------------------------------------------"<<endl;

	   for(unsigned int i = 0; i < this->_respiteFrequenceVector.size(); i++){
		   for(unsigned int j = 0; j < this->_respiteFrequenceVector[i].size(); j++){
				   cout<<this->_respiteFrequenceVector[i][j]<<endl;
		  cout<<"------------------------State--------------------"<<endl;
		   }
		   cout<<"-------------------Cluster--------------------"<<endl;
	   }


//
	   cout<<"------------------------------------------------------------------------"<<endl;
	   cout<<"le vecteur du répit est le suivant : "<<endl;
	   cout<<"------------------------------------------------------------------------"<<endl;

	   for(unsigned int i = 0; i < this->_respiteVector.size(); i++){
		   for(unsigned int j = 0; j < this->_respiteVector[i].size(); j++){
			   for(unsigned int k = 0; k < this->_respiteVector[i][j].size(); k++){
				   cout<<this->_respiteVector[i][j][k]<<endl;
			   }

			   cout<<"------------------------Time--------------------"<<endl;
		   }
		   cout<<"-------------------Cluster--------------------"<<endl;
	   }

	}
//-----------------------------------------------------Fin----------------------------------



//-----------------------------------------------------Debut----------------------------------

void MarkovProcessAnalytic::genrateBurnoutRepartition(){

	vector< float> temp1(this->_inputData->getNbrStatePerCluster(), 0);

	for(unsigned int i = 0; i < this->_inputData->getNemberCluster(); i++){
		vector< vector <float> > temp2;
		for(unsigned int j = 0; j < this->_inputData->getTImeHorizon(); j++){
			vector< float> temp1(this->_inputData->getNbrStatePerCluster(), 0);
			for(unsigned int k = 0; k < this->_inputData->getNbrCaregiverPerCluster(); k++){
				if(j == 0){
					float burnout = this->_inputData->getBurnoutByIdByTime(i,k,j);
					temp1[int(burnout)-1]+=float(1)/float(this->_inputData->getNbrCaregiverPerCluster());
					//cout<<"check mo, vector : "<<temp1[int(burnout)]<<endl;
				}

			}
			temp2.push_back(temp1);
		}
	  this->_burnoutVector.push_back(temp2);
	}
}
//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------

void MarkovProcessAnalytic::generateRespiteRepartition(){

	vector< float> temp1(this->_inputData->getmaxTimeInRespite(), 0);
	//cout<<"mon répit vaut : "<<temp1[2]<<endl;
	vector< vector < float> > temp2 (this->_inputData->getNbrStatePerCluster(), temp1);

	for(unsigned int i = 0; i < this->_inputData->getNemberCluster(); i++){
		this->_respiteVector.push_back(temp2);
	}
	//vector< vector < vector< float> >  > this->_respiteVector(this->_inputData->getNemberCluster(), temp2);

}
//-----------------------------------------------------Fin----------------------------------


//-----------------------------------------------------Debut----------------------------------
void MarkovProcessAnalytic::generateVectorRespiteFrequence(){
		for(unsigned int j = 0; j < this->_inputData->getNemberCluster(); j++){
			vector<float>temp1;
			for(unsigned int k = 0; k < this->_inputData->getNbrStatePerCluster(); k++){
				if(k < this->_inputData->getNbrStatePerCluster()/2){
					float val = this->_respiteFrequence/2;
					val= val /float(this->_inputData->getmaxTimeInRespite()*(k+1));
					temp1.push_back(val);
				}
				else{
					float val = this->_respiteFrequence;
					val= val /float(this->_inputData->getmaxTimeInRespite()*(k+1));
					temp1.push_back(val);
				}
			}
			this->_respiteFrequenceVector.push_back(temp1);
		}
}
//-----------------------------------------------------Fin---------------------------------

//-----------------------------------------------------Debut----------------------------------
void MarkovProcessAnalytic::checkMarkovMatrix(){

	//Verfier les conditions stochastique de notre matice des transisons d eMarkov
	for(unsigned int i = 0; i < this->_burnoutMatrix.size(); i++){
		for(unsigned int j = 0; j < this->_burnoutMatrix[i].size(); j++){
			for(unsigned int k = 0; k < this->_burnoutMatrix[i][j].size(); k++){
				float val = 0;
				for(unsigned int l = 0; l < this->_respiteMatrix[i][j][k].size()+this->_burnoutMatrix[i][j][k].size(); l++){
					if(l < this->_respiteMatrix[i][j][k].size()){
						val+=this->_respiteMatrix[i][j][k][l];
					}
					else{
						val+=this->_burnoutMatrix[i][j][k][l-this->_respiteMatrix[i][j][k].size()];
					}
				}
				if(val != 1){
					cout<<" Attention la somme des probas sur une ligne est !!!!!!!!!!!!!!! : "<<val<<endl;
				}

			}
		}
	}

	//verifier les condition stochastique des vecteurs de répartitons sur l'épuisement et le répit

	for(unsigned int i = 0; i < this->_inputData->getNemberCluster(); i++){
        float val = 0;
		for(unsigned int j = 0; j < this->_inputData->getNbrStatePerCluster(); j++){
			for(unsigned int k = 0; k < this->_inputData->getTImeHorizon() + this->_timeMaxRespite; k++){
				if(k < this->_inputData->getTImeHorizon()){
					val+=this->_burnoutVector[i][k][j];
				}
				else{
					val+=this->_respiteVector[i][j][k - this->_inputData->getTImeHorizon()];
				}
			}
		}
	     if (val != 1 ){
	    	 cout<<"Attention voila somme de ma répartition !!!!!!!!!!!!!!!!!!! : "<<float(val)<<endl;
	     }


	}



}
//-----------------------------------------------------Fin---------------------------------

//-----------------------------------------------------Debut----------------------------------
void MarkovProcessAnalytic::stationnaryPolicy(){

	//this->_nbrIterationForMarkoProcess = this->_inputData->getTImeHorizon()*this->_inputData->getNbrStatePerCluster()
//	cout<<"début du processus de Markov"<<endl;
	for(unsigned int i = 0; i < 600; i++){
//		cout<<"############################################"<<endl;
//		cout<<"------------Iteration --------------- : "<<i+1<<"--------"<<endl;
//		cout<<"###########################################"<<endl;
		//this->printInstance();
		this->updateBurnoutVector();
		this->updateRespiteVector();
		this->_burnoutVector = burnoutTemp;
		this->_respiteVector = respiteTemp;
//		this->checkMarkovMatrix();
	}
//	cout<<"Fin de processus de Markov"<<endl;

	cout<<"Le nombre d'aidants en urgence : "<<this->getNbHospitalization()<<endl;
	cout<<"Le nombre de ressources répit : "<<this->getRespiteRessources()<<endl;

}
//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------
void MarkovProcessAnalytic::updateBurnoutVector(){



burnoutTemp = this->_burnoutVector;
	for(unsigned int i = 0; i < this->_inputData->getNemberCluster(); i++){
		for(unsigned int j = 0; j < this->_inputData->getTImeHorizon(); j++){
			for(unsigned int k = 0; k < this->_inputData->getNbrStatePerCluster(); k++){
				float val = 0;
					if(j == 0){
						val = this->_respiteVector[i][k][0];
					}
					else{
						for(unsigned int l = 0; l < this->_inputData->getNbrStatePerCluster(); l++){
//							cout<<"la valeur du vecteur est : "<< this->_burnoutVector[i][j][l]<<endl;
//							cout<<"la valeur de la matrice est : "<< this->_burnoutMatrix[i][j-1][l][k]<<endl;
							val+=this->_burnoutVector[i][j-1][l]*this->_burnoutMatrix[i][j-1][l][k];
						}
					}
					burnoutTemp[i][j][k] = val;
			}
		}
	}

//	cout<<"voici le résultat du vecteur épuisement pour vérifier"<<endl;
//	for(unsigned int i = 0; i < burnoutTemp.size(); i++){
//		for(unsigned int j = 0; j < burnoutTemp[i].size(); j++){
//			for(unsigned int k = 0; k < burnoutTemp[i][j].size(); k++){
//				cout<<burnoutTemp[i][j][k]<<endl;
//			}
//			cout<<"------------------time-----------------------"<<endl;
//		}
//		cout<<"------------------Cluster-----------------------"<<endl;
//	}
//


}
//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------
void MarkovProcessAnalytic::updateRespiteVector(){

	respiteTemp = this->_respiteVector;
	for(unsigned int i = 0; i < this->_inputData->getNemberCluster(); i++){
		for(unsigned int j = 0; j < this->_inputData->getNbrStatePerCluster(); j++){
			for(unsigned int k = 0; k < this->_inputData->getmaxTimeInRespite(); k++){
				float val = 0;
				for(unsigned int l = 0; l < this->_inputData->getTImeHorizon(); l++){
					unsigned int s = j;
					while(s < this->_inputData->getNbrStatePerCluster()){
						val +=this->_respiteMatrix[i][l][s][j]*this->_burnoutVector[i][l][s];
						s++;
					}
				}
				if(k < this->_inputData->getmaxTimeInRespite()-1){
					val+=this->_respiteVector[i][j][k+1];
				}
				respiteTemp[i][j][k] = val;
			}
		}
	}

//	cout<<"voici le résultat du vecteur répit pour vérifier"<<endl;
//	for(unsigned int i = 0; i < respiteTemp.size(); i++){
//		for(unsigned int j = 0; j < respiteTemp[i].size(); j++){
//			for(unsigned int k = 0; k < respiteTemp[i][j].size(); k++){
//				cout<<respiteTemp[i][j][k]<<endl;
//			}
//			cout<<"------------------time-----------------------"<<endl;
//		}
//		cout<<"------------------Cluster-----------------------"<<endl;
//	}

}
//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------
void MarkovProcessAnalytic::getKpiResults(){

	vector<float> temp(this->_inputData->getTImeHorizon(), 0);
	for (unsigned int i = 0; i < this->_burnoutVector.size(); i++){
		for(unsigned int j = 0; j < this->_burnoutVector[i].size(); j++){
			for(unsigned int k = 0; k < this->_burnoutVector[i][j].size(); k++){
                if(k == this->_burnoutVector[i][j].size()-1){
                	temp[j]+=this->_burnoutVector[i][j][k];
                }

			}
		}
	}


	string const monFichier("C:/Users/oussama.batata/eclipse-workspace/simulation/resultsMarkovProcess.txt");


	ofstream monflux(monFichier.c_str());

	for(unsigned int i = 0; i < temp.size(); i++){
   	 monflux<<temp[i]<<" ";
	}
//    float val = 0;
//	for (unsigned int i = 0; i < this->_burnoutVector.size(); i++){
//		for(unsigned int j = 0; j < this->_burnoutVector[i].size(); j++){
//
//			for(unsigned int k = 0; k < this->_burnoutVector[i][j].size(); k++){
//				cout<<_burnoutVector[i][j][k]<<"  ";
//                if (j == this->_burnoutVector[i].size()-1 && k <= this->_burnoutVector[i][j].size()-2){
//                	val+=this->_burnoutVector[i][j][k];
//                }
//                if(k == this->_burnoutVector[i][j].size()-1){
//                	 monflux<<this->_burnoutVector[i][j][k]<<" ";
//                }
//
//			}
//		}
//	}




//    	for (unsigned int i = 0; i < this->_respiteVector.size(); i++){
//    		for(unsigned int j = 0; j < this->_respiteVector[i].size(); j++){
//
//    			for(unsigned int k = 0; k < this->_respiteVector[i][j].size(); k++){
//    				cout<<_burnoutVector[i][j][k]<<"  ";
//
//    			}
//    			cout<<endl;
//    		}
//    	}


}
//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------
float MarkovProcessAnalytic::getNbHospitalization(){
    float nbHospitalization = float(0);
	for(unsigned int i = 0; i < this->_burnoutVector.size(); i++){
		for(unsigned int j = 0; j < this->_burnoutVector[i].size(); j++){
			for(unsigned int k = 0; k < this->_burnoutVector[i][j].size(); k++){
				if (j > 10 && k == this->_burnoutVector[i][j].size()-1){
					nbHospitalization+=float(this->_burnoutVector[i][j][k]);
				}
			}
		}
	}

	return nbHospitalization;
}

//-----------------------------------------------------Fin----------------------------------

//-----------------------------------------------------Debut----------------------------------
float MarkovProcessAnalytic::getRespiteRessources(){
    float nbRespiteRessources = 0;

//    for(unsigned int i = 0; i < this->_respiteVector.size(); i++){
//    	for(unsigned int j = 0; j < this->_respiteVector[i].size(); j++){
//    		for(unsigned int k = 0; k < this->_respiteVector[i][j].size(); k++){
//    			//cout<<nbRespiteRessources<<endl;
//    			nbRespiteRessources+=float(this->_respiteVector[i][j][k]);
//    		}
//    	}
//    }
//


    for (unsigned int i = 0; i < this->_respiteVector.size(); i++){
    	for(unsigned int j = 0; j < this->_respiteVector[i].size(); j++){
    		for(unsigned int k = 0; k < this->_respiteVector[i][j].size(); k++){
    			nbRespiteRessources+=this->_respiteVector[i][j][k];
    		}
    	}
    }

 return nbRespiteRessources;

}

//-----------------------------------------------------Fin----------------------------------



} /* namespace mySpace */
