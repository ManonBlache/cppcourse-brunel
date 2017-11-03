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
}

Network::~Network(){
		for (auto& neuron : neurons_){
			neuron= nullptr;
			delete neuron;
		}
	
	
}

vector<Neuron*> Network::getNeurons(){ return neurons_;}

void Network::create_network(int exct,int inhb){
	for (int i(0); i<exct; ++i) {
		Neuron* neuron (new Neuron(0.1));
		neurons_.push_back(neuron);
		}
	for (int i(0); i<inhb; ++i) {
		Neuron* neuron (new Neuron(0.1));//to change to -0.5
		neurons_.push_back(neuron);
		}
	
}

void Network::connect(){ 
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> exct(0,9999);
	uniform_int_distribution<> inhb(10000,12499);
	
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
	
	for (auto& neuron : neurons_){
		
		if (neuron->Update(1.01, poisson)){
			for (auto target : neuron->getTargets()){
				neurons_[target]->ImplementBuffer( neuron->getJ(),
												   neuron->getLifeTime()/0.1);
				
				}
				
		}	
	}
	++Net_clock_;
	
	/*for (size_t sender(0); sender < neurons_.size(); ++sender){
		
		if (neurons_[sender]->Update(1.01,true)){ 
			//!< If the neuron spikes, it has to send J in the buffer of neurons connected to it
			
			for (auto target : connections_[sender]){
				
				if ((connections_[sender][target]!=0) and (sender<99999)){ //!< Find the connections
					neurons_[target]->ImplementBuffer((connections_[sender][target]*0.1),15);
				}
				if ((connections_[sender][target]!=0) and (sender>=99999)){ //!< Find the connections
					neurons_[target]->ImplementBuffer((connections_[sender][target]*(-0.5)),15);
				}
			}
				
		}

	}*/

}
