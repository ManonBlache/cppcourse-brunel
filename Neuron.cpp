#include "Neuron.h"
#include <cmath>

//Constructeur et constructeur de copie
	Neuron::Neuron()
	:membrane_pot_(0),
	 num_spikes_(0),
	 tau_(20), //membrane time constant
	 tau_ref_(2),
	 membrane_resistance_(20),//membrane resistance
	 threshold_(20), //spike threshold
	 life_time_(0),
	 h_(0.1), //integration time step
	 ref_(0),
	 Iext_(1.01),
	 J_(0.1),//PSP (spike response) amplitude 
	 D_(1.5), //Synaptic delay
	 buffer_((D_/h_)+1, 0)
	 {}

	Neuron::Neuron(double const& birth) 
	: membrane_pot_(0),
	 num_spikes_(0),
	 tau_(20), //membrane time constant
	 tau_ref_(2),
	 membrane_resistance_(20),//membrane resistance
	 threshold_(20), //spike threshold
	 life_time_(birth),
	 h_(0.1), //integration time step
	 ref_(0),
	 Iext_(1.01),
	 J_(0.1),//PSP (spike response) amplitude 
	 D_(1.5), //Synaptic delay
	 buffer_((D_/h_)+1, 0)
	{} 
	
	Neuron::Neuron(Neuron const &autre)
	:membrane_pot_(autre.membrane_pot_), num_spikes_(autre.num_spikes_), tau_(10), tau_ref_(2)
	{} 
	
	Neuron::~Neuron (){}
	
//Getters and setters
	double Neuron::getMembranePot () const { return membrane_pot_; }
    unsigned int Neuron::getSpikes () const { return num_spikes_; }
    double Neuron::getLifeTime() const {return life_time_*h_;}
    double Neuron::getH() const {return h_;}
    double Neuron::getD() const {return D_;}
    double Neuron::getJ() const {return J_;}
    void Neuron::setLifeTime(int time) {life_time_=life_time_+time;}
    void Neuron::setH(double h) {h_=h;}
    void Neuron::setIext(double I) {Iext_=I;}

//Method that updates the neuron state from time t+T, where T=n*h
bool Neuron::Update (double const& Iext)
{
	spike_ =false;
	
	if (ref_>0){
		membrane_pot_=0;
		///neuron is refractory so it doesn't interact, 
		///we have to clear the buffer or the next time it will receive twice the J value
		clearBuffer((life_time_+1)%buffer_.size()); 
		ref_ -=1;
	} else {

	membrane_pot_= getBuffer((life_time_+1)%buffer_.size()) +(exp(-h_/tau_)*membrane_pot_) + ( Iext*membrane_resistance_*(1-exp(-h_/tau_)) ) ;
		clearBuffer((life_time_+1)%buffer_.size());
	}
	
	if (membrane_pot_>=threshold_) {
		ref_= tau_ref_/h_;
		membrane_pot_=0;
		num_spikes_+=1;
		spike_=true;
		}
		
		life_time_+=1;
	return spike_;
}


void Neuron::ImplementBuffer(double j, int d) {
	size_t position = (life_time_+d)%buffer_.size();
	buffer_[position]+=j;
}

double Neuron::getBuffer(size_t position) {
	return buffer_[position];
}

void Neuron::clearBuffer(size_t position){
	buffer_[position]=0;
	}
