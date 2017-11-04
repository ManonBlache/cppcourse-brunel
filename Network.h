#ifndef NETWORK_H
#define NETWORK_H
#include "Neuron.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Network
{
	private:
	int Net_clock_;
	
	const int N_ = 12500; //!<number of neurons
	
	
	const int Ni_ = N_/5; //!<number of inhibitatory neurons
	const int Ne_ = Ni_*4; //!<number of excitatory neurons
	
	const int Ce_ = Ne_*0.1; //!<number of excitatory connections = 1000
	const int Ci_ = Ni_*0.1; //!<number of inhibitatory connections = 250
	
	const double g =3;
	const double Je_ = 0.1; //!<weight for excitatory connections
	const double Ji_ = -g*Je_; //!<weight for inhibitatory connections
	
	vector <Neuron*> neurons_;
	//vector <vector <int> > connections_;
	
	ofstream sortie;
	const double eta_= 2;
	const double tau_=20;
	const double threshold_=20; //!<Tau used in the membrane potential implementation formula = 20 ms
	

	
	public:
	
	//Constructeur et constructeur de copie
	Network();
	~Network();
	
	//Getters & setters
	vector<Neuron*> getNeurons();
	
	//Methodes
	void create_network(int exct, int inhb);
	/*!
     * @brief : Function to create the netword, i.e. the 12500 neurons.
     * 			
     */
	void connect();
	/*!
     * @brief : Function to create the random connections between the neurons,
     * 			implement the connections_ tab with each connection.
     */
     
     void update(bool poisson);
     /*!
     * @brief : Passes through the neurons_ vector,
     * 			if the neuron spikes during his Neuron::update(),
     * 			the Network::update() find the connections and implement 
     * 			the buffer of connected neurons
     */
	
};




#endif
