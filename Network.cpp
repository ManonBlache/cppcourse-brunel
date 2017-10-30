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

void Network::create_network(int num_neurons){
	for (int i(0); i<num_neurons; ++i) {
		Neuron* neuron (new Neuron);
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
		
		for (size_t exct_cons=0; exct_cons < 1000 ; ++exct_cons){ //!< create the excitatory connections
			size_t connected_neuron(exct(gen));
			connections_[neuron_s][connected_neuron]+=1;
			}
		for (size_t inhb_cons=0; inhb_cons < 250 ; ++inhb_cons){ //!< create the inhibitatory connections
			size_t connected_neuron(inhb(gen));
			connections_[neuron_s][connected_neuron]+=1;
			}

		}
	
	
}

void Network::update(){
	
	
	
	
	
}
