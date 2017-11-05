#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
using namespace std;

class Neuron
{
	private:
		
	
		double membrane_pot_; //!< Membrane potential
		unsigned int num_spikes_;//!<Global neuron count for spikes during whole simulation
		bool spike_; //!<true if the neuron spiked during last update
		
		double tau_; //!<Tau used in the membrane potential implementation formula = 20 ms
		double tau_ref_; //!<refractory time of neuron = 2 ms
		double  membrane_resistance_; //!< = 20
		double threshold_;  //!< = 20
		int life_time_; //!<Neuron clock
		double h_; //!<Step time = 0.1 ms		
		double ref_;//!< number of steps required to quit refractory time = tau_ref_/h
		double Iext_; //!<External current
		double J_; //!>weight
		int D_; //!<Delay
		
		vector <double> buffer_ ; //!< Neuron buffer, contains J values
		vector <int> targets_; //!< Keep in memory neurons it is connected to
	
	public:
	
	//Constructeur et constructeur de copie
	Neuron(double J);
	Neuron(double J, double const& birth); 
	~Neuron ();
	
	//Getters et setters
	double getMembranePot() const;
    unsigned int getSpikes() const;
    bool getIfSpike() const;
    double getLifeTime() const;
    double getH() const;
    double getD() const;
    double getJ() const;
    vector<int> getTargets() const;
    
    void setLifeTime(int time);
    void setH(double h);
    void setJ(double j);
    void setIext(double I);
	
	//Method that updates the neuron state from time t+T, where T=n*h
	bool Update(double const& Iext, bool poisson, int poissongene);
	/*!
     * @brief : Function to update neurons. 
     * -Implement membrane potential w/o poisson (bool true/false)
     * -Check spiking condition and set the neuron as refractory if needed
     * @param : Takes as paramaters the external current Iext, and a 
     * boolean to use or not the Poissson's background noise.
     * @return : the neuron spiked during this update (true), or not (false) 
     **/

	//Methods to implement and use the ring buffer
	void ImplementBuffer(double j, int time);
	/*!
     * @brief : Function to implement the buffer when a spike from 
     * 			a connected neuron occurs
     * @param : Takes as paramaters the amplitude J and delay D
     */
     
	double getBuffer(int time);
	/*!
     * @brief : Function to get the value in the buffer, at time 'position'
     * @param : Takes as parameter the tab position to be returned
     * @return : Returns the value in tab[position]
     */
     
	void clearBuffer(size_t position);
	/*!
     * @brief : Function to clear the buffer at a certain time ,
     * 			when the value in this case is used.
     * @param : Takes as paramater the tab position to be cleared. 
     */
	
	void setConnections(int target);
	/*!
     * @brief : Function to implement the targets_ tab of the neuron
     * @param : Takes as paramater the target neuron ID 
     */
	
};




#endif
