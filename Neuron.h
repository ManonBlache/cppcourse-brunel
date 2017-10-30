#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
using namespace std;

class Neuron
{
	private:
		
	
		double membrane_pot_;
		unsigned int num_spikes_;
		bool spike_;
		
		double tau_; ///Tau used in the membrane potential implementation formula = 20 ms
		double tau_ref_; ///refractory time of neuron = 2 ms
		double  membrane_resistance_; /// = 20
		double threshold_;  /// = 20
		int life_time_; ///number of steps since birth
		double h_; ///time of a single step = 0.1 ms		
		double ref_;/// number of steps required to quit refractory time = tau_ref_/h
		double Iext_; ///External current
		
		double J_; ///weight
		int D_; ///Delay
		
	public:
		vector <double> buffer_ ;

	
	public:
	
	//Constructeur et constructeur de copie
	Neuron();
	Neuron(double const& birth); 
	Neuron(Neuron const &autre);
	~Neuron ();
	
	//Getters et setters
	double getMembranePot() const;
    unsigned int getSpikes() const;
    double getLifeTime() const;
    double getH() const;
    double getD() const;
    double getJ() const;
    void setLifeTime(int time);
    void setH(double h);
    void setIext(double I);
	
	//Method that updates the neuron state from time t+T, where T=n*h
	bool Update(double const& Iext); ///true if spike during update

	//Methods to implement and use the ring buffer
	void ImplementBuffer(double j, int d);
	/*!
     * @brief : Function to implement the buffer when a spike from 
     * 			a connected neuron occurs
     * @param : Takes as paramaters the amplitude J and delay D
     */
     
	double getBuffer(size_t position);
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
	
};




#endif
