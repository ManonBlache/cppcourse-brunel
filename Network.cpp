#include "Network.h"
#include <cassert>
#include <random>
//#include <map>

Network::Network()
{	//neurons_.resize(12500); ///don't need this line if using tab.push_back()
	connections_.resize(12500, vector<int>(12500, 0));	
	create_network(12500); //!< When network is created, it creates all the 12500 neurons
	connect(); //!<And then creates the 10% connections between them
}

Network::Network(int number)
{	/*neurons_.resize(12500); don't need this line if using 
	tab.push_back() in function create_network*/
	connections_.resize(number, vector<int>(number, 0));	
	create_network(number); //!< When network is created, it creates all the 12500 neurons
	connect(); //!<And then creates the 10% connections between them
}

Network::~Network(){
		for (auto& neuron : neurons_){
			neuron= nullptr;
			delete neuron;
		}
	
	
}

void Network::create_network(int num_neurons){
	for (int i(0); i<num_neurons; ++i) {
		Neuron* neuron (new Neuron());
		neurons_.push_back(neuron);
		}
	
}

void Network::connect(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> exct(0,9999);
	uniform_int_distribution<> inhb(10000,12499);
	
	///create random connections for each neuron
	for (size_t neuron_s = 0; neuron_s < 12500; ++neuron_s){
		
		for (size_t exct_cons=0; exct_cons < 1000 ; ++exct_cons){ 
			//!< create the excitatory connections
			size_t connected_neuron(exct(gen));
			connections_[connected_neuron][neuron_s]+=1; 
			//the neuron receive connection from connected_neuron
		}
		for (size_t inhb_cons=0; inhb_cons < 250 ; ++inhb_cons){ 
			//!< create the inhibitatory connections
			size_t connected_neuron(inhb(gen));
			connections_[connected_neuron][neuron_s]+=1;
		}

	}
	
	
}

void Network::update(){
	
	for (size_t sender(0); sender < neurons_.size(); ++sender){
		
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

	}

}
