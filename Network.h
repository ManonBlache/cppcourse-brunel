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
	int Net_clock_; //!< global clock of the whole network
	
	const int N_ = 12500; //!<number of neurons
	
	
	const int Ni_ = N_/5; //!<number of inhibitatory neurons
	const int Ne_ = Ni_*4; //!<number of excitatory neurons
	
	const int Ce_ = Ne_*0.1; //!<number of excitatory connections = 1000
	const int Ci_ = Ni_*0.1; //!<number of inhibitatory connections = 250
	
	const double g =4.5;
	const double Je_ = 0.1; //!<weight for excitatory connections
	const double Ji_ = -g*Je_; //!<weight for inhibitatory connections
	
	vector <Neuron*> neurons_; //!<memory of the target neurons
	
	ofstream sortie; //!<  output file for the spikes
	const double eta_= 0.9;
	const double tau_=20;
	const double threshold_=20; //!<Tau used in the membrane potential implementation formula = 20 ms
	

	
	public:
	
	//Constructeur et destructeur
	Network();
	~Network();
	
	//Getters & setters
	vector<Neuron*> getNeurons();
	/*!
     * @brief : function to return the target neurons.
     * 
     * @return : the vector with the targets ID
     * 			
     */
	
	//Methodes
	void create_network(int exct, int inhb);
	/*!
     * @brief : Function to create the netword, i.e. the 12500 neurons.
     * 
     * @param : take as parameters the number of excitatory and 
     * 		inhibitatory neurons.			
     */
	void connect();
	/*!
     * @brief : Function to create the random connections between the neurons,
     * 			implement the targets_ tab with each connection.
     */
     
     void update(double iext ,bool poisson);
     /*!
     * @brief : Passes through the neurons_ vector,
     * 			if the neuron spikes during his Neuron::update(),
     * 			the Network::update() find the connections and implement 
     * 			the buffer of connected neurons
     * @param : take as parameters the external current iext and the boolean
     * 			argument to know if we want to use the poisson distribution or not.
     */
	
};




#endif
