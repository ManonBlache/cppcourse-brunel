#include "Network.h"
#include <cassert>
#include <random>

//#include <map>

Network::Network()
	:Net_clock_(0)
{	//neurons_.resize(12500); ///don't need this line if using tab.push_back()
	//connections_.resize(12500, vector<int>(12500, 0));	
	create_network(Ne_,Ni_); //!< When network is created, it creates all the 12500 neurons
	connect(); //!<And then creates the 10% connections between them
	string nom_fichier ("data_network_A.gdf");
	sortie.open(nom_fichier.c_str());
	if (sortie.fail()) {
		cerr << "Erreur d'ouverture du fichier,"
			 << "impossible d'écrire dans le fichier " << nom_fichier << endl;
			 } 
}

Network::~Network(){
		for (auto& neuron : neurons_){
			neuron= nullptr;
			delete neuron;
		}
	
	sortie.close();
}

vector<Neuron*> Network::getNeurons(){ return neurons_;}

void Network::create_network(int exct,int inhb){
	for (int i(0); i<exct; ++i) {
		Neuron* neuron (new Neuron(0.1));
		neurons_.push_back(neuron);
		}
	for (int i(0); i<inhb; ++i) {
		Neuron* neuron (new Neuron(-0.5));//to change to -0.5
		neurons_.push_back(neuron);
		}
	
}

void Network::connect(){ 
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> exct(0,Ne_-1);
	uniform_int_distribution<> inhb(Ne_,Ne_+Ni_-1);
	
	///create random connections for each neuron
	for (auto& neuron : neurons_){
		
		for (int exct_cons=0; exct_cons < Ce_ ; ++exct_cons){ 
			//!< create the 1000 excitatory connections
			neuron->setConnections(exct(gen));
		}
		for (int inhb_cons=0; inhb_cons < Ci_ ; ++inhb_cons){ 
			//!< create the 250 inhibitatory connections
			neuron->setConnections(inhb(gen));
		}

	}
	
	
}

void Network::update(bool poisson){
	
	static random_device rd;
	mt19937 gen(rd());
	double v = (threshold_*eta_)/(0.1*tau_);
	poisson_distribution<> d(v*0.1);

	int indice (0);
			
	for (auto& neuron : neurons_){
				
		if (neuron->Update(0.0, poisson, d(gen))){
			sortie << neuron->getLifeTime()/0.1 << '\t' << indice+1 << '\n';
				
			for (auto target : neuron->getTargets()){
								neurons_[target]->ImplementBuffer( neuron->getJ(),
													neuron->getLifeTime()/0.1);
				
						}
					
					
				}	
				++indice;
			}

++Net_clock_;

}
